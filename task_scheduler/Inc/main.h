/*
 * main.h
 *
 *  Created on: Sep 11, 2023
 *      Author: ryanjackson
 */

#ifndef MAIN_H_
#define MAIN_H_

#define MAX_TASKS			4

#define SIZE_TASK_STACK		1024U
#define SIZE_SCHD_STACK		1024U

#define SRAM_START			0x20000000U
#define SIZE_RAM			((128) * (1024))
#define SRAM_END			((SRAM_START) + (SIZE_RAM))

#define T1_STACK_START		SRAM_END
#define T2_STACK_START		(SRAM_END - SIZE_TASK_STACK)
#define T3_STACK_START		(SRAM_END - (2 * SIZE_TASK_STACK))
#define T4_STACK_START		(SRAM_END - (3 * SIZE_TASK_STACK))
#define SCHD_STACK_START	(SRAM_END - (4 * SIZE_TASK_STACK))

#define TICK_HZ				1000U

#define HSI_CLOCK			16000000U
#define SYSTICK_TIM_CLK		HSI_CLOCK

#define DUMMY_XPSR	0x01000000U;

#endif /* MAIN_H_ */
