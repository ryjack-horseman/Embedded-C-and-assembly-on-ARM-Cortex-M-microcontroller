/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2023 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
#define IRQNO_TIMER2	28
#define IRQNO_I2C1		31

#include <stdint.h>
#include <stdio.h>

void configure_priority_for_irqs(uint8_t, uint8_t);

uint32_t *pNVIC_IPRBase = (uint32_t *) 0xE000E400;
uint32_t *pNVIC_ISERBase = (uint32_t *) 0xE000E100;
uint32_t *pNVIC_ISPRBase = (uint32_t *) 0xE000E200;

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

int main(void)
{
	//1. configure priority for peripherals
	configure_priority_for_irqs(IRQNO_TIMER2, 0x80);
	configure_priority_for_irqs(IRQNO_I2C1, 0x80);

	//2. Set interrupt pending bit in NVIC
	//manually pend the pending bit for the  USART3 IRQ number in NVIC
	*pNVIC_ISPRBase |= (1 << (IRQNO_TIMER2 % 32));

	//3. Enable the IRQs in ISER
	//Enable the USART3 IRQ number in NVIC
	*pNVIC_ISERBase |= (1 << (IRQNO_TIMER2 % 32));
	*pNVIC_ISERBase |= (1 << (IRQNO_I2C1 % 32));
    /* Loop forever */
	for(;;);
}

void configure_priority_for_irqs(uint8_t irq_no, uint8_t priority_value){
	uint8_t iprx = irq_no / 4;
	uint32_t *ipr = pNVIC_IPRBase + iprx;

	uint8_t pos = (irq_no % 4) * 8;

	*ipr &= ~(0xFF << pos);
	*ipr |= (priority_value << pos);
}

void I2C2_EV_IRQHandler(void){
	printf("in I2C2 isr\n");
}

void TIM2_IRQHandler(void){
	printf("in TIM2 isr\n");
	*pNVIC_ISPRBase |= (1 << (IRQNO_I2C1 % 32));
}
