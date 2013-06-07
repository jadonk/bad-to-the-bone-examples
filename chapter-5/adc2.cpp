//**************************************************************
//include files
#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <math.h>

//define
#define  output "out"
#define  input  "in"
#define  ain1_in "/sys/bus/platform/devices/tsc/ain1"

//function prototypes
void delay_sec(float delay_value);

int  main (void)
{
//define file handles
FILE *ifp_ain1;
float ain0_value;
float ain0_voltage;
float ain0_temp;

ifp_ain1 = fopen(ain1_in, "r");
if (ifp_ain1 == NULL) {printf("Unable to ain1.\n");}

while(1)
  {
  fseek(ifp_ain1, 0, SEEK_SET);
  fscanf(ifp_ain1, "%f", &ain0_value);
  printf("AINO reading [of 4096]: %f\n", ain0_value); 
  ain0_voltage = ((ain0_value/4096.0) * 1.8);
  printf("AINO voltage [V]: %f\n", ain0_voltage);
  ain0_temp = (ain0_voltage/.010);
  printf("AINO temperature [F]: %f\n\n", ain0_temp);
  delay_sec(2.0);
  }
fclose(ifp_ain1);
return 1;
}	

//**************************************************************
//function definitions
//**************************************************************

void delay_sec(float delay_value)
{
time_t  now, later;

now = time(NULL);
later = time (NULL);

while(difftime(later, now) < delay_value)
  {
  later = time(NULL);             //keep checking time
  }
}

//**************************************************************

