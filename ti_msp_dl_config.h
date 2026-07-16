/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
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

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X
#define CONFIG_MSPM0G3507

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)



#define CPUCLK_FREQ                                                     32000000



/* Defines for PWM */
#define PWM_INST                                                           TIMG6
#define PWM_INST_IRQHandler                                     TIMG6_IRQHandler
#define PWM_INST_INT_IRQN                                       (TIMG6_INT_IRQn)
#define PWM_INST_CLK_FREQ                                                1000000
/* GPIO defines for channel 0 */
#define GPIO_PWM_C0_PORT                                                   GPIOB
#define GPIO_PWM_C0_PIN                                            DL_GPIO_PIN_2
#define GPIO_PWM_C0_IOMUX                                        (IOMUX_PINCM15)
#define GPIO_PWM_C0_IOMUX_FUNC                       IOMUX_PINCM15_PF_TIMG6_CCP0
#define GPIO_PWM_C0_IDX                                      DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_PWM_C1_PORT                                                   GPIOB
#define GPIO_PWM_C1_PIN                                            DL_GPIO_PIN_3
#define GPIO_PWM_C1_IOMUX                                        (IOMUX_PINCM16)
#define GPIO_PWM_C1_IOMUX_FUNC                       IOMUX_PINCM16_PF_TIMG6_CCP1
#define GPIO_PWM_C1_IDX                                      DL_TIMER_CC_1_INDEX



/* Defines for TIMER_0 */
#define TIMER_0_INST                                                     (TIMA0)
#define TIMER_0_INST_IRQHandler                                 TIMA0_IRQHandler
#define TIMER_0_INST_INT_IRQN                                   (TIMA0_INT_IRQn)
#define TIMER_0_INST_LOAD_VALUE                                           (399U)
/* Defines for TIMER_1 */
#define TIMER_1_INST                                                     (TIMG0)
#define TIMER_1_INST_IRQHandler                                 TIMG0_IRQHandler
#define TIMER_1_INST_INT_IRQN                                   (TIMG0_INT_IRQn)
#define TIMER_1_INST_LOAD_VALUE                                           (399U)



/* Defines for UART_0 */
#define UART_0_INST                                                        UART0
#define UART_0_INST_FREQUENCY                                           32000000
#define UART_0_INST_IRQHandler                                  UART0_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                         DL_GPIO_PIN_1
#define GPIO_UART_0_TX_PIN                                         DL_GPIO_PIN_0
#define GPIO_UART_0_IOMUX_RX                                      (IOMUX_PINCM2)
#define GPIO_UART_0_IOMUX_TX                                      (IOMUX_PINCM1)
#define GPIO_UART_0_IOMUX_RX_FUNC                       IOMUX_PINCM2_PF_UART0_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                       IOMUX_PINCM1_PF_UART0_TX
#define UART_0_BAUD_RATE                                                (115200)
#define UART_0_IBRD_32_MHZ_115200_BAUD                                      (17)
#define UART_0_FBRD_32_MHZ_115200_BAUD                                      (23)





/* Port definition for Pin Group BEEP */
#define BEEP_PORT                                                        (GPIOA)

/* Defines for ONE: GPIOA.23 with pinCMx 53 on package pin 24 */
#define BEEP_ONE_PIN                                            (DL_GPIO_PIN_23)
#define BEEP_ONE_IOMUX                                           (IOMUX_PINCM53)
/* Port definition for Pin Group LED */
#define LED_PORT                                                         (GPIOA)

/* Defines for BLUE: GPIOA.26 with pinCMx 59 on package pin 30 */
#define LED_BLUE_PIN                                            (DL_GPIO_PIN_26)
#define LED_BLUE_IOMUX                                           (IOMUX_PINCM59)
/* Defines for GREEN: GPIOA.28 with pinCMx 3 on package pin 35 */
#define LED_GREEN_PIN                                           (DL_GPIO_PIN_28)
#define LED_GREEN_IOMUX                                           (IOMUX_PINCM3)
/* Defines for LapNum: GPIOA.2 with pinCMx 7 on package pin 42 */
#define KEY_LapNum_PORT                                                  (GPIOA)
#define KEY_LapNum_PIN                                           (DL_GPIO_PIN_2)
#define KEY_LapNum_IOMUX                                          (IOMUX_PINCM7)
/* Defines for TaskNum: GPIOA.31 with pinCMx 6 on package pin 39 */
#define KEY_TaskNum_PORT                                                 (GPIOA)
#define KEY_TaskNum_PIN                                         (DL_GPIO_PIN_31)
#define KEY_TaskNum_IOMUX                                         (IOMUX_PINCM6)
/* Defines for TotalStart: GPIOB.9 with pinCMx 26 on package pin 61 */
#define KEY_TotalStart_PORT                                              (GPIOB)
#define KEY_TotalStart_PIN                                       (DL_GPIO_PIN_9)
#define KEY_TotalStart_IOMUX                                     (IOMUX_PINCM26)
/* Port definition for Pin Group Motor_left */
#define Motor_left_PORT                                                  (GPIOB)

/* Defines for AIN1: GPIOB.15 with pinCMx 32 on package pin 3 */
#define Motor_left_AIN1_PIN                                     (DL_GPIO_PIN_15)
#define Motor_left_AIN1_IOMUX                                    (IOMUX_PINCM32)
/* Defines for AIN2: GPIOB.17 with pinCMx 43 on package pin 14 */
#define Motor_left_AIN2_PIN                                     (DL_GPIO_PIN_17)
#define Motor_left_AIN2_IOMUX                                    (IOMUX_PINCM43)
/* Port definition for Pin Group Motor_right */
#define Motor_right_PORT                                                 (GPIOB)

/* Defines for BIN1: GPIOB.13 with pinCMx 30 on package pin 1 */
#define Motor_right_BIN1_PIN                                    (DL_GPIO_PIN_13)
#define Motor_right_BIN1_IOMUX                                   (IOMUX_PINCM30)
/* Defines for BIN2: GPIOB.16 with pinCMx 33 on package pin 4 */
#define Motor_right_BIN2_PIN                                    (DL_GPIO_PIN_16)
#define Motor_right_BIN2_IOMUX                                   (IOMUX_PINCM33)
/* Port definition for Pin Group Encoder_left */
#define Encoder_left_PORT                                                (GPIOB)

/* Defines for E1A: GPIOB.4 with pinCMx 17 on package pin 52 */
// groups represented: ["Encoder_right","Encoder_left"]
// pins affected: ["E2A","E2B","E1A","E1B"]
#define GPIO_MULTIPLE_GPIOB_INT_IRQN                            (GPIOB_INT_IRQn)
#define GPIO_MULTIPLE_GPIOB_INT_IIDX            (DL_INTERRUPT_GROUP1_IIDX_GPIOB)
#define Encoder_left_E1A_IIDX                                (DL_GPIO_IIDX_DIO4)
#define Encoder_left_E1A_PIN                                     (DL_GPIO_PIN_4)
#define Encoder_left_E1A_IOMUX                                   (IOMUX_PINCM17)
/* Defines for E1B: GPIOB.5 with pinCMx 18 on package pin 53 */
#define Encoder_left_E1B_IIDX                                (DL_GPIO_IIDX_DIO5)
#define Encoder_left_E1B_PIN                                     (DL_GPIO_PIN_5)
#define Encoder_left_E1B_IOMUX                                   (IOMUX_PINCM18)
/* Port definition for Pin Group Encoder_right */
#define Encoder_right_PORT                                               (GPIOB)

/* Defines for E2A: GPIOB.23 with pinCMx 51 on package pin 22 */
#define Encoder_right_E2A_IIDX                              (DL_GPIO_IIDX_DIO23)
#define Encoder_right_E2A_PIN                                   (DL_GPIO_PIN_23)
#define Encoder_right_E2A_IOMUX                                  (IOMUX_PINCM51)
/* Defines for E2B: GPIOB.12 with pinCMx 29 on package pin 64 */
#define Encoder_right_E2B_IIDX                              (DL_GPIO_IIDX_DIO12)
#define Encoder_right_E2B_PIN                                   (DL_GPIO_PIN_12)
#define Encoder_right_E2B_IOMUX                                  (IOMUX_PINCM29)
/* Defines for IO_0: GPIOA.27 with pinCMx 60 on package pin 31 */
#define Gray_IO_0_PORT                                                   (GPIOA)
#define Gray_IO_0_PIN                                           (DL_GPIO_PIN_27)
#define Gray_IO_0_IOMUX                                          (IOMUX_PINCM60)
/* Defines for IO_1: GPIOB.25 with pinCMx 56 on package pin 27 */
#define Gray_IO_1_PORT                                                   (GPIOB)
#define Gray_IO_1_PIN                                           (DL_GPIO_PIN_25)
#define Gray_IO_1_IOMUX                                          (IOMUX_PINCM56)
/* Defines for IO_2: GPIOB.20 with pinCMx 48 on package pin 19 */
#define Gray_IO_2_PORT                                                   (GPIOB)
#define Gray_IO_2_PIN                                           (DL_GPIO_PIN_20)
#define Gray_IO_2_IOMUX                                          (IOMUX_PINCM48)
/* Defines for IO_3: GPIOA.14 with pinCMx 36 on package pin 7 */
#define Gray_IO_3_PORT                                                   (GPIOA)
#define Gray_IO_3_PIN                                           (DL_GPIO_PIN_14)
#define Gray_IO_3_IOMUX                                          (IOMUX_PINCM36)
/* Defines for IO_4: GPIOA.16 with pinCMx 38 on package pin 9 */
#define Gray_IO_4_PORT                                                   (GPIOA)
#define Gray_IO_4_PIN                                           (DL_GPIO_PIN_16)
#define Gray_IO_4_IOMUX                                          (IOMUX_PINCM38)
/* Defines for IO_5: GPIOA.15 with pinCMx 37 on package pin 8 */
#define Gray_IO_5_PORT                                                   (GPIOA)
#define Gray_IO_5_PIN                                           (DL_GPIO_PIN_15)
#define Gray_IO_5_IOMUX                                          (IOMUX_PINCM37)
/* Defines for IO_6: GPIOA.10 with pinCMx 21 on package pin 56 */
#define Gray_IO_6_PORT                                                   (GPIOA)
#define Gray_IO_6_PIN                                           (DL_GPIO_PIN_10)
#define Gray_IO_6_IOMUX                                          (IOMUX_PINCM21)
/* Defines for IO_7: GPIOA.11 with pinCMx 22 on package pin 57 */
#define Gray_IO_7_PORT                                                   (GPIOA)
#define Gray_IO_7_PIN                                           (DL_GPIO_PIN_11)
#define Gray_IO_7_IOMUX                                          (IOMUX_PINCM22)




/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_PWM_init(void);
void SYSCFG_DL_TIMER_0_init(void);
void SYSCFG_DL_TIMER_1_init(void);
void SYSCFG_DL_UART_0_init(void);

void SYSCFG_DL_SYSTICK_init(void);

bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
