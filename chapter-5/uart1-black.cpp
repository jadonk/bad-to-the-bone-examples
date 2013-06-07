//*********************************************************************
//uart1.cpp - configures BeagleBone uart1 for tranmission and 9600 Baud
//and repeatedly sends the character G via uart1 tx pin (P9, 24)
//
//To configure the UART first do:
// # dtc -O dtb -o uart1-00A0.dtbo -b 0 -@ uart1.dts
// # cp uart1-00A0.dtbo /lib/firmware/uart1-00A0.dtbo
// # echo uart1 > /sys/devices/bone_capemgr.8/slots
//
//Check that the pinmux has been configured via:
// # cat /sys/kernel/debug/pinctrl/44e10800.pinmux/pinmux-pins
// pin 96 (44e10980): serial1_pinmux_helper.14 (GPIO UNCLAIMED) function pinmux_serial1_pins group pinmux_serial1_pins
// pin 97 (44e10984): serial1_pinmux_helper.14 (GPIO UNCLAIMED) function pinmux_serial1_pins group pinmux_serial1_pins
//
//*********************************************************************

#include <stdio.h>
#include <stddef.h>
#include <time.h>
#include <iostream>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>

int main(void)
{
//define file handle for uart1
FILE *ofp_uart1_tx, *ofp_uart1_rx;

//uart1 configuration using termios
termios uart1;
int fd;

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
tcsetattr(fd, TCSANOW, &uart1);

char byte_out[] = {0x47};

//set ASCII charater G repeatedly
while(1)
  {
  write(fd, byte_out, strlen(byte_out)+1);
  }

close(fd);
}

//***********************************************************

