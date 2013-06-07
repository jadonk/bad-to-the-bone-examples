//******************************************************************
//sq_wave:  generates a 100 Hz, 50% duty cycle signal on header 
//P8, pin 13 (GPIO1_12 designated as gpio44).
//******************************************************************

#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <sys/time.h>

#define  output "out"
#define  input  "in"

void delay_us(int);

int  main (void)
{
//define file handles
FILE *ofp_export, *ofp_gpio44_value, *ofp_gpio44_direction;

//define pin variables
int pin_number = 44, logic_status = 1;
char* pin_direction = output;

ofp_export = fopen("/sys/class/gpio/export", "w");
if(ofp_export == NULL) {printf("Unable to open export.\n");}
fseek(ofp_export, 0, SEEK_SET);
fprintf(ofp_export, "%d", pin_number);
fflush(ofp_export);

ofp_gpio44_direction = fopen("/sys/class/gpio/gpio44/direction", "w");
if(ofp_gpio44_direction == NULL) {printf("Unable to open gpio44_direction.\n");}
fseek(ofp_gpio44_direction, 0, SEEK_SET);
fprintf(ofp_gpio44_direction, "%s",  pin_direction);
fflush(ofp_gpio44_direction);

ofp_gpio44_value = fopen("/sys/class/gpio/gpio44/value", "w");
if(ofp_gpio44_value == NULL) {printf("Unable to open gpio44_value.\n");}
fseek(ofp_gpio44_value, 0, SEEK_SET);
logic_status = 1;
fprintf(ofp_gpio44_value, "%d", logic_status);
fflush(ofp_gpio44_value);


while(1)
  {
  delay_us(5000);
  if(logic_status == 1) logic_status = 0;
    else logic_status = 1;
  //write to gpio44
  fprintf(ofp_gpio44_value, "%d", logic_status);
  fflush(ofp_gpio44_value);
  }
fclose(ofp_export);
fclose(ofp_gpio44_direction);
fclose(ofp_gpio44_value);
return 1;
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

