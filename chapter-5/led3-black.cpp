//*********************************************************************
//led3.cpp: this programs toggles (flashes) an LED connected to
//expansion header P8, pin 13 (GPIO1_12 designated as gpio44) at five
//second intervals.
//*********************************************************************

#include <stdio.h>
#include <stddef.h>
#include <time.h>

#define  output "out"
#define  input  "in"

int  main (void)
{
//define file handles
FILE *ofp_export, *ofp_gpio44_value, *ofp_gpio44_direction;

//define pin variables
int pin_number = 44, logic_status = 1;
char* pin_direction = output;

//time parameters
time_t  now, later;

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

now = time(NULL);
later = time(NULL);

while(1)
  {
  while(difftime(later, now) < 5.0)
    {
    later = time(NULL); //keep checking time
    }
  if(logic_status == 1) logic_status = 0;
    else logic_status = 1;
  //write to gpio44
  fprintf(ofp_gpio44_value, "%d", logic_status);
  fflush(ofp_gpio44_value);
  now=time(NULL);
  later=time(NULL);
  }
fclose(ofp_export);
fclose(ofp_gpio44_direction);
fclose(ofp_gpio44_value);
return 1;
}	

//*********************************************************************

