//**************************************************************
//adc1.cpp: the analog value on AIN0 (P9, pin 39) provided by 
//a LM34 temperature sensor is read continuously until 
//[Control][C] is used to stop the program.
//**************************************************************

#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <math.h>

#define  output "out"
#define  input  "in"

int  main (void)
{
//define file handles
FILE *ifp_ain1;
float ain0_value;

ifp_ain1 = fopen("/sys/bus/platform/devices/tsc/ain1", "r");
if (ifp_ain1 == NULL) {printf("Unable to ain1.\n");}

while(1)
  {
  fseek(ifp_ain1, 0, SEEK_SET);
  fscanf(ifp_ain1, "%f", &ain0_value);
  printf("%f\n", ain0_value); 
  }

fclose(ifp_ain1);
return 1;
}	
//**************************************************************

