//**********************************************************************
//pwm.cpp
//
//This uses PWM to output a "fade" effect to P9_14
//
//Before use, you must:
// echo bone_pwm_P9_14 > /sys/devices/bone_capemgr.*/slots
//
//Note that in /sys/devices/ocp.2/pwm_test_P9_14.12
// the .2 after ocp and the .12 after pwm_test_P9_14 both might change
//**********************************************************************
#include <stdio.h>
#include <stddef.h>
#include <time.h>

#define  output "out"
#define  input  "in"

int  main (void)
{
//define file handles
FILE *pwm_period, *pwm_duty, *pwm_polarity, *pwm_run;

//define pin variables
int period = 500000, duty = 250000, polarity = 1, run = 1;
int increment = 1;

pwm_period = fopen("/sys/devices/ocp.2/pwm_test_P9_14.12/period", "w");
if(pwm_period == NULL) {printf("Unable to open pwm period.\n");}
fseek(pwm_period, 0, SEEK_SET);
fprintf(pwm_period, "%d", period);
fflush(pwm_period);

pwm_duty = fopen("/sys/devices/ocp.2/pwm_test_P9_14.12/duty", "w");
if(pwm_duty == NULL) {printf("Unable to open pwm duty cycle.\n");}
fseek(pwm_duty, 0, SEEK_SET);
fprintf(pwm_duty, "%d", duty);
fflush(pwm_duty);

pwm_polarity = fopen("/sys/devices/ocp.2/pwm_test_P9_14.12/polarity", "w");
if(pwm_polarity == NULL) {printf("Unable to open pwm polarity.\n");}
fseek(pwm_polarity, 0, SEEK_SET);
fprintf(pwm_polarity, "%d", polarity);
fflush(pwm_polarity);

pwm_run = fopen("/sys/devices/ocp.2/pwm_test_P9_14.12/run", "w");
if(pwm_run == NULL) {printf("Unable to open pwm run.\n");}
fseek(pwm_run, 0, SEEK_SET);
fprintf(pwm_run, "%d", run);
fflush(pwm_run);

while(1)
  {
if(duty >= period) increment = -1;
else if(duty <= 0) increment = 1;
duty += increment;
fseek(pwm_duty, 0, SEEK_SET);
fprintf(pwm_duty, "%d", duty);
fflush(pwm_duty);
  }

fclose(pwm_period);
fclose(pwm_duty);
fclose(pwm_polarity);
fclose(pwm_run);

return 1;
}	
//**********************************************************************

