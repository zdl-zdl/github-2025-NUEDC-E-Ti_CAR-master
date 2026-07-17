#include "headfile.h"

float left_speed = 0;
float right_speed = 0;

SPEED_PID_Struct left_speed_pid = 
{
	.ki = 7.7,
	.kp = 0.0
};

SPEED_PID_Struct right_speed_pid = 
{
	.ki = 7.5,
	.kp = 0.0
};

void GetSpeed(float filter_alpha)
{
    static int32_t last_left_count = 0;
    static int32_t last_right_count = 0;
    int32_t left_count = encoder_left_count;
    int32_t right_count = encoder_right_count;
    int32_t deltaA = left_count - last_left_count;
    int32_t deltaB = right_count - last_right_count;
    last_left_count = left_count;
    last_right_count = right_count;
    float raw_left_count = ((float)deltaA / ENCODER_RESOLUTION) * WHEEL_CIRCUMFERENCE / 0.01f;
    float raw_right_speed = ((float)deltaB / ENCODER_RESOLUTION) * WHEEL_CIRCUMFERENCE / 0.01f;
    static float last_left_speed = 0;
    static float last_right_speed = 0;
    left_speed = filter_alpha * raw_left_count + (1 - filter_alpha) * last_left_speed;
    right_speed = filter_alpha * raw_right_speed + (1 - filter_alpha) * last_right_speed;
    last_left_speed = left_speed;
    last_right_speed = right_speed;
}

int LeftSpeedPidCtrl(int target, int current)
{  
    static float left_pwm = 0.0f, last_offset = 0.0f;
    float offset = (float)(target - current); 
    left_pwm += left_speed_pid.ki * (offset - last_offset) + left_speed_pid.kp * offset;
    last_offset = offset;
    if(left_pwm >= MaxPWM) left_pwm = MaxPWM;
    else if(left_pwm <= -MaxPWM) left_pwm = -MaxPWM;
    return (int)left_pwm;
}

int RightSpeedPidCtrl(int target, int current)
{  
    static float right_pwm = 0.0f, last_offset = 0.0f;
    float offset = (float)(target - current); 
    right_pwm += right_speed_pid.ki * (offset - last_offset) + right_speed_pid.kp * offset;
    last_offset = offset;
    if(right_pwm >= MaxPWM) right_pwm = MaxPWM;
    else if(right_pwm <= -MaxPWM) right_pwm = -MaxPWM;
    return (int)right_pwm;
}

/***  转角环（90° 定点转弯）***
 * 当前：左轮停(PWM=0)、右轮前进(offset+PID)，绕左轮 pivot 转
 * 开环问题：①打滑导致编码器读数≠实际转角 ②速度不受控(目标20m/s不可达)
 *
 * 【改进建议】
 * 方案A-差速转弯（减少打滑）：左轮反转+右轮正转，原地转
 *   motor_left_dir=0; Motor_LeftCtrl(offset+fabs(left_pwm));
 *   motor_right_dir=1; Motor_RightCtrl(offset+fabs(right_pwm));
 *   注意：差速转弯 TURN_DISTANCE = 定点转弯的一半(轮距×π/4)
 *
 * 方案B-陀螺仪闭环（最精确）：用 yaw 角度做 PID 反馈
 *   在 IsTurnComplete() 里用 gyro_yaw 判断（已预留，见 task.c）
 *   转弯速度用 yaw 误差的 PD 控制，而非固定 offset
 */
void turn_90_control(int tar, int offset)
{
	float left_pwm = LeftSpeedPidCtrl(tar, left_speed);
	float right_pwm = RightSpeedPidCtrl(tar, right_speed);
	if(left_pwm > 0) motor_left_dir = 1; 	else motor_left_dir = 0;
	if(right_pwm > 0) motor_right_dir = 1;	else motor_right_dir = 0;
	Motor_LeftCtrl(0);
	Motor_RightCtrl(offset + fabs(right_pwm));
}

/***  速度环  ***/
void SpeedPidCtrl(int tar, int base)
{
	if (abs(tar) < 5) tar = 0;
	float left_pwm = base - LeftSpeedPidCtrl(tar, left_speed);
	float right_pwm = base + RightSpeedPidCtrl(tar, right_speed);
	if(left_pwm >= 0) motor_left_dir = 1; 	else motor_left_dir = 0;
	if(right_pwm >= 0) motor_right_dir = 1;	else motor_right_dir = 0;
	Motor_LeftCtrl(fabs(left_pwm));
	Motor_RightCtrl(fabs(right_pwm));
}
