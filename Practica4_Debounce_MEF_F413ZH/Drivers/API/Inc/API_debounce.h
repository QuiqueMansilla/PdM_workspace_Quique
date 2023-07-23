/*
 * API_debounce.h
 *
 *  Created on: Jul 14, 2023
 *      Author: quique
 */

#ifndef API_INC_API_DEBOUNCE_H_
#define API_INC_API_DEBOUNCE_H_



#endif /* API_INC_API_DEBOUNCE_H_ */

/*Includes*/
#include "main.h"

/* Exported types ------------------------------------------------------------*/
/*Enumeracion con tipo de datos que indican estado de MEF para debounce*/
typedef enum{
		BUTTON_UP,
		BUTTON_FALLING,
		BUTTON_DOWN,
		BUTTON_RAISING
		} debounceState_t;

delay_t debounce_Delay;
/* Exported functions prototypes ---------------------------------------------*/
/*void Error_Handler(void);*/

/* USER CODE BEGIN EFP */
void debounceMEF_Init(void);
void debounceMEF_Update(void);
void debouncePressed(void);
void debounceReleased(void);
/* USER CODE END EFP */
