#include "headfile.h"

uint8_t workstep = 0;		// 工作步骤
uint8_t turn_flag = 0;		// 转向标志
uint8_t lap_count = 0; 	// 行驶圈数
uint8_t corner_detected = 0;	// 触发转向标志
uint8_t corner_cnt = 0;	 // 路段/拐角计次

uint16_t bias = 0;	// 转角环补偿值
float basespeed = 0;	// 行驶速度

/* ===== 陀螺仪转弯预留 =====
 * turn_mode=TURN_ENCODER : 编码器开环（当前），靠距离判断
 * turn_mode=TURN_GYRO    : 陀螺仪闭环（后续），靠 yaw 角度判断
 * 接入陀螺仪后：在定时器中断里更新 gyro_yaw，把 turn_mode 改成 TURN_GYRO
 */
TurnMode_e turn_mode = TURN_ENCODER;  // 默认编码器开环
float gyro_yaw = 0.0f;                 // 陀螺仪 yaw（后续接入后在定时器中断更新）
float turn_target_yaw = 90.0f;        // 转弯目标角度（转弯开始时设为 gyro_yaw+90）

/*
 * @brief 转弯完成判断
 * @note  编码器模式：右轮距离 >= TURN_DISTANCE
 *        陀螺仪模式：yaw 误差 < 3° 死区
 *        后续接入陀螺仪后把 turn_mode 改成 TURN_GYRO 即可切换
 */
static uint8_t IsTurnComplete(void)
{
	if(turn_mode == TURN_GYRO)
	{
		/* 陀螺仪闭环：yaw 达到目标角度停止 */
		float err = turn_target_yaw - gyro_yaw;
		/* 角度环绕处理（-180~180） */
		if(err > 180.0f)  err -= 360.0f;
		if(err < -180.0f) err += 360.0f;
		return (fabs(err) <= 3.0f);  /* 3° 死区 */
	}
	else
	{
		/* 编码器开环：距离达到 TURN_DISTANCE 停止 */
		return (fabs(carR_dis) >= TURN_DISTANCE);
	}
}

/*
 * @brief 进入转弯时调用，记录转弯目标
 * @note  编码器模式：清零距离
 *        陀螺仪模式：记录目标 yaw = 当前 yaw + 90°
 */
static void Turn_Start(void)
{
	ClearDistance();
	turn_target_yaw = gyro_yaw + 90.0f;  /* 目标转 90°（右转） */
}

static void Task_Reset(void)
{
	task_num = 0;
	corner_cnt = 0;
    lap_count = 0;
    corner_detected = 0;
	turn_flag = 0;
    pid_flag = 0;
    basespeed = 0;
	lap_num = 0;
	workstep = 0;
}

/**
 * @brief 赛道拐角与圈数检测处理函数
 * @note  通过灰度传感器检测黑线，识别转弯标志并计数
 */
static void Track_DetectCorner(void)
{
	static int black_cnt = 0;      // 连续扫描到黑线的次数
    static int timer_ms = 0;       // 软件消抖计时器
    static int is_latched = 0;     // 防止单次拐角重复触发

    // 更新灰度传感器原始数据
    Gray_Update();

    // 1. 检测是否处于黑线/拐角标志区（8路：≥4路同时压黑线即视为拐角）
    int black = gray.io[0] + gray.io[1] + gray.io[2] + gray.io[3]
              + gray.io[4] + gray.io[5] + gray.io[6] + gray.io[7];
    if (black >= 4)
    {
        black_cnt++;
    }
    else
    {
        black_cnt = 0;
        is_latched = 0; // 离开黑线区域，重置锁存
    }

    timer_ms++;
    // 触发判断逻辑
    if (black_cnt >= 3 && !is_latched && timer_ms >= 100)
    {
        corner_detected = 1;  
        corner_cnt++;          
        is_latched = 1;       // 锁定当前触发，直到离开黑线
        timer_ms = 0;         // 重置消抖时间

        // 3. 圈数计算逻辑
        if(task_num == 1)
        {
            if (corner_cnt >= 4)
            {
                lap_count++;  // 圈数+1
                corner_cnt = 0;
            }
        } 
        else if(task_num == 2)
        {
            if (corner_cnt >= 5)
            {
                lap_count++;  // 圈数+1
                corner_cnt = 1; 
            }
        }
        // 触发声光反馈
        SoundLightRun();
    }
}


void FirstTask(void)
{
	switch(workstep)
	{
		case 0: 
			PID_Update(&track_pid, POSITION_PID, 145, 0, 65);  // 单级寻迹环
			lap_count = 0;
			corner_detected = 0;
			pid_flag = 0;
			basespeed = 280;
			workstep++;
			break;

		case 1:
			if(lap_count >= lap_num && !debug_no_turn)
			{
				if(!turn_flag)  // 首次进入转弯阶段
				{
					turn_flag = 1;
					Turn_Start();  // 清零距离 + 记录目标yaw
				}

				GetDistance();  // 实时更新距离
				bias = 190;
				basespeed = 20;
				pid_flag = TURN_90_PID;

				// 转弯完成判断（编码器/陀螺仪自动切换）
				if(IsTurnComplete())
				{
					Motor_Stop();
					Task_Reset();
					SetLedMode(LED_BLUE, LED_ON);  // 圈数完成，转弯完成
				}
				break;
			}

			// 非转弯阶段执行寻迹
			if(!turn_flag)
			{
				Track_DetectCorner();
				pid_flag = TRACK_PID;

				if(corner_detected && !debug_no_turn)
				{
					turn_flag = 1;
					Turn_Start();  // 进入拐角转弯
				}
			}
			else  // 拐角转弯阶段
			{
				GetDistance();
				pid_flag = TURN_90_PID;
				bias = 190;
				basespeed = 20;

				if(IsTurnComplete())
				{
					corner_detected = 0;
					turn_flag = 0;
					basespeed = 280;
				}
			}
			break;
	}
}

void SecondTask(void)
{
	switch(workstep)
	{
		case 0: 
			PID_Update(&track_pid, POSITION_PID, 145, 0, 65);  // 单级寻迹环
			corner_cnt = 0;
			lap_count = 0;
			corner_detected = 0;
			pid_flag = 0;
			basespeed = 260;
			workstep++;
			break;

		case 1:
			if(lap_count >= lap_num && !debug_no_turn)  // 圈数达成，直接停车
			{
				Motor_Stop();          
				Task_Reset();    
				ClearDistance();
				break;                 // 不再执行后续逻辑
			}

			// 非转弯阶段执行寻迹
			if(!turn_flag)
			{
				Track_DetectCorner();
				pid_flag = TRACK_PID;

				if(corner_detected && !debug_no_turn)
				{
					turn_flag = 1;
					Turn_Start();  // 进入拐角转弯
				}
			}
			else  // 拐角转弯阶段
			{
				GetDistance();
				pid_flag = TURN_90_PID;
				bias = 190;
				basespeed = 20;

				if(IsTurnComplete())
				{
					corner_detected = 0;
					turn_flag = 0;
					basespeed = 260;
				}
			}
			break;
	}
}


