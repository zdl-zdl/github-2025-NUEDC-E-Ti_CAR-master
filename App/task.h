#ifndef __TASK_H
#define __TASK_H
#include "stdint.h"

#define TURN_DISTANCE 320   // 90°转弯距离(mm)，定点转弯=轮距×π/2；实测微调

/* ===== 转弯模式 =====
 * TURN_ENCODER : 编码器开环转弯（当前），靠 carR_dis >= TURN_DISTANCE 判断
 * TURN_GYRO    : 陀螺仪闭环转弯（后续接入），靠 yaw 角度判断
 * 切换方式：改 task.c 里 turn_mode 变量
 */
typedef enum {
    TURN_ENCODER = 0,   // 编码器开环
    TURN_GYRO,          // 陀螺仪闭环
} TurnMode_e;

void FirstTask(void);
void SecondTask(void);

extern uint8_t turn_flag;
extern uint8_t corner_detected;
extern uint8_t lap_count;
extern uint8_t debug_no_turn;

extern uint16_t bias;
extern float basespeed;

/* 陀螺仪转弯相关（后续接入时使用） */
extern TurnMode_e turn_mode;       // 转弯模式
extern float gyro_yaw;             // 陀螺仪 yaw 角度（后续在定时器中断里更新）
extern float turn_target_yaw;     // 每次转弯的目标 yaw 角度

#endif