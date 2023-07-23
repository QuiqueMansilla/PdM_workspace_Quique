/*
 * API_debounce.c
 *
 *  Created on: Jul 14, 2023
 *      Author: quique
 */

/*Includes*/
#include "main.h"
#include "API_debounce.h"
#include "API_delay.h"

/*Private Defines ------------------------------------------------------------*/
#define DEBUNCE_DELAY 40

/* Private variables ---------------------------------------------------------*/
/*Variable de estado que tomará unos de os 4 estados definidos en debounceState_t*/
static debounceState_t stateMEF;
static delay_t debounceDelay;
static bool_t buttonRead = true;

/* USER CODE BEGIN EFP */
void debounceMEF_Init(void)
{
	stateMEF = BUTTON_UP;
	/*Asume el uso de USER_Btn_Pin con su configuracion en main.c, se prevé agregar
	 * código para poder inicializar eluso de otro pin de entrada conectado a un
	 * pulsador externo*/
	delayInit(*debounceDelay, DEBUNCE_DELAY);
}

void debounceMEF_Update(void)
{
	switch(stateMEF);
	{
	case BUTTON_UP:
		/*Actualiza salida de este estado*/
		HAL_GPIO_WritePin(GPIOB, LD1_Pin|LD3_Pin|LD2_Pin, GPIO_PIN_RESET);
		/*Chequea condicion de transicion*/
		buttonRead = HAL_GPIO_ReadPin(GPIOC, USER_Btn_Pin);
		if (buttonRead == false)
		{
			delayRead(*debounceDelay);/*Inicia cuenta de DEBUNCE_DELAY*/
			stateMEF = BUTTON_FALLING; /*Cambio al siguiente estado*/
		}
	break;

	case BUTTON_FALLING:
		/*Actualiza salida de este estado*/
		//HAL_GPIO_WritePin(GPIOB, LD1_Pin|LD3_Pin|LD2_Pin, GPIO_PIN_RESET);
		/*Chequea condicion de transicion*/
		buttonRead = HAL_GPIO_ReadPin(GPIOC, USER_Btn_Pin);
		if ((buttonRead == false) && (delayRead(*debounceDelay)))
		{
			/*Dispara la condicion para buttonPressed()*/;
			stateMEF = BUTTON_DOWN; /*Cambio al siguiente estado*/
		}
		stateMEF = BUTTON_UP; /*Cambio al estado anterior*/
	break;

	case BUTTON_DOWN:
		/*Chequea condicion de transicion*/
		buttonRead = HAL_GPIO_ReadPin(GPIOC, USER_Btn_Pin);
		if (buttonRead == false)
		{
			delayRead(*debounceDelay); /*inicia cuenta de DEBUNCE_DELAY*/
			/*Dispara la condicion para buttonPressed()*/
			stateMEF = BUTTON_RAISING; /*Cambio al siguiente estado*/
		}
	break;

	case BUTTON_RAISING:
		/*Chequea condicion de transicion*/
		buttonRead = HAL_GPIO_ReadPin(GPIOC, USER_Btn_Pin);
		if ((buttonRead == true) && (delayRead(*debounceDelay)))
		{
			/*Dispara la condicion para buttonReleassed()*/
			stateMEF = BUTTON_UP; /*Cambio al siguiente estado*/
		}
		stateMEF = BUTTON_DOWN; /*Cambio al estado anterior*/
	break;

	default:
		Error_Handler();
	break;
	}
}
void debouncePressed(void)
{
	HAL_GPIO_TogglePin(GPIOB, LD1_Pin);
}

void debounceReleased(void)
{
	HAL_GPIO_TogglePin(GPIOB, LD3_Pin);
}
/* USER CODE END EFP */
