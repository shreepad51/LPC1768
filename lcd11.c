#include"lpc17xx.h"
#include"lcd.h"
int main(void)
{
	init_lcd();
send_cmd(0x80);
	user_string("shree");
	send_cmd(0xc0);
	user_string("ram");
}
