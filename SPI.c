#include"lpc17xx.h"
void SPI_init(void);
void DELAY(unsigned TIME);
void DATA(unsigned int data);

void SPI_init(void)
{
		LPC_SC->PCONP |=(1<<8);
	LPC_PINCON->PINSEL0 |=(1<<31)|(1<<30);  //for select the sck of spi bus 
	LPC_PINCON->PINSEL1 |= (1<<3)|(1<<2)|(1<<5)|(1<<4);//|(1<<1)|(0<<0);  //for select ssel0,and mosi0 for spi 0
	//LPC_SC->PCLKSEL0 |= (0<<17)|(1<<16);

	LPC_SPI->SPCR |=(1<<5)|(1<<6);
	//LPC_SPI->SPCR |=0X00;
	LPC_SPI->SPCCR |= 0x0E;
	LPC_GPIO0->FIODIR |=(1<<16);
	//LPC_GPIO0->FIOSET |=(1<<16);
//	LPC_GPIO0->FIOSET |= (1<<16);
	
	
}
void DELAY(unsigned TIME)
{
	int i,j;
	for(i=0;i<10000;i++)
	for(j=0;j<TIME;j++);
}
void DATA(unsigned int data)
{
	LPC_GPIO0->FIOSET |=(1<<16);
	LPC_SPI->SPDR |=data;
	while(!(LPC_SPI->SPSR & (1<<7)));
	LPC_GPIO0->FIOCLR = (1<<16);
	//int i = LPC_SPI->SPDR;
	//int j = LPC_SPI->SPSR;
}
int main(void)
{
	//LPC_GPIO2->FIODIR |=(1<<9);
	SPI_init();
	while(1){
		DATA(0xAA);
		DELAY(2000);
		DATA(0x55);
		DELAY(2000);
			
}
}
