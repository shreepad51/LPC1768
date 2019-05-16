#include<lpc17xx.h>

void uart_init(void);
void send_data(unsigned char data);
unsigned char receive_data(void);


void send_u_data(unsigned char data)
{
	while(!(LPC_UART0->LSR &(1<<5)));
	LPC_UART0->THR = data;
}
unsigned char receive_data(void)
{
	while(!(LPC_UART0->LSR &(1<<0)));
	unsigned char data = LPC_UART0->RBR;
	return data;
}	
void uart_init(void)
{
	LPC_UART0->LCR =(1<<0)|(1<<1)|(1<<2); //8 bit data 2 stop bit 
	LPC_UART0->LCR |= (1<<7); //dlab set bit
	LPC_UART0->DLL = 223;//setting boud rate 
	LPC_UART0->DLM |=0x00; //DLM is 0
	LPC_UART0->LCR &=~(1<<7); //DLAB clear bit
LPC_UART0->TER = (1<<7); //TXEN bit enable
LPC_UART0->FDR = (1<<4); //boud rate pre scaller multiplier value this field must be greater than 1
}	
	
		