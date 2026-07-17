#include "motor.h"
#define MOTOR_DEADZONE 0   // TB6612死区很小，先设0；若低速不动再调大(如10~30)

/*
 * 当前 TB6612 双路驱动板实际接线（与 ti_msp_dl_config.h / empty.syscfg 同步）：
 *   左轮 PWMA : PB2  (TIMG6_CCP0)  -> 板子 PWMA
 *   左轮 AIN1 : PB15               -> 板子 AIN1
 *   左轮 AIN2 : PB17               -> 板子 AIN2
 *   右轮 PWMB : PB3  (TIMG6_CCP1)  -> 板子 PWMB
 *   右轮 BIN1 : PB13               -> 板子 BIN1
 *   右轮 BIN2 : PB16               -> 板子 BIN2
 *   板子 STBY: 必须外接 3.3V 才能使能（详见 README_接线.md §2.2）
 */


uint8_t motor_left_dir = 1;
uint8_t motor_right_dir = 1;

void Motor_LeftDuty(uint8_t dir, uint32_t speed)
{
    /* 方向逻辑已对调：原接线与实际转向相反 */
    if(dir)
    {
        AIN1_OUT(0);
        AIN2_OUT(1);
    }
    else
    {
        AIN1_OUT(1);
        AIN2_OUT(0);
    }   
        
    DL_TimerG_setCaptureCompareValue(PWM_INST,speed ,GPIO_PWM_C0_IDX);
}

void Motor_RightDuty(uint8_t dir, uint32_t speed)
{
    /* 方向逻辑已对调：原接线与实际转向相反 */
    if(dir)
    {
        BIN1_OUT(0);
        BIN2_OUT(1);
    }
    else
    {
        BIN1_OUT(1);
        BIN2_OUT(0);
    }   
        
    DL_TimerG_setCaptureCompareValue(PWM_INST,speed + MOTOR_DEADZONE,GPIO_PWM_C1_IDX);
}

void Motor_LeftCtrl(float speed)
{
    /* 方向逻辑已对调：原接线与实际转向相反 */
    if(motor_left_dir)
    {
        AIN1_OUT(0);
        AIN2_OUT(1);
    }
    else
    {
        AIN1_OUT(1);
        AIN2_OUT(0);
    }   
        
    DL_TimerG_setCaptureCompareValue(PWM_INST,(uint32_t)speed + MOTOR_DEADZONE, GPIO_PWM_C0_IDX);
}

void Motor_RightCtrl(float speed)
{
    /* 方向逻辑已对调：原接线与实际转向相反 */
    if(motor_right_dir)
    {
        BIN1_OUT(0);
        BIN2_OUT(1);
    }
    else
    {
        BIN1_OUT(1);
        BIN2_OUT(0);
    }   
        
    DL_TimerG_setCaptureCompareValue(PWM_INST,(uint32_t)speed + MOTOR_DEADZONE,GPIO_PWM_C1_IDX);
}

void Motor_Stop(void)
{
	AIN1_OUT(1);
    AIN2_OUT(1);
	
	BIN1_OUT(1);
    BIN2_OUT(1);
}

/*******************************************************
功能：电机正转2s / 反转2s 循环测试（排查用）
说明：dir=1 正转，dir=0 反转；speed 为 PWM 占空值(0~周期)
      每次循环用蓝/绿 LED + 串口打印确认 MSPM0 是否在跑
********************************************************/
void Motor_Test(void)
{
    printf("MOTOR TEST FWD 2s\r\n");
    SetLedMode(LED_BLUE, LED_ON);          // 蓝灯亮 = 正在正转
    Motor_LeftDuty(1, 300);                // 左轮正转
    Motor_RightDuty(1, 300);               // 右轮正转
    delay_ms(2000);
    Motor_Stop();
    delay_ms(500);

    printf("MOTOR TEST REV 2s\r\n");
    SetLedMode(LED_BLUE, LED_OFF);
    SetLedMode(LED_GREEN, LED_ON);         // 绿灯亮 = 正在反转
    Motor_LeftDuty(0, 300);                // 左轮反转
    Motor_RightDuty(0, 300);               // 右轮反转
    delay_ms(2000);
    Motor_Stop();
    delay_ms(500);
    SetLedMode(LED_GREEN, LED_OFF);

    printf("MOTOR TEST DONE\r\n");
}
