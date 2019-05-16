#include<lpc17xx.h>
#include"lcd.h"
static int flag=0;
static unsigned int i=0;
void delay1(unsigned int time)
{
	int i,j;
	for(i=0;i<10000;i++)
	for(j=0;j<time;j++);
}
//int counter();
int main()
{
	init_lcd();
	//LPC_PINCON->PINSEL4 &=~((1<<23)|(1<<22)| (1<<18)|(1<<19));   //22&23 are set for buzzer 
  //LPC_GPIO2->FIODIR1 = (1<<3)|(1<<1);
	LPC_PINCON->PINSEL4 =(1<<24);
	LPC_GPIO2->FIODIR1 =(1<<1);
	
	//LPC_SC->EXTINT=(1<<2);
	LPC_SC->EXTMODE &=~(1<<2);
	LPC_SC->EXTPOLAR &=~(1<<2);
	
	NVIC_EnableIRQ(EINT2_IRQn);
	while(1)
	{
	//LPC_GPIO2->FIOCLR1=(1<<23)|(1<<22);}
}
}
void EINT2_IRQHandler(void)
{
	if(flag==0)
	{
	 user_string("YOU ARE IN Interrupt1");
		LPC_GPIO2->FIOSET1=(1<<1);
		delay1(1000);
		send_cmd(0x01);
	 // counter();
	flag=1;
	}
	else 
	{
	user_string("YOU ARE IN Interrupt2");
		LPC_GPIO2->FIOCLR1=(1<<1);
		delay1(1000);
		send_cmd(0x01);
  //  counter();	
		flag=0;
	}	
	LPC_SC->EXTINT =(1<<2);
}
//int counter()
//{
//	while(1)
	//{
//		i++;
//	  send_data(i);
//	}
//}
