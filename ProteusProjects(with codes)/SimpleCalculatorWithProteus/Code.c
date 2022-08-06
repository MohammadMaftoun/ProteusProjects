#include <mega32.h>
#include <stdio.h>
#include <alcd.h>

int row[4]={0xfe,0xfd,0xfb,0xf7},num1=0,num2=0;
char buffer[16];
bit flag2=0;
bit flag=0;
void setNum(int n);
void sum();
void mul();
void dev();
void sub();

void main(void)
{
int i=0,mode=0;

PORTA=0x00;
DDRA=0x00;
PORTB=0x00;
DDRB=0x00;
Func0=Out  
PORTC=0xff;
DDRC=0x0F;
 
PORTD=0x00;
DDRD=0x00;

TCCR0=0x00;
TCNT0=0x00;
OCR0=0x00;

TCCR1A=0x00;
TCCR1B=0x00;
TCNT1H=0x00;
TCNT1L=0x00;
ICR1H=0x00;
ICR1L=0x00;
OCR1AH=0x00;
OCR1AL=0x00;
OCR1BH=0x00;
OCR1BL=0x00;

ASSR=0x00;
TCCR2=0x00;
TCNT2=0x00;
OCR2=0x00;

MCUCR=0x00;
MCUCSR=0x00;

TIMSK=0x00;

UCSRB=0x00;

ACSR=0x80;
SFIOR=0x00;

ADCSRA=0x00;

SPCR=0x00;
TWCR=0x00;

lcd_init(16);

while (1)
      {
      // Place your code here  
         for(i=0;i<4;i++)
        {
            PORTC=row[i];
            if(i==0)
            {
                if(PINC.4==0)
                {
                    while(PINC.4==0)
                    {}
                    lcd_putchar('7');
                    setNum(7);
                }
                if(PINC.5==0)
                {
                    while(PINC.5==0)
                    {}
                    lcd_putchar('8');
                    setNum(8);
                }
                if(PINC.6==0)
                {
                    while(PINC.6==0)
                    {}
                    lcd_putchar('9');
                    setNum(9);
                }
                if(PINC.7==0)
                {
                    while(PINC.7==0)
                    {}
                    if(flag==0 || flag2==1)
                    {
                        flag=1;
                        lcd_putchar('/');
                        flag2=0;
                        mode=1;
                    }
                }     
            }
            else
            {
            if(i==1)
            {
                if(PINC.4==0)
                {
                    while(PINC.4==0)
                    {}
                    lcd_putchar('4');
                    setNum(4);
                }
                if(PINC.5==0)
                {
                    while(PINC.5==0)
                    {}
                    lcd_putchar('5');
                    setNum(5);
                }
                if(PINC.6==0)
                {
                    while(PINC.6==0)
                    {}
                    lcd_putchar('6');
                    setNum(6);
                }
                if(PINC.7==0)
                {
                    while(PINC.7==0)
                    {}
                    if(flag==0 || flag2==1)
                    {
                        flag=1; 
                        flag2=0;
                        lcd_putchar('*');
                        mode=2;
                    }
                }     
            }
            else
            {
            if(i==2)
            {
                if(PINC.4==0)
                {
                    while(PINC.4==0)
                    {}
                    lcd_putchar('1');
                    setNum(1);
                }
                if(PINC.5==0)
                {
                    while(PINC.5==0)
                    {}
                    lcd_putchar('2');
                    setNum(2);
                }
                if(PINC.6==0)
                {
                    while(PINC.6==0)
                    {}
                    lcd_putchar('3');
                    setNum(3);
                }
                if(PINC.7==0)
                {
                    while(PINC.7==0)
                    {}
                    if(flag==0 || flag2==1)
                    {
                        flag=1;  
                        flag2=0;
                        lcd_putchar('-');
                        mode=3;
                    }
                }     
            }
            else
            {
            if(i==3)
            {
                if(PINC.4==0)
                {
                    while(PINC.4==0)
                    {}
                    num1=0;
                    num2=0;
                    flag=0;
                    flag2=0;
                    lcd_clear();
                }
                if(PINC.5==0)
                {
                    while(PINC.5==0)
                    {}
                    lcd_putchar('0');
                    setNum(0);
                }
                if(PINC.6==0)
                {
                    while(PINC.6==0)
                    {}
                    switch(mode)
                    {
                        case 1:
                        {
                            dev();
                            break;
                        }
                        case 2:
                        {
                            mul();
                            break;
                        }
                        case 3:
                        {
                            sub();
                            break;
                        }
                        case 4:
                        {
                            sum();
                            break;
                        }
                    }
                }
                if(PINC.7==0)
                {
                    while(PINC.7==0)
                    {}
                    if(flag==0 || flag2==1)
                    {
                        flag=1;
                        flag2=0;
                        lcd_putchar('+');
                        mode=4;
                    }
                }     
            }
            }
            }
            }
            
        }
      }
}

void setNum(int n)
{

    if(flag==1)
    {
        num2=(num2)*10;
        num2+=n;
    }
    else if(flag==0)
    {
        num1=(num1)*10;
        num1+=n;
    }          
}

void sum()
{
    int answer=num1+num2;
    num1=answer;
    num2=0;
    lcd_clear();
    sprintf(buffer,"%d",answer);
    lcd_puts(buffer);
    flag2=1;
}

void mul()
{
    int answer=num1*num2;
    num2=0;
    num1=answer;
    lcd_clear();
    sprintf(buffer,"%d",answer);
    lcd_puts(buffer);
    flag2=1;
}

void dev()
{
    int answer=num1/num2;
    num2=0;
    lcd_clear();
    num1=answer;
    sprintf(buffer,"%d",answer);
    lcd_puts(buffer);
    flag2=1;
}

void sub()
{
    int answer=num1-num2;
    num1=answer;
    num2=0;
    lcd_clear();
    sprintf(buffer,"%d",answer);
    lcd_puts(buffer); 
    flag2=1;
}