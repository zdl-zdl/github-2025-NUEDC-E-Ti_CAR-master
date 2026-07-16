#ifndef __TRACK_H
#define __TRACK_H

#include "pid.h"
#include "stdint.h"

typedef struct{
	int8_t w[8];	// 8路对称权重，左负右正，无独立中
}Gray_Weight_Struct; // 灰度权重


void TrackPidCtrl(float basespeed);
int TrackLoopPidCtrl(float target);
void TrackCascadeCtrl(float track_tar, int basespeed);

extern PID_Struct track_pid;	
extern PID_Struct track_loop_pid;	

#endif