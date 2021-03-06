/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Switch_ZF_Pin GPIO_PIN_13
#define Switch_ZF_GPIO_Port GPIOC
#define bb_Pin GPIO_PIN_1
#define bb_GPIO_Port GPIOA
#define Mode_Pin GPIO_PIN_2
#define Mode_GPIO_Port GPIOA
#define Mode_EXTI_IRQn EXTI2_IRQn
#define A_INTPUT_Pin GPIO_PIN_3
#define A_INTPUT_GPIO_Port GPIOA
#define A_INTPUT_EXTI_IRQn EXTI3_IRQn
#define B_INTPUT_Pin GPIO_PIN_4
#define B_INTPUT_GPIO_Port GPIOA
#define B_INTPUT_EXTI_IRQn EXTI4_IRQn
#define ADC_Pin GPIO_PIN_5
#define ADC_GPIO_Port GPIOA
#define CONTROL_I_Pin GPIO_PIN_6
#define CONTROL_I_GPIO_Port GPIOA
#define CONTROL_I_EXTI_IRQn EXTI9_5_IRQn
#define SLEEP_MODE_Pin GPIO_PIN_1
#define SLEEP_MODE_GPIO_Port GPIOB
#define PWM_OUT_Pin GPIO_PIN_15
#define PWM_OUT_GPIO_Port GPIOA
#define EN1_Pin GPIO_PIN_8
#define EN1_GPIO_Port GPIOB
#define EN2_Pin GPIO_PIN_9
#define EN2_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
