#ifndef __DIST_H
#define __DIST_H

#define PI 3.14159265
#define MOTOR_REDUCTION_RATIO 20.0f   // MG310 减速比 1:20
#define ENCODER_PPR 13                // TODO: 改为MG310编码器每转线数(常见11/13/16)，转一圈数脉冲反推
#define ENCODER_QUAD 2                // 2倍频：当前代码只数A/B相各自的上升沿(原工程13*2*28=728即此法)
#define ENCODER_RESOLUTION (ENCODER_PPR * ENCODER_QUAD * MOTOR_REDUCTION_RATIO) // 默认13*2*20=520
#define WHEEL_DIAMETER 0.065f		  // 轮子直径D = 65mm
#define WHEEL_CIRCUMFERENCE (PI * WHEEL_DIAMETER)  // 轮子周长=PI*D
#define WHEEL_DIST (WHEEL_CIRCUMFERENCE / ENCODER_RESOLUTION) // 轮子单脉冲前进距离(mm)
                                                              // = 3.1416*0.065/520 ≈ 0.3927 毫米/脉冲
                                                              // 1m=1000mm ≈ 2546脉冲; TURN_DISTANCE=320mm ≈ 815脉冲


void GetDistance(void);      // 直接获取一段距离
void ClearDistance(void);	   // 清除获取的距离

extern float carL_dis;
extern float carR_dis;

#endif