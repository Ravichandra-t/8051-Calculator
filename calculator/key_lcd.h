/*************************KEY_LCD.H***********************************/
/**************Declaring pins of LCD & KEYPAD*************************/
sbit rs=P3^3;									/*Register Select Pin*/
sbit en=P3^2;									/*Enable Pin*/
sbit R1=P2^0;									/*Row 1*/
sbit R2=P2^1;									/*Row 2*/
sbit R3=P2^2;									/*Row 3*/
sbit R4=P2^3;									/*Row 4*/
sbit C1=P2^4;									/*Column 1*/
sbit C2=P2^5;									/*Column 2*/
sbit C3=P2^6;									/*Column 3*/
sbit C4=P2^7;									/*Column 4*/
/*********************************************************************/

/*******************Function Declaration******************************/
unsigned char conv(unsigned char dat);
void delay(unsigned int ms);
void init_lcd();
void lcmd(unsigned char cmd);
void ldata(unsigned char msg);
void lstrng(unsigned char *msg);
unsigned char read_key();
unsigned char key();
/*********************************************************************/

/*******************Function Definition*******************************/
unsigned char conv(unsigned char dat)   /*To convert ASCII to DECIMAL*/
	{
		switch(dat)
			{
				case '0':return 0;break;
				case '1':return 1;break;
				case '2':return 2;break;
				case '3':return 3;break;
				case '4':return 4;break;
				case '5':return 5;break;
				case '6':return 6;break;
				case '7':return 7;break;
				case '8':return 8;break;
				case '9':return 9;break;
			}
	}
unsigned char read_key()   /* Scanning Pressed Key from Kepad */
	{
		C1=1;C2=1;C3=1;
		R1=0;R2=1;R3=1;R4=1;	/*first row */
		if(C1==0){delay(1);while(C1==0);return '7';}  /*first column  */
		if(C2==0){delay(1);while(C2==0);return '8';}  /*second column */
		if(C3==0){delay(1);while(C3==0);return '9';}  /*third column  */
		if(C4==0){delay(1);while(C4==0);return '/';}  /*fourth column */
		R1=1;R2=0;R3=1;R4=1;	/*second row */
		if(C1==0){delay(1);while(C1==0);return '4';}  /*first column  */
		if(C2==0){delay(1);while(C2==0);return '5';}  /*second column */
		if(C3==0){delay(1);while(C3==0);return '6';}  /*third column  */
		if(C4==0){delay(1);while(C4==0);return '*';}  /*fourth column */
		R1=1;R2=1;R3=0;R4=1;	 /*third row */
		if(C1==0){delay(1);while(C1==0);return '1';}  /*first column  */
		if(C2==0){delay(1);while(C2==0);return '2';}  /*second column */
		if(C3==0){delay(1);while(C3==0);return '3';}  /*third column  */
		if(C4==0){delay(1);while(C4==0);return '-';}  /*fourth column */
		R1=1;R2=1;R3=1;R4=0;	/*fourth row */
		if(C1==0){delay(1);while(C1==0);return 'C';}  /*first column  */
		if(C2==0){delay(1);while(C2==0);return '0';}  /*second column */
		if(C3==0){delay(1);while(C3==0);return '=';}  /*third column 	*/
		if(C4==0){delay(1);while(C4==0);return '+';}  /*fourth column */
		return 'n';
	}
unsigned char key(void)   /* Reapeat scanning until key pressed*/
	{
		char key='n';
		while(key=='n')
		key=read_key();
		return key;
	}
	
void delay(unsigned int ms)    /* 1ms Delay generation */
	{
		int i,j;
		for(i=0;i<ms;i++)
			for(j=0;j<1275;j++);
	}
	
void init_lcd()         /*Initializing LCD*/
	{
		lcmd(0x38);
		delay(5);
		lcmd(0x0c);
		delay(5);
		lcmd(0x01);
		delay(5);
		lcmd(0x06);
		delay(5);
	}
	
void lcmd(unsigned char cmd)  /*Function to send command*/
	{
		P1=cmd;
		en=1;
		rs=0;
		delay(1);
		en=0;
	}
	
void ldata(unsigned char msg)  /*Function to send Data*/
	{
		P1=msg;
		en=1;
		rs=1;
		delay(1);
		en=0;
	}
	
void lvar(unsigned char val)/*Function to display content of variable*/
	{
		unsigned char temp;
		temp = val/100;				 				// 123 / 100 = 1
		if(temp!=0)
			ldata(temp+0x30);
		temp = val/10;	   							// 123 / 10 = 12
		temp = temp%10;								// 12 % 10 = 2
		ldata(temp+0x30);
		temp = val%10;								// 123 % 10 = 3
		ldata(temp+0x30);
	}

void lstrng(unsigned char *msg)    /*Function to send String to LCD*/
	{
		int k;
		for(k=0;msg[k]!=0;msg++)
			ldata(msg[k]);
	}
void clr_lcd()										/*Function to clear LCD screen*/
	{
		lcmd(0x01);
		lcmd(0x80);
	}					
void set_cur(char line, char position)/*Function to set cursor*/
	{
		if(line==1)
			lcmd(0x80+position);
		if(line==2)
			lcmd(0xC0+position);
	}																											   
/************************************************************************/