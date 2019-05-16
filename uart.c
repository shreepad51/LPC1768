#include"lpc17xx.h"
void uart_init(void);
unsigned char uart_rx_data(void);
void uart_tx_data(unsigned char data);
	
	
void uart_tx_data(unsigned char data)
{
	while(!(LPC_UART0->LSR & (1<<5)));
	LPC_UART0->THR = data;
}
unsigned char uart_rx_data(void)
{
	while(!(LPC_UART0->LSR & (1<<0)));
	unsigned char data = LPC_UART0->RBR;
	return data;
}
void uart_init(void)
{
	LPC_PINCON->PINSEL0 |= (1<<4)|(1<<6);
	LPC_SC->PCLKSEL0 = 0x00000000;//(0<<18)|(0<<19); //cclk/4=pclk
	LPC_UART0->LCR = (1<<0)|(1<<1)|(1<<7);
	LPC_UART0->DLL = 162; //by calculating value cclk/1=pclk pclk/(16*dll)=9600 boude rate
	LPC_UART0->DLM = 0x00;
	LPC_UART0->LCR =(1<<0)|(1<<1);
	LPC_UART0->FDR = (1<<4); //DIVADDVAL=0,MULVAL=1;
	LPC_UART0->TER = (1<<7); //TXEN BIT SET TO SEND DATA
	
	
}

int main(void)
{
	uart_init();
	unsigned char ptr[100]="shriram";
	int i=0;
	while(ptr[i] != '\0')
	{
		uart_tx_data(ptr[i]);
		i++;
	}
	unsigned char ch = uart_rx_data();
	uart_tx_data(ch);
}

