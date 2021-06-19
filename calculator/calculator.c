#include<reg51.h>
#include<key_lcd.h>				/*Including Keypad & LCD file*/
void main()
	{	
		unsigned char a,b,c,op;
		init_lcd();
		clr_lcd();
		set_cur(1,3);
		lstrng("8051 BASED");
		set_cur(2,3);
		lstrng("CALCULATOR");
		delay(300);
		clr_lcd();
		while(1)
			{		
				a=key();					/*to get first number*/
				clr_lcd();
				ldata(a);					/*display it on LCD*/
				a=conv(a);				/*converting ASCII to DECIMAL*/
				op=key();					/*to get operator*/
				ldata(op);
				b=key();
				ldata(b);
				b=conv(b);
				c=key();
				if(c=='=')			
					switch(op)
						{
							case '+':op=a+b;ldata('=');lvar(op);break;
							case '-':op=a-b;ldata('=');lvar(op);break;
							case '*':op=a*b;ldata('=');lvar(op);break;
							case '/':op=a/b;ldata('=');lvar(op);
											 ldata(' ');op=a%b;lvar(op);break;
						}
			}
	}