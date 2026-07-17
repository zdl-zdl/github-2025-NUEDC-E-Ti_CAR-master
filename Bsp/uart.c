#include "uart.h"
#include <stdio.h>

void UartDeviceInit(void)
{
	// MiniPC
	NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);
	NVIC_EnableIRQ(UART_0_INST_INT_IRQN);
}

/* ===== printf 重定向到 UART0 =====
 * 原实现位于 Bsp/board.c，但 board.c 同时定义了 delay_us/delay_ms，
 * 与 Bsp/delay.c 重复，整文件加入工程会链接报错。
 * 故将 printf 重定向部分（fputc + 半主机 retarget）单独搬到此文件，
 * 既恢复 printf 输出，又不引入重复定义。
 * 该 retarget 写法与原 board.c 一致，已在当前工程（非 MicroLIB）验证可用。
 */
#if !defined(__MICROLIB)
/* 非微库时需要补充以下声明，避免标准库使用半主机接口 */
#if (__ARMCLIB_VERSION <= 6000000)
/* AC5 及更早版本的 FILE 结构定义 */
struct __FILE
{
	int handle;
};
#endif

FILE __stdout;

/* 提供 _sys_exit() 以使用非半主机模式 */
void _sys_exit(int x)
{
	x = x;
}
#endif

/* printf 重定向：每个字符经 UART0 发送 */
int fputc(int ch, FILE *stream)
{
	(void)stream;
	// 发送前等待 UART 不忙，再写入发送数据寄存器
	while (DL_UART_isBusy(UART_0_INST) == true)
		;

	DL_UART_Main_transmitData(UART_0_INST, (uint8_t)ch);

	return ch;
}
