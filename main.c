#include "main.h"

void SystemClock_Config(void);

void gpo_config (void)
{
	  RCC->AHBENR |=RCC_AHBENR_GPIOEEN;		//Įjungiama MCU periferija per RCC registrus

	  GPIOE->MODER |= GPIO_MODER_MODER9_1;		//Nustatomi GPIO registrai LED įjungimui
	  GPIOE->MODER &= ~GPIO_MODER_MODER9_0;		//Nustatomi GPIO registrai LED išjungimui

	  GPIOE->AFR[1] |=0b00100000;		//Nustato 9 piną

}

void delay(int time_cycle)		//Void funkcija, kuri sukuria delay
{
	for(int i = 0; i < time_cycle;i++)	//Tuščias for ciklas
	{
	}
}

void timer_config (int brightness)			//Nustatomi Timer registrai - PWM mode
   {
   		RCC->APB2ENR |=RCC_APB2ENR_TIM1EN;	//TIM1 timer clock enable
   		TIM1->CCMR1 |= TIM_CCMR1_OC1PE;		//preload enable
   		TIM1->CR1 |= TIM_CR1_ARPE;			//auto-reload preload enable
   		TIM1->CCMR1 &= ~TIM_CCMR1_OC1M_0;
   		TIM1->CCMR1 |= TIM_CCMR1_OC1M_1;
   		TIM1->CCMR1 |= TIM_CCMR1_OC1M_2;
   		TIM1->CCMR1 &= ~TIM_CCMR1_OC1M_3;
   		TIM1-> ARR = 100;
   		TIM1-> CCR1 = brightness;
   		TIM1-> BDTR |= TIM_BDTR_MOE;		//Main output enable
   		TIM1-> CCER |= TIM_CCER_CC1E;		//Enable output pirmam kanalui
   		TIM1-> CR1 |= TIM_CR1_CEN;			//Counter enable
   }

int main(void)
{
	gpo_config();		//Iškviečiama funkcija GPIO registrams nustatyti

while(1)
{								//Keičiamas impulso plotis per timer_config funkciją
	for(int i =0; i<=100; i++)
	{
		timer_config(i);		//Ryškina diodą, nes paduodamas kintamasis i didėja
		delay(10000);
	}
	for(int i=100; i>=0; i--)
		{
			timer_config(i);	//Gesina diodą, nes paduodamas kintamasis i mažėja
			delay(10000);
		}
}

}
