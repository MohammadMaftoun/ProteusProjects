#include <mega8.h>
#include <delay.h>

#define comm_port PORTC
#define data_port PORTD

void set_time(void);
void display(void);

flash char cathode_seg[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
//-------------------------0----1----2----3----4----5----6----7----8----9---


signed char second=0,minute=0,hour=0;
unsigned char key,dot, pointer;
unsigned char dot_set_min,dot_set_hour,dot_set_sec;


void main(void)
{
PORTB=0x00;
DDRB=0x00;
PORTC=0x00;
DDRC=0xFF;
PORTD=0x00;
DDRD=0xFF;
ASSR=0x08;
TCCR2=0x05;
TCNT2=0x00;
OCR2=0x00;
TIMSK=0x40;
#asm("sei")

while (1)
      {
      set_time();
      display(); 
      }
}

//*************************************************************************
interrupt [TIM2_OVF] void timer2_ovf_isr(void)
{
if (dot==0) {
pointer = ~pointer & 0b10000000;
second++;
    if (second > 59) 
    {
    second=0;
    minute++;
            if (minute>59)
            {
            minute=0;
            hour++;
                    if(hour>23)
                    {
                    hour=0;
                    }
            }
    } 
            };

}
//***************************************************************************
void set_time(void)
{
key=PINB & 0b00000111;
switch (key) {
/////press set button
    case 0b00000001:
                    dot++;
                   switch (dot) {
                    case 1 :
                    dot_set_sec=0b10000000;
                    dot_set_min=0b00000000;
                    dot_set_hour=0b00000000; 
                    pointer=0;
                    break;
                   case 2:
                    dot_set_sec=0b00000000;
                    dot_set_min=0b10000000;
                    dot_set_hour=0b00000000;
                    pointer=0;
                    break; 
                   case 3:
                    dot_set_sec=0b00000000;
                    dot_set_min=0b00000000;
                    dot_set_hour=0b10000000;
                    pointer=0;
                    break;                    
                    default:
                    if (dot >= 4) {  
                    dot=0; 
                    dot_set_sec=0b00000000;
                    dot_set_min=0b00000000;
                    dot_set_hour=0b00000000; 
                    }
                    };
                    break; 
/////press up button                    
    case 0b00000010:                        
                    switch (dot) { 
                        case 1 : 
                                second++;
                                if (second>59)  second=0;

                                break;                    
                        case 2 : 
                                minute++;
                                if (minute>59)  minute=0;

                                break;
                                 
                         case 3:       
                                hour++;
                                if (hour>23)    hour=0;

                                break;
                               };
                    break;
////press DOWN button    
    case 0b00000100:                        
                    switch (dot) { 
                        case 1 : 
                                second--;
                                if (second<0)  second=59;

                                break;                    
                        case 2 : 
                                minute--;
                                if (minute<0)  minute=59;
                                
                                break;
                                 
                         case 3:       
                                hour--;
                                if (hour<0)    hour=23;
                                  
                                break;
                               };    
                    break;
};
}
//********************************************************************
void display(void)
{ 
unsigned char i;
for(i=0;i<100;i++){
data_port=cathode_seg[hour   / 10] | dot_set_hour         ;comm_port=0b11111110;delay_us(250);comm_port=0xff; 
data_port=cathode_seg[hour   % 10] | dot_set_hour| pointer;comm_port=0b11111101;delay_us(250);comm_port=0xff;
data_port=cathode_seg[minute / 10] | dot_set_min          ;comm_port=0b11111011;delay_us(250);comm_port=0xff; 
data_port=cathode_seg[minute % 10] | dot_set_min | pointer;comm_port=0b11110111;delay_us(250);comm_port=0xff;  
data_port=cathode_seg[second / 10] | dot_set_sec          ;comm_port=0b11101111;delay_us(250);comm_port=0xff; 
data_port=cathode_seg[second % 10] | dot_set_sec          ;comm_port=0b11011111;delay_us(250);comm_port=0xff; 
                  };
}