//******************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>

#define  output "out"
#define  input  "in"

//function prototypes
void configure_LCD_interface(void);
void LCD_putcommand(unsigned char);
void LCD_putchar(unsigned char);
void LCD_print(unsigned int, char *string);
void delay_us(int);
void LCD_init(void);
FILE *setup_gpio(unsigned int pin_number, char* direction);
void set_gpio_value(FILE* value_file, unsigned int logic_status);

//LCD_RS: bone.P8_9 LCD Register Set (RS) control: GPIO2_5: pin-69
FILE* gpio_rs_value = NULL;
int pin_number_rs = 69, logic_status_rs = 1;
char* pin_direction_rs = output;

//LCD_E:   bone.P8_10: LCD Enable En (E): GPIO2_4: pin-68
FILE* gpio_e_value = NULL;
int pin_number_e = 68, logic_status_e = 1;
char* pin_direction_e = output;
  
//LCD_DB0: bone.P8_11: LCD Data line DB0: GPIO1_13: pin-45
FILE *gpio_db0_value = NULL;
int pin_number_db0 = 45, logic_status_db0 = 1;
char* pin_direction_db0 = output;

//LCD_DB1: bone.P8_12: LCD Data line DB1: GPIO1_12: pin-44
FILE *gpio_db1_value = NULL;
int pin_number_db1 = 44, logic_status_db1 = 1;
char* pin_direction_db1 = output;

//LCD_DB2: bone.P8_13: LCD Data line DB2: GPIO0_23: pin-23
FILE *gpio_db2_value = NULL;
int pin_number_db2 = 23, logic_status_db2 = 1;
char* pin_direction_db2 = output;

//LCD_DB3: bone.P8_14: LCD Data line DB3: GPIO0_26: pin-26
FILE *gpio_db3_value = NULL;
int pin_number_db3 = 26, logic_status_db3 = 1;
char* pin_direction_db3 = output;

//LCD_DB4: bone.P8_15: LCD Data line DB4: GPIO1_15: pin-47
FILE *gpio_db4_value = NULL;
int pin_number_db4 = 47, logic_status_db4 = 1;
char* pin_direction_db4 = output;

//LCD_DB5: bone.P8_16: LCD Data line DB5: GPIO1_14: pin-46
FILE *gpio_db5_value = NULL;
int pin_number_db5 = 46, logic_status_db5 = 1;
char* pin_direction_db5 = output;

//LCD_DB6: bone.P8_17: LCD Data line DB6: GPIO0_27: pin-27
FILE *gpio_db6_value = NULL;
int pin_number_db6 = 27, logic_status_db6 = 1;
char* pin_direction_db6 = output;

//LCD_DB7: bone.P8_18: LCD Data line DB7: GPIO2_1: pin-65
FILE *gpio_db7_value = NULL;
int pin_number_db7 = 65, logic_status_db7 = 1;
char* pin_direction_db7 = output;


int main(void)
{	
configure_LCD_interface();
printf("Configure LCD \n");
LCD_init();  //call LCD initialize
printf("LCD initialize \n");

while(1)
 {
  LCD_print(1, "Bad to the");
  printf("Bad to the\n");
  delay_us(100);
  LCD_print(2, "  Bone");
  printf("  Bone\n");
  delay_us(100);
  }
return 1;
}

//******************************************************************
//FILE *setup_gpio(unsigned int pin_number, char* pin_direction)
//******************************************************************

FILE *setup_gpio(unsigned int pin_number, char* pin_direction)
{
FILE *exp, *gpio_value, *gpio_direction;
char gpio_direction_filename[40];
char gpio_value_filename[40];

//create direction and value file for pin
exp = fopen("/sys/class/gpio/export", "w");
if(exp == NULL) {printf("Unable to open export.\n");}
fseek(exp, 0, SEEK_SET);
fprintf(exp, "%d", pin_number);
fflush(exp);
fclose(exp);

//configure pin direction
sprintf(gpio_direction_filename, "/sys/class/gpio/gpio%d/direction", pin_number);
gpio_direction = fopen(gpio_direction_filename, "w");
if(gpio_direction == NULL) {printf("Unable to open %s.\n", gpio_direction_filename);}
fseek(gpio_direction, 0, SEEK_SET);
fprintf(gpio_direction, "%s",  pin_direction);
fflush(gpio_direction);
fclose(gpio_direction);

//open pin value file
sprintf(gpio_value_filename, "/sys/class/gpio/gpio%d/value", pin_number);
gpio_value = fopen(gpio_value_filename, "w");
if(gpio_value == NULL) {printf("Unable to open %s.\n", gpio_value_filename);}

printf("Opening %d (%s) returned 0x%08x\n", pin_number, gpio_value_filename, (int)gpio_value);
return(gpio_value);
}

//******************************************************************
//void set_gpio_value(FILE* value_file, unsigned int logic_status)
//******************************************************************
void set_gpio_value(FILE* value_file, unsigned int logic_status)
{

printf(" %d -> 0x%08x\n", logic_status, (int)value_file);
fseek(value_file, 0, SEEK_SET);
fprintf(value_file, "%d", logic_status);
fflush(value_file);

}

//******************************************************************
//void configure_LCD_interface(void)
//******************************************************************

void configure_LCD_interface(void)
{

//Setup LCD GPIO pins
gpio_rs_value = setup_gpio(pin_number_rs, pin_direction_rs);
gpio_e_value = setup_gpio(pin_number_e, pin_direction_e);
gpio_db0_value = setup_gpio(pin_number_db0, pin_direction_db0);
gpio_db1_value = setup_gpio(pin_number_db1, pin_direction_db1);
gpio_db2_value = setup_gpio(pin_number_db2, pin_direction_db2);
gpio_db3_value = setup_gpio(pin_number_db3, pin_direction_db3);
gpio_db4_value = setup_gpio(pin_number_db4, pin_direction_db4);
gpio_db5_value = setup_gpio(pin_number_db5, pin_direction_db5);
gpio_db6_value = setup_gpio(pin_number_db6, pin_direction_db6);
gpio_db7_value = setup_gpio(pin_number_db7, pin_direction_db7);

}

//******************************************************************
//LCD_init
//******************************************************************

void LCD_init(void)
{
delay_us(15000);                   //wait 15 ms
LCD_putcommand(0x30);              //set for 8-bit operation
delay_us(5000);                    //delay 5 ms
LCD_putcommand(0x30);              //set for 8-bit operation
delay_us(100);                     //delay 100 us
LCD_putcommand(0x30);              //set for 8-bit operation
LCD_putcommand(0x38);              //function set
LCD_putcommand(0x80);              //display off
LCD_putcommand(0x01);              //display clear
LCD_putcommand(0x06);              //entry mode set
}

//******************************************************************
//LCD_putcommand
//******************************************************************

void LCD_putcommand(unsigned char cmd)
{
//parse command variable into individual bits for output
//to LCD

//configure DB7 value
if((cmd & 0x0080)== 0x0080)
  {
  printf("CmDB7:1");
  logic_status_db7 = 1; 
  }
else
  {
  printf(" CmDB7:0");
  logic_status_db7 = 0;
  }
set_gpio_value(gpio_db7_value, logic_status_db7);


//configure DB6 value
if((cmd & 0x0040)== 0x0040)
  {
  printf(" CmDB6:1");
  logic_status_db6 = 1; 
  }
else
  {
  printf(" CmDB6:0");
  logic_status_db6 = 0;
  }
set_gpio_value(gpio_db6_value, logic_status_db6);


//configure DB5 value
if((cmd & 0x0020)== 0x0020)
  {
  printf(" CmDB5:1");
  logic_status_db5 = 1; 
  }
else
  {
  printf(" CmDB5:0");
  logic_status_db5 = 0;
  }
set_gpio_value(gpio_db5_value, logic_status_db5);


//configure DB4 value
if((cmd & 0x0010)== 0x0010)
  {
  printf(" CmDB4:1");
  logic_status_db4 = 1; 
  }
else
  {
  printf(" CmDB4:0");
  logic_status_db4 = 0;
  }
set_gpio_value(gpio_db4_value, logic_status_db4);


//configure DB3 value
if((cmd & 0x0008)== 0x0008)
  {
  printf(" CmDB3:1");
  logic_status_db3 = 1; 
  }
else
  {
  printf(" CmDB3:0");
  logic_status_db3 = 0;
  }
set_gpio_value(gpio_db3_value, logic_status_db3);


//configure DB2 value
if((cmd & 0x0004)== 0x0004)
  {
  printf(" CmDB2:1");
  logic_status_db2 = 1; 
  }
else
  {
  printf(" CmDB2:0");
  logic_status_db2 = 0;
  }
set_gpio_value(gpio_db2_value, logic_status_db2);


//configure DB1 value
if((cmd & 0x0002)== 0x0002)
  {
  printf(" CmDB1:1");
  logic_status_db1 = 1; 
  }
else
  {
  printf(" CmDB1:0");
  logic_status_db1 = 0;
  }
set_gpio_value(gpio_db1_value, logic_status_db1);


//configure DB0 value
if((cmd & 0x0001)== 0x0001)
  {
  printf(" CmDB0:1");
  logic_status_db0 = 1; 
  }
else
  {
  printf(" CmDB0:0");
  logic_status_db0 = 0;
  }
set_gpio_value(gpio_db0_value, logic_status_db0);

printf("\n");

//LCD Register Set (RS) to logic zero for command input
logic_status_rs = 0;
set_gpio_value(gpio_rs_value, logic_status_rs);

//LCD Enable (E) pin high
logic_status_e = 1;
set_gpio_value(gpio_e_value, logic_status_e);

//delay
delay_us(2);

//LCD Enable (E) pin low
logic_status_e = 0;
set_gpio_value(gpio_e_value, logic_status_e);

//delay
delay_us(100);
}

//******************************************************************
//LCD_putchar
//******************************************************************

void LCD_putchar(unsigned char chr)
{
//parse character variable into individual bits for output
//to LCD

printf("Data: %c:%d", chr, chr);
chr = (int)(chr);

//configure DB7 value
if((chr & 0x0080)== 0x0080)
  {
  printf(" DB7:1");
  logic_status_db7 = 1; 
  }
else
  {
  printf(" DB7:0");	  
  logic_status_db7 = 0;
  }
set_gpio_value(gpio_db7_value, logic_status_db7);


//configure DB6 value
if((chr & 0x0040)== 0x0040)
  {
  printf(" DB6:1");
  logic_status_db6 = 1; 
  }
else
  {
  printf(" DB6:0");
  logic_status_db6 = 0;
  }
set_gpio_value(gpio_db6_value, logic_status_db6);


//configure DB5 value
if((chr & 0x0020)== 0x0020)
  {
  printf(" DB5:1");
  logic_status_db5 = 1; 
  }
else
  {
  printf(" DB5:0");
  logic_status_db5 = 0;
  }
set_gpio_value(gpio_db5_value, logic_status_db5);


//configure DB4 value
if((chr & 0x0010)== 0x0010)
  {
  printf(" DB4:1");
  logic_status_db4 = 1; 
  }
else
  {
  printf(" DB4:0");
  logic_status_db4 = 0;
  }
set_gpio_value(gpio_db4_value, logic_status_db4);


//configure DB3 value
if((chr & 0x0008)== 0x0008)
  {
  printf(" DB3:1");
  logic_status_db3 = 1; 
  }
else
  {
  printf(" DB3:0");
  logic_status_db3 = 0;
  }
set_gpio_value(gpio_db3_value, logic_status_db3);


//configure DB2 value
if((chr & 0x0004)== 0x0004)
  {
  printf(" DB2:1");
  logic_status_db2 = 1; 
  }
else
  {
  printf(" DB2:0");
  logic_status_db2 = 0;
  }
set_gpio_value(gpio_db2_value, logic_status_db2);


//configure DB1 value
if((chr & 0x0002)== 0x0002)
  {
  printf(" DB1:1");
  logic_status_db1 = 1; 
  }
else
  {
  printf(" DB1:0");
  logic_status_db1 = 0;
  }
set_gpio_value(gpio_db1_value, logic_status_db1);

//configure DB0 value
if((chr & 0x0001)== 0x0001)
  {
  printf(" DB0:1\n");
  logic_status_db0 = 1; 
  }
else
  {
  printf(" DB0:0\n");
  logic_status_db0 = 0;
  }
set_gpio_value(gpio_db0_value, logic_status_db0);

//LCD Register Set (RS) to logic one for character input
logic_status_rs = 1;
set_gpio_value(gpio_rs_value, logic_status_rs);

//LCD Enable (E) pin high
logic_status_e = 1;
set_gpio_value(gpio_e_value, logic_status_e);

//delay
delay_us(2);

//LCD Enable (E) pin low
logic_status_e = 0;
set_gpio_value(gpio_e_value, logic_status_e);

//delay
delay_us(2);

}

//******************************************************************
//******************************************************************
void LCD_print(unsigned int line, char *msg)
{
int i = 0;

if(line == 1)
  {
  LCD_putcommand(0x80);          //print to LCD line 1
  }
else
  {
  LCD_putcommand(0xc0);          //print to LCD line 2
  }

while(*(msg) != '\0')
  {
  LCD_putchar(*msg);
  //printf("Data: %c\n\n", *msg);
  msg++;
  }
}

//******************************************************************

void delay_us(int desired_delay_us)
{
struct timeval  tv_start;  //start time hack
struct timeval  tv_now;    //current time hack
int elapsed_time_us;

gettimeofday(&tv_start, NULL);
elapsed_time_us = 0;

while(elapsed_time_us <  desired_delay_us)
  {
  gettimeofday(&tv_now, NULL);
  if(tv_now.tv_usec >= tv_start.tv_usec)
    elapsed_time_us = tv_now.tv_usec - tv_start.tv_usec;
  else
    elapsed_time_us = (1000000 - tv_start.tv_usec) + tv_now.tv_usec;
  //printf("start: %ld \n", tv_start.tv_usec);
  //printf("now: %ld \n", tv_now.tv_usec);
  //printf("desired: %d \n", desired_delay_ms);
  //printf("elapsed: %d \n\n", elapsed_time_ms);
  }
}

//******************************************************************



