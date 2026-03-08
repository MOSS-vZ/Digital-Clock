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
 *  DO NOT EDIT - This file is generated for the MSPM0L130X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0L130X

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



/* Defines for PWM_0 */
#define PWM_0_INST                                                         TIMG2
#define PWM_0_INST_IRQHandler                                   TIMG2_IRQHandler
#define PWM_0_INST_INT_IRQN                                     (TIMG2_INT_IRQn)
#define PWM_0_INST_CLK_FREQ                                                 5000
/* GPIO defines for channel 0 */
#define GPIO_PWM_0_C0_PORT                                                 GPIOA
#define GPIO_PWM_0_C0_PIN                                          DL_GPIO_PIN_8
#define GPIO_PWM_0_C0_IOMUX                                       (IOMUX_PINCM9)
#define GPIO_PWM_0_C0_IOMUX_FUNC                      IOMUX_PINCM9_PF_TIMG2_CCP0
#define GPIO_PWM_0_C0_IDX                                    DL_TIMER_CC_0_INDEX



/* Defines for TIMER_0 */
#define TIMER_0_INST                                                     (TIMG0)
#define TIMER_0_INST_IRQHandler                                 TIMG0_IRQHandler
#define TIMER_0_INST_INT_IRQN                                   (TIMG0_INT_IRQn)
#define TIMER_0_INST_LOAD_VALUE                                         (39999U)
/* Defines for TIMER_1 */
#define TIMER_1_INST                                                     (TIMG1)
#define TIMER_1_INST_IRQHandler                                 TIMG1_IRQHandler
#define TIMER_1_INST_INT_IRQN                                   (TIMG1_INT_IRQn)
#define TIMER_1_INST_LOAD_VALUE                                         (39999U)



/* Defines for UART_0 */
#define UART_0_INST                                                        UART1
#define UART_0_INST_IRQHandler                                  UART1_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART1_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                        DL_GPIO_PIN_11
#define GPIO_UART_0_TX_PIN                                        DL_GPIO_PIN_10
#define GPIO_UART_0_IOMUX_RX                                     (IOMUX_PINCM12)
#define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM11)
#define GPIO_UART_0_IOMUX_RX_FUNC                      IOMUX_PINCM12_PF_UART1_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM11_PF_UART1_TX
#define UART_0_BAUD_RATE                                                (115200)
#define UART_0_IBRD_32_MHZ_115200_BAUD                                      (17)
#define UART_0_FBRD_32_MHZ_115200_BAUD                                      (23)





/* Port definition for Pin Group GPIO_GRP_0 */
#define GPIO_GRP_0_PORT                                                  (GPIOA)

/* Defines for CS: GPIOA.2 with pinCMx 3 on package pin 6 */
#define GPIO_GRP_0_CS_PIN                                        (DL_GPIO_PIN_2)
#define GPIO_GRP_0_CS_IOMUX                                       (IOMUX_PINCM3)
/* Defines for LED: GPIOA.25 with pinCMx 26 on package pin 29 */
#define GPIO_GRP_0_LED_PIN                                      (DL_GPIO_PIN_25)
#define GPIO_GRP_0_LED_IOMUX                                     (IOMUX_PINCM26)
/* Defines for D0: GPIOA.6 with pinCMx 7 on package pin 10 */
#define GPIO_GRP_0_D0_PIN                                        (DL_GPIO_PIN_6)
#define GPIO_GRP_0_D0_IOMUX                                       (IOMUX_PINCM7)
/* Defines for D1: GPIOA.5 with pinCMx 6 on package pin 9 */
#define GPIO_GRP_0_D1_PIN                                        (DL_GPIO_PIN_5)
#define GPIO_GRP_0_D1_IOMUX                                       (IOMUX_PINCM6)
/* Defines for DC: GPIOA.4 with pinCMx 5 on package pin 8 */
#define GPIO_GRP_0_DC_PIN                                        (DL_GPIO_PIN_4)
#define GPIO_GRP_0_DC_IOMUX                                       (IOMUX_PINCM5)
/* Port definition for Pin Group KEY */
#define KEY_PORT                                                         (GPIOA)

/* Defines for H1: GPIOA.0 with pinCMx 1 on package pin 1 */
#define KEY_H1_PIN                                               (DL_GPIO_PIN_0)
#define KEY_H1_IOMUX                                              (IOMUX_PINCM1)
/* Defines for H2: GPIOA.1 with pinCMx 2 on package pin 2 */
#define KEY_H2_PIN                                               (DL_GPIO_PIN_1)
#define KEY_H2_IOMUX                                              (IOMUX_PINCM2)
/* Defines for H3: GPIOA.7 with pinCMx 8 on package pin 11 */
#define KEY_H3_PIN                                               (DL_GPIO_PIN_7)
#define KEY_H3_IOMUX                                              (IOMUX_PINCM8)
/* Defines for H4: GPIOA.12 with pinCMx 13 on package pin 16 */
#define KEY_H4_PIN                                              (DL_GPIO_PIN_12)
#define KEY_H4_IOMUX                                             (IOMUX_PINCM13)
/* Defines for V1: GPIOA.13 with pinCMx 14 on package pin 17 */
#define KEY_V1_PIN                                              (DL_GPIO_PIN_13)
#define KEY_V1_IOMUX                                             (IOMUX_PINCM14)
/* Defines for V2: GPIOA.14 with pinCMx 15 on package pin 18 */
#define KEY_V2_PIN                                              (DL_GPIO_PIN_14)
#define KEY_V2_IOMUX                                             (IOMUX_PINCM15)
/* Defines for V3: GPIOA.17 with pinCMx 18 on package pin 21 */
#define KEY_V3_PIN                                              (DL_GPIO_PIN_17)
#define KEY_V3_IOMUX                                             (IOMUX_PINCM18)
/* Defines for V4: GPIOA.18 with pinCMx 19 on package pin 22 */
#define KEY_V4_PIN                                              (DL_GPIO_PIN_18)
#define KEY_V4_IOMUX                                             (IOMUX_PINCM19)
/* Port definition for Pin Group BUZZER */
#define BUZZER_PORT                                                      (GPIOA)

/* Defines for PIN_0: GPIOA.15 with pinCMx 16 on package pin 19 */
#define BUZZER_PIN_0_PIN                                        (DL_GPIO_PIN_15)
#define BUZZER_PIN_0_IOMUX                                       (IOMUX_PINCM16)

/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_PWM_0_init(void);
void SYSCFG_DL_TIMER_0_init(void);
void SYSCFG_DL_TIMER_1_init(void);
void SYSCFG_DL_UART_0_init(void);



#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
