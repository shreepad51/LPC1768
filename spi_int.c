#include<lpc17xx.h>
void spi_init(void);
void spi_data(unsigned int data);
void delay_timer(unsigned int time);
void SPI_IRQnHandler(void);
void timer_init(void);
void timer0IRQ(void);


int main(void)
{
//	timer_init();
	spi_init();
		
	//NVIC_EnableIRQ(TIMER0_IRQn);
	//NVIC_EnableIRQ(SPI_IRQn);
	//NVIC_SetPriority(SPI_IRQn,1);
	LPC_GPIO0->FIODIR = (1<<9);
   LPC_GPIO0->FIOSET = (1<<9);
	while(1)
	{
		spi_data(0xF0);
		delay_timer(1000);
		spi_data(0x00);
		delay_timer(1000);
	}
}
void spi_init(void)
{
	LPC_SC->PCONP = (1<<8);
	LPC_SC->PCLKSEL0 = (1<<16)|(0<<17);
	LPC_PINCON->PINSEL0 = (1<<31)|(1<<30);
	LPC_PINCON->PINSEL1 = (1<<4)|(1<<5);
	LPC_SPI->SPCR = (1<<5)|(1<<6);
	LPC_SPI->SPCCR = 0x0A;
	LPC_GPIO0->FIODIR = (1<<16);
	
}
void spi_data(unsigned int data)
{
	int j;
	LPC_GPIO0->FIOSET = (1<<16);
	LPC_SPI->SPDR = data;
	while(!(LPC_SPI->SPSR & (1<<7)));
	LPC_GPIO0->FIOCLR = (1<<16);
		//j=LPC_SPI->SPDR;// After every transmit the SPI also clocks in a data byte, which you have to clear with a dummy read.
	//	j=LPC_SPI->SPSR;
}
/*void SPI_IRQnHandler(void)
{
	int j;
	while((LPC_SPI->SPINT & (1<<0))==(1<<0));
	LPC_GPIO0->FIOCLR = (1<<9);
		j=LPC_SPI->SPDR;// After every transmit the SPI also clocks in a data byte, which you have to clear with a dummy read.
		j=LPC_SPI->SPSR;
}*/
/*void timer_init(void)
{
	LPC_SC->PCON = (1<<1);
	LPC_SC->PCLKSEL0 = (1<<2);
	LPC_TIM0->MCR = (1<<1);
	LPC_TIM0->PR = 60000;
	LPC_TIM0->MR0 = 1000;
	

	//NVIC_SetPriority(TIMER0_IRQn,0);
}
void TIMER0_IRQHandler(void)
{
		while((LPC_TIM0->IR&(1<<0)) == (1<<0));
	LPC_GPIO2->FIODIR = (1<<11);
	LPC_GPIO2->FIOCLR = (1<<11);
	delay_timer();
	LPC_GPIO2->FIOSET = (1<<11);
	LPC_TIM0->IR |= (1<<0);
}

void delay_timer(void)
{
	LPC_TIM0->TCR = (1<<0);
   while((LPC_TIM0->TC)!=(LPC_TIM0->MR0));
  LPC_TIM0->TCR = (1<<1);
  LPC_TIM0->TCR = ~(1<<0);
}	*/
void delay_timer(unsigned int time)
{
	int i,j;
	for(i=0;i<10000;i++)
	for(j=0;j<time;j++);
}