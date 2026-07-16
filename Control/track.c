#include "headfile.h"

PID_Struct track_pid;   // 单级寻迹
PID_Struct track_loop_pid;	// 串级寻迹

Gray_Weight_Struct gray_weight =
{
	.w = {-7, -5, -3, -1, 1, 3, 5, 7}  // 8路一字排开，左负右正，对称无中
};
// 单级寻迹环
void TrackPidCtrl(float basespeed)
{ 	
	Gray_Update();
	float sum = gray.io[0] + gray.io[1] + gray.io[2] + gray.io[3]
	           + gray.io[4] + gray.io[5] + gray.io[6] + gray.io[7];
	if (sum < 0.001f) sum = 1.0f;
	float current = (gray.io[0] * gray_weight.w[0] + gray.io[1] * gray_weight.w[1]
	               + gray.io[2] * gray_weight.w[2] + gray.io[3] * gray_weight.w[3]
	               + gray.io[4] * gray_weight.w[4] + gray.io[5] * gray_weight.w[5]
	               + gray.io[6] * gray_weight.w[6] + gray.io[7] * gray_weight.w[7]) / sum;
	track_pid.now = current;
	track_pid.target = 0;
	PID_Calculate(&track_pid);
	PID_OutPutLimit(&track_pid, 1000);
	Motor_LeftCtrl(basespeed - track_pid.out);
	Motor_RightCtrl(basespeed + track_pid.out);
}

int TrackLoopPidCtrl(float target)
{
	Gray_Update();
	float sum = gray.io[0] + gray.io[1] + gray.io[2] + gray.io[3]
	           + gray.io[4] + gray.io[5] + gray.io[6] + gray.io[7];
	if (sum < 0.001f) sum = 1.0f;
	float current = (gray.io[0] * gray_weight.w[0] + gray.io[1] * gray_weight.w[1]
	               + gray.io[2] * gray_weight.w[2] + gray.io[3] * gray_weight.w[3]
	               + gray.io[4] * gray_weight.w[4] + gray.io[5] * gray_weight.w[5]
	               + gray.io[6] * gray_weight.w[6] + gray.io[7] * gray_weight.w[7]) / sum;
	track_loop_pid.now = current;
	track_loop_pid.target = target;
	PID_Calculate(&track_loop_pid);
	PID_OutPutLimit(&track_loop_pid, 1000);
	return track_loop_pid.out;
}
// 串级寻迹环
void TrackCascadeCtrl(float track_tar, int basespeed)
{
	int tar = TrackLoopPidCtrl(track_tar);
	SpeedPidCtrl(tar, basespeed);
}
