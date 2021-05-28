/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "moto.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

int pwm_mode0 = 0;    		//pwm����
int pwm_mode1_ang = 0;  	//pwm����
int pwm_mode1_sp = 0;     //pwm����
int mode = -1;            //ģʽ0��1 -1Ϊ�޲���
int target_speed = 5*390; //Ŀ���ٶȣ�����/��
int target_angel_1 = 160; //Ŀ��Ȧ��
int target_angel_2 = 530; //Ŀ��Ȧ��1m
int target_speed_1 = 0.3*390;
int uart_sent_times = 0;  //����ʱ��
int stateZF = 0;          //�������
float ADC = 0;       //ADCֵ 

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */
int fputc(int ch, FILE *f){
	uint8_t temp[1] = {ch};
	HAL_UART_Transmit(&huart1, temp, 1, 2);//huart1��Ҫ������������޸�
	return ch;
}
/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_ADC1_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  MX_USART1_UART_Init();
  /* USER CODE BEGIN 2 */
	HAL_TIM_Base_Start_IT(&htim1);
	HAL_ADCEx_Calibration_Start(&hadc1);
	
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB busses clocks 
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_ADC;
  PeriphClkInit.AdcClockSelection = RCC_ADCPCLK2_DIV6;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/*********************/
void BeforeSleep(void){                                         //����״̬ǰ׼��
	__HAL_RCC_APB2_FORCE_RESET();
	__HAL_RCC_PWR_CLK_ENABLE();
	__HAL_PWR_CLEAR_FLAG(PWR_FLAG_WU);
	HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1);
}

void SwitchZF(void){                                            //�л��������
	HAL_GPIO_WritePin(EN1_GPIO_Port,EN1_Pin,GPIO_PIN_SET);
	HAL_GPIO_WritePin(EN2_GPIO_Port,EN2_Pin,GPIO_PIN_SET);
	HAL_Delay(10);
	if(stateZF == 0){
		HAL_GPIO_WritePin(EN1_GPIO_Port,EN1_Pin,GPIO_PIN_SET);
		HAL_GPIO_WritePin(EN2_GPIO_Port,EN2_Pin,GPIO_PIN_RESET);
	}
	else if(stateZF == 1){
		HAL_GPIO_WritePin(EN1_GPIO_Port,EN1_Pin,GPIO_PIN_RESET);
		HAL_GPIO_WritePin(EN2_GPIO_Port,EN2_Pin,GPIO_PIN_SET);
	}
}

/*********************/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {          
  if(GPIO_Pin == A_INTPUT_Pin) {                                //��⵽���AB���������ػ��½��ؾ�����һ�Σ���4��Ƶ
		if(mode == 0)
			pwm_mode0++;
  }
	
	else if(GPIO_Pin == B_INTPUT_Pin){                            //��⵽���AB���������ػ��½��ؾ�����һ�Σ���4��Ƶ
		if(mode == 0)
			pwm_mode0++;
	}
	
	else if(GPIO_Pin == Mode_Pin){
		HAL_Delay(10);                                               //����
		if(HAL_GPIO_ReadPin(Mode_GPIO_Port,Mode_Pin) == GPIO_PIN_SET){     //�л�ģʽ����5
			mode = 0;
		}
		else if(HAL_GPIO_ReadPin(Mode_GPIO_Port,Mode_Pin) == SET){  //�л�ģʽ����6
			mode = 1;
		}
	}
	
	else if(GPIO_Pin == SLEEP_MODE_Pin){                          //��������״̬
		HAL_Delay(3000);                                            //�������ӳ�
		if(HAL_GPIO_ReadPin(Mode_GPIO_Port,Mode_Pin) == GPIO_PIN_SET){
			BeforeSleep();
			HAL_PWR_EnterSTANDBYMode();
		}
	}
	
	else if(GPIO_Pin == CONTROL_I_Pin){                           //��6����Ƶ����
		if(mode == 1)
			pwm_mode1_ang++;
			pwm_mode1_sp++;
	}
	else if(GPIO_Pin == Switch_ZF_Pin){                           //�л��������
		HAL_Delay(10);                                              //�������ӳ�
		if(HAL_GPIO_ReadPin(Mode_GPIO_Port,Mode_Pin) == GPIO_PIN_SET){
			stateZF = !stateZF;
			SwitchZF();
		}

	}
}

/*********************/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	if (htim->Instance == htim1.Instance) {
		if(mode != -1){
			HAL_TIM_PWM_Start(&htim2,TIM_CHANNEL_1);                //����PWM���
			if(mode == 0){
				int pwm = (float)calculate_speed(pwm_mode0)/4.0;      //�õ�Ƶ�� ��4Ϊ��ԭԭƵ��
				pwm_mode0 = 0;																				//���õ��ٶ�
				float speed = pwm;                              //ÿȦ390������
				mode_0(target_speed,speed);                           //ģʽ0����
				uint8_t speed_out = (float)((int)speed*100)/100.0;    //ʣ��λС��
			}
			else if(mode == 1){
				int pwm_ang = (float)calculate_speed(pwm_mode1_ang)/2.0;       //�õ�Ƶ�� ��4Ϊ��ԭԭƵ��
				float angel = pwm_ang/2.0;                                     //ÿȦ2������
        int pwm_sp = (float)calculate_speed(pwm_mode1_sp)/2.0;         //�õ�Ƶ�� ��4Ϊ��ԭԭƵ��
				pwm_mode1_sp = 0;																				       //���õ��ٶ�
				float speed = pwm_sp/2.0;   
				mode_1(target_angel_1,target_angel_2,angel,target_speed_1,speed);            //ģʽ1����
			}
		}
		if(uart_sent_times == 100){
			HAL_ADC_Start(&hadc1);                             //����ADC
			HAL_ADC_PollForConversion(&hadc1, 5);              //��ȡADC��ֵ��ʱ��5ms  ʵ��ʱ��12Mhz/14
			ADC += HAL_ADC_GetValue(&hadc1);              //��¼������
			float ADCvalue = ADC*3.3/4096;                //���ѹ
			printf("%.4f/n",ADCvalue/5.0);										 //�����������
			uart_sent_times = 0;
		}
//		else if(uart_sent_times > 96){
//			HAL_ADC_Start(&hadc1);                             //����ADC
//			HAL_ADC_PollForConversion(&hadc1, 5);              //��ȡADC��ֵ��ʱ��5ms  ʵ��ʱ��12Mhz/14
//			temp_ADC += HAL_ADC_GetValue(&hadc1);              //��¼������
//		}
	}
}

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */

  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{ 
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     tex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/