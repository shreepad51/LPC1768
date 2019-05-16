#include"lpc17xx.h"
void timer_init(void);
void timer_delay(void);
void TIMER0_IRQHandler(void);
int flag = 0;
int main(void)
{
	timer_init();
	NVIC_EnableIRQ(TIMER0_IRQn);
	LPC_GPIO2->FIODIR = (1<<9);
	while(1)
	{
		LPC_GPIO2->FIOSET = (1<<9);
		timer_delay();
		LPC_GPIO2->FIOCLR = (1<<9);
		timer_delay();
		
	}
}
void timer_init(void)
{
	
	LPC_SC->PCON = (1<<1);
	LPC_SC->PCLKSEL0 = (1<<2);
	LPC_TIM0->IR = 0xff;
	LPC_TIM0->CTCR = 0x00;
	LPC_TIM0->MCR = (1<<1)|(1<<0);
	LPC_TIM0->PR = 60000;
	LPC_TIM0->MR0 = 1000;
	LPC_TIM0->TCR = (1<<1);
}
void timer_delay(void)
{
	LPC_TIM0->TCR = (1<<0);
	while((LPC_TIM0->TC) != (LPC_TIM0->MR0));
	LPC_TIM0->TCR = (1<<1);
	LPC_TIM0->TCR = ~(1<<0);
}
void TIMER0_IRQHandler(void)
{
	while((LPC_TIM0->IR & (1<<0))== (1<<0));
	LPC_GPIO2->FIODIR = (1<<11);
	if(flag==0)
	{
	LPC_GPIO2->FIOCLR = (1<<11);
		flag=1;
	}
	else
	{
		LPC_GPIO2->FIOSET = (1<<11);
	flag=0;
	}
	LPC_TIM0->IR = ~(1<<0);
}