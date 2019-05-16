#include"lpc17xx.h"
void timer_delay(void);
void timer_init(void){
		LPC_SC->PCON = (1<<1);
	LPC_SC->PCLKSEL0 = (1<<2);
	LPC_TIM0->MCR = (1<<1);//rsest m0
	LPC_TIM0->PR = 60000; //maximum count
	LPC_TIM0->MR0 =1000;  //reset on match
}





void timer_delay(void)
{
	LPC_TIM0->TCR = (1<<0); //enable timer
	while((LPC_TIM0->TC)!=(LPC_TIM0->MR0));
	LPC_TIM0->TCR= (1<<1); //reset timer
	LPC_TIM0->TCR = ~(1<<0);
}
int main(void)
{
		

timer_init();
		LPC_GPIO2->FIODIR = (1<<9);
	while(1)
	{
		LPC_GPIO2->FIOCLR = (1<<9);
		timer_delay();

		LPC_GPIO2->FIOSET = (1<<9);
		timer_delay();
	}
}