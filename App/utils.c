#include "headfile.h"

/* ===== 1m 正方形循迹参数 =====
 * 赛道：1m×1m 正方形黑线，4个直角拐角。
 * lap_num=1   → 检测到4个拐角(1圈)后自动停车
 * task_num=1  → FirstTask（循迹 + 90°转弯）
 * debug_no_turn=0 → 启用拐角转弯（正方形必须！）
 * total_start_flag=0 → 等按键发车（按 PB9 TotalStart 键开始）
 * wait_flag=1 → 按键后直接走，跳过倒计时
 * debug_motor_stop=0 → 电机正常工作
 */
uint8_t lap_num          = 1;   // 1圈=4个拐角，跑完自动停车
uint8_t task_num         = 1;   // FirstTask（循迹+90°转弯）
uint8_t total_start_flag = 0;   // 0=等按键发车(按PB9)；1=上电直接发车
uint8_t wait_flag        = 1;   // 跳过倒计时（=0会触发中断内1s阻塞延时）
uint8_t debug_no_turn    = 0;   // 0=正常拐角转弯（正方形必须启用！）
uint8_t debug_motor_stop = 0;   // 0=电机正常工作

void System_Init(void)
{
	SYSCFG_DL_init();
	LedDeviceInit();
	BeepDeviceInit();
	KeyDeviceInit();
	EncoderInit();
	TimerDeviceInit();
	UartDeviceInit();
}

void TaskSelect(void)
{	
	if(total_start_flag == 0)
	{
		if (Key_GetNum(lap_num_key)) 
		{
			SetLedMode(LED_GREEN, LED_ON);
			lap_num++;
			if(lap_num > 5) lap_num = 0;
		}
		
		if(Key_GetNum(task_num_key))
		{
			SetLedMode(LED_BLUE, LED_ON);
			task_num ++;
			if (task_num > 2) task_num = 0; 
		}
		
		if(Key_GetNum(total_start_key))
		{
			total_start_flag = 1;
		}
	}
	else
	{
		if (debug_motor_stop)			// 调试：抬车、手转轮子测编码器，电机关闭
		{
			Motor_Stop();
		}
		else if(wait_flag == 1)	// 修正：倒计时结束后(wait_flag=1)才进入行驶，原==0会导致跑1秒就停
		{
			switch(task_num)
			{
				case First: 		FirstTask(); 		break;
				case Second: 	SecondTask(); 	break;
			}
		}
	}
}

void Wait_For_A_While(void)
{
	SetLedMode(LED_BLUE, LED_ON);
	SetLedMode(LED_GREEN, LED_ON);
	delay_ms(1000);
	wait_flag = 1;
	SetLedMode(LED_BLUE, LED_OFF);
	SetLedMode(LED_GREEN, LED_OFF);
}

/*******************************************************
功能：调试串口打印（约每500ms一次，由TIMER_1(10ms)调用）
输出：8路灰度 + 左右编码器计数 + 左右轮速度 + 基础速度
***********************************************************/
void DebugPrint(void)
{
	static uint8_t cnt = 0;
	if (++cnt < 50) return;          // 50 * 10ms ≈ 500ms
	cnt = 0;

	Gray_Update();                   // 刷新灰度，保证任何状态下都能看到当前值
	GetDistance();                   // 刷新距离，方便观察每段直线/转弯的距离
	printf("GR:%d %d %d %d %d %d %d %d | EL:%d ER:%d | VL:%.1f VR:%.1f | bs:%.0f | dL:%.0f dR:%.0f%s\r\n",
		gray.io[0], gray.io[1], gray.io[2], gray.io[3],
		gray.io[4], gray.io[5], gray.io[6], gray.io[7],
		encoder_left_count, encoder_right_count,
		left_speed, right_speed, basespeed,
		carL_dis, carR_dis,
		debug_no_turn ? " [NO-TURN]" : "");
}


