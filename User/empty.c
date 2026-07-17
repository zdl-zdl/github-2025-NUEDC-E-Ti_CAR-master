/*
 * Copyright (c) 2021, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#include "headfile.h"

int main(void)
{
	/* ===== 1m 正方形循迹 =====
	 * 赛道：1m×1m 正方形黑线，4个直角拐角。
	 * 流程：灰度循迹(TP)→检测拐角→90°定点转弯(TURN)→继续循迹，4个角后停车。
	 * 参数在 App/utils.c 顶部（lap_num/task_num/debug_no_turn 等）。
	 * TIMER_0(10ms)：测速 + PID_Select（循迹/转弯 PID 切换）
	 * TIMER_1(10ms)：声光反馈 + DebugPrint（每 500ms 串口打印调试）
	 */
	System_Init();          // 时钟 + LED + 蜂鸣器 + 按键 + 编码器 + 定时器中断 + UART中断

	while (1)
	{
		TaskSelect();        // 任务调度：根据 task_num 执行 FirstTask/SecondTask
	}
}


// pid控制
void TIMER_0_INST_IRQHandler(void)   //PID运算  10ms  优先级最高
{
	if(DL_TimerA_getPendingInterrupt(TIMER_0_INST))
	{
		if(DL_TIMER_IIDX_ZERO) 
		{	
			GetSpeed(0.2); 
			PID_Select();
		}
	}
} 

void TIMER_1_INST_IRQHandler(void)	// 声光检测  10ms  优先级高
{
	if(DL_TimerG_getPendingInterrupt(TIMER_1_INST))
	{
		if(DL_TIMER_IIDX_LOAD)
		{	
			if (total_start_flag == 1 && wait_flag == 0) 	Wait_For_A_While();
			SoundLightUpdate();
			DebugPrint();
		}
	}
}


