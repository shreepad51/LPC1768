#include<lpc17xx.h>
#include"lcd.h"
#include<stdio.h>
void uart_init(void);
void send_u_data(unsigned char data);
#define VREF 3.3
 void adc_init(void);
 int main(void)
 {
	  adc_init();
	  uart_init();
	 init_lcd();
	 unsigned char value[8];
	 float value1;
	 unsigned int i,j=0;
	 send_cmd(0x01);
	 send_cmd(0x80);
	unsigned char ptr[20]="value of adc=";
	 //	unsigned char str[100]="assignment";
//	 while(str[j] !='\n')
//{
//			send_u_data(str[j]);
//			j++; ooo
//}
	 int da = 0x0D;
	 int db=0x0A;
	 while(1)
	 {
		 while(!(LPC_ADC->ADSTAT & (1<<2)));
		 unsigned int data = (LPC_ADC->ADDR2)&(0x0000FFF0);
		 data = (data>>4);
		  value1 = (data*VREF)/4096.0;
		 		send_cmd(0x80);
		 user_string(ptr);
		 sprintf(value ,"%0.2fV\n" ,value1);
		 send_cmd(0xc0);
		 user_string(value);
		 for(i=0;i<7;i++)
		 {
			send_u_data(value[i]);
			
		} send_u_data(da);
		 send_u_data(db);
	}
}
 void adc_init(void)
 {
	 LPC_SC->PCONP |= (1<<12);
	 LPC_SC->PCLKSEL0 |= ~((1<<25)|(1<<24));
	 LPC_ADC->ADCR =(1<<2)|(1<<8)|(1<<16)|(1<<21);
	 LPC_PINCON->PINSEL1 |= (1<<18);
 }

void send_u_data(unsigned char data)
{
	while(!(LPC_UART0->LSR &(1<<5)));
	LPC_UART0->THR = data;
}
 	
void uart_init(void)
{
	LPC_SC->PCLKSEL0 = ~((1<<6)|(1<<7));
	LPC_PINCON->PINSEL0 = (1<<4)|(1<<6);
	LPC_UART0->LCR =(1<<0)|(1<<1)|(1<<7); //8 bit data 2 stop bit 
	LPC_UART0->DLL = 0xA2;//setting boud rate 
	LPC_UART0->DLM |=0x00; //DLM is 0
	LPC_UART0->LCR =(1<<1)|(1<<0); //DLAB clear bit
LPC_UART0->TER = (1<<7); //TXEN bit enable
LPC_UART0->FDR = (1<<4); //boud rate pre scaller multiplier value this field must be greater than 1
}	
	
		