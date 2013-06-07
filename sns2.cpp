//*********************************************************************
//sns.cpp - Speak and Spell
//  - prompts user for input
//  - prints input to screen
//  - configures BeagleBone P8, pin 5 for receive from SP0-512
//    speech chip SPEAKING pin (SP0-512, pin 17)
//  - configures BeagleBone uart1 for tranmission and 9600 Baud
//    (P9, 24)
//  - provides spoken input via speech synthesis chip connected
//    to uart1 tx pin (P9, 24) 
//*********************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include <iostream>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/time.h>

#define  output "out"
#define  input  "in"


//function prototype
void delay_us(int);
void delay_sec(float delay_value);
void configure_uart1(void);
void configure_SP0_512(void);
void SP0_512_handshake(void);
void reset_SP0_512(void);
void configure_P8_3_output(void);

//global variables
//***UART1*** 
//define file handle for uart1
FILE *ofp_uart1_tx, *ofp_uart1_rx;

//define mux mode for uart1 tx
int mux_mode_uart1_tx = 0X8000;
int mux_mode_uart1_rx = 0X8020;

//uart1 configuration using termios
termios uart1;
int fd, i;
char byte_out[40];

//***SP0-512***
//configure P8, pin 5 for input - connect to SP0-512 SPEAKING signal
//define file handles for gpio34 (P8, pin 5, GPIO1_2)
FILE *ofp_gpmc_ad2, *ofp_export_34, *ifp_gpio34_value, *ofp_gpio34_direction;

//define pin variables for gpio34
int mux_mode_34 = 0x003f, pin_number_34 = 34, logic_status_34;
char* pin_direction_34 = input;

//configure P8, pin 3 for output - connect to reset circuit on SP0-512
//define file handles for gpio38 (P8, pin 3, GPIO1_6)
FILE *ofp_gpmc_ad6, *ofp_export_38, *ofp_gpio38_value, *ofp_gpio38_direction;

//define pin variables for gpio38
int mux_mode_38 = 0x0007, pin_number_38 = 38, logic_status_38 = 0;
char* pin_direction_38 = output;

char cntr_cr[] = "\r";
char reset[] = "[RESET]";

int main(void)
{
configure_uart1();
configure_P8_3_output();
configure_SP0_512();

while(1)
  {
  printf("Enter letter, word, statement. Press [Enter].\r\n\n");
  scanf("%s", byte_out);
  printf("%s\r\n\n", byte_out);
  strcat(byte_out, cntr_cr);
  write(fd, byte_out, strlen(byte_out)+2);
  SP0_512_handshake();
  reset_SP0_512();
  }

fclose(ofp_gpmc_ad2);
fclose(ofp_export_34);
fclose(ofp_gpio34_direction);
fclose(ifp_gpio34_value);
close(fd);
}

//*************************************************************

void SP0_512_handshake(void)
{	
  for(i=0; i<=10; i++)           //wait for SPEAKING line to go logic high
    {
    delay_us(10000);
    }
  
  logic_status_34 = 1;

  while(logic_status_34 != 0)    //wait for SPEAKING line to go low
    {
    //configure gpio34 value and read the gpio34 pin  
    ifp_gpio34_value = fopen("/sys/class/gpio/gpio34/value", "r");
    if(ifp_gpio34_value == NULL) {printf("Unable to open gpio34_value.\n");}
    fseek(ifp_gpio34_value, 0, SEEK_SET);
    fscanf(ifp_gpio34_value, "%d", &logic_status_34);
    fclose(ifp_gpio34_value);
    }	    
  
  for(i=0; i<=10; i++)           //wait for SPEAKING line to go logic high
    {
    delay_us(10000);
    }
}

//*************************************************************

void configure_uart1(void)
{	

//configure uart1 for transmission
ofp_uart1_tx = fopen("/sys/kernel/debug/omap_mux/uart1_txd", "w");
if(ofp_uart1_tx == NULL) printf("Unable to open uart1 tx file.\n");
fseek(ofp_uart1_tx, 0, SEEK_SET);
fprintf(ofp_uart1_tx, "0x%2x", mux_mode_uart1_tx);
fflush(ofp_uart1_tx); 

//configure uart1 for reception
ofp_uart1_rx = fopen("/sys/kernel/debug/omap_mux/uart1_rxd", "w");
if(ofp_uart1_rx == NULL) printf("Unable to open uart1 rx file.\n");
fseek(ofp_uart1_rx, 0, SEEK_SET);
fprintf(ofp_uart1_rx, "0x%2x", mux_mode_uart1_rx);

//open uart1 for tx/rx, not controlling device
if((fd = open("/dev/ttyO1", O_RDWR | O_NOCTTY)) < 0)
  printf("Unable to open uart1 access.\n");

//get attributes of uart1
if(tcgetattr(fd, &uart1) < 0)
  printf("Could not get attributes of UART1 at ttyO1\n");

//set Baud rate
if(cfsetospeed(&uart1, B9600) < 0)
  printf("Could not set baud rate\n");
else
  printf("Baud rate: 9600\n");

//set attributes of uart1
uart1.c_iflag = 0;
uart1.c_oflag = 0;
uart1.c_lflag = 0;
uart1.c_cflag |= CS8;
tcsetattr(fd, TCSANOW, &uart1);
}

//***********************************************************

void configure_SP0_512(void)
{	
//gpio34 mux setting
ofp_gpmc_ad2 = fopen("/sys/kernel/debug/omap_mux/gpmc_ad2", "w");
if(ofp_gpmc_ad2 == NULL) {printf("Unable to open gpmc_ad2.\n");}
fseek(ofp_gpmc_ad2, 0, SEEK_SET);
fprintf(ofp_gpmc_ad2, "0x%02x", mux_mode_34);
fflush(ofp_gpmc_ad2);

//create direction and value file for gpio34
ofp_export_34 = fopen("/sys/class/gpio/export", "w");
if(ofp_export_34 == NULL) {printf("Unable to open export.\n");}
fseek(ofp_export_34, 0, SEEK_SET);
fprintf(ofp_export_34, "%d", pin_number_34);
fflush(ofp_export_34);

//configure gpio34 direction
ofp_gpio34_direction = fopen("/sys/class/gpio/gpio34/direction", "w");
if(ofp_gpio34_direction == NULL) {printf("Unable to open gpio34_direction.\n");}
fseek(ofp_gpio34_direction, 0, SEEK_SET);
fprintf(ofp_gpio34_direction, "%s",  pin_direction_34);
}

//*********************************************************************

void configure_P8_3_output(void)
{	
//gpio38 mux setting
ofp_gpmc_ad6 = fopen("/sys/kernel/debug/omap_mux/gpmc_ad6", "w");
if(ofp_gpmc_ad6 == NULL) {printf("Unable to open gpmc_ad6.\n");}
fseek(ofp_gpmc_ad6, 0, SEEK_SET);
fprintf(ofp_gpmc_ad6, "0x%02x", mux_mode_38);
fflush(ofp_gpmc_ad6);

//create direction and value file for gpio38
ofp_export_38 = fopen("/sys/class/gpio/export", "w");
if(ofp_export_38 == NULL) {printf("Unable to open export.\n");}
fseek(ofp_export_38, 0, SEEK_SET);
fprintf(ofp_export_38, "%d", pin_number_38);
fflush(ofp_export_38);

//configure gpio38 direction
ofp_gpio38_direction = fopen("/sys/class/gpio/gpio38/direction", "w");
if(ofp_gpio38_direction == NULL) {printf("Unable to open gpio38_direction.\n");}
fseek(ofp_gpio38_direction, 0, SEEK_SET);
fprintf(ofp_gpio38_direction, "%s",  pin_direction_38);
fflush(ofp_gpio38_direction);

//configure gpio38 value - initially set logic low
ofp_gpio38_value = fopen("/sys/class/gpio/gpio38/value", "w");
if(ofp_gpio38_value == NULL) {printf("Unable to open gpio38_value.\n");}
fseek(ofp_gpio38_value, 0, SEEK_SET);
fprintf(ofp_gpio38_value, "%d", logic_status_38);
fflush(ofp_gpio38_value);
}

//*************************************************************

void reset_SP0_512(void)
{	
logic_status_38 = 1;
fseek(ofp_gpio38_value, 0, SEEK_SET);
fprintf(ofp_gpio38_value, "%d", logic_status_38);
fflush(ofp_gpio38_value);

delay_us(10000);

logic_status_38 = 0;
fseek(ofp_gpio38_value, 0, SEEK_SET);
fprintf(ofp_gpio38_value, "%d", logic_status_38);
fflush(ofp_gpio38_value);
}

//**************************************************************

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

//*************************************************************
//delay_sec(float delay_value)
//*************************************************************

void delay_sec(float delay_value)
{
time_t   now, later;

now = time(NULL);
later = time(NULL);

while(difftime(later,now) < delay_value)
  {
  later = time(NULL);
  }  
}

//*************************************************************
