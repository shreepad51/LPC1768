#include<lpc17xx.h>
void EINT2_IRQHandler(void);
void ext_int(void);
void ext_int(void)
{
	LPC_PINCON->PINSEL4 = (1<<24)|(0<<25);
	LPC_SC->EXTINT = (1<<2);
	LPC_SC->EXTMODE = (1<<2);
	LPC_SC->EXTPOLAR = (1<<2);
}
void EINT2_IRQHandler(void)
{
	LPC_SC->EXTINT = (1<<2);
	LPC_GPIO2->FIOCLR = (1<<9);
}
int main(void)
{
	ext_int();
	NVIC_EnableIRQ(EINT2_IRQn);
	LPC_GPIO2->FIODIR = (1<<9);
	LPC_GPIO2->FIOSET = (1<<9);
	while(1);
}
