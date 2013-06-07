//*********************************************************************
//*********************************************************************
//sns.cpp - Speak and Spell
//  - prompts user for input
//  - prints input to screen
//  - provides spoken input via speech synthesis chip connected
//    to uart1 
//  - configures BeagleBone uart1 for tranmission and 9600 Baud
//
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

int main(void)
{
//define file handle for uart1
FILE *ofp_uart1_tx, *ofp_uart1_rx;

//define mux mode for uart1 tx
int mux_mode_uart1_tx = 0X8000;
int mux_mode_uart1_rx = 0X8020;

//configure uart1 for transmission
ofp_uart1_tx = fopen("/sys/kernel/debug/omap_mux/uart1_txd", "w");
if(ofp_uart1_tx == NULL) printf("Unable to open uart1 tx file.\n");
fseek(ofp_uart1_tx, 0, SEEK_SET);
fprintf(ofp_uart1_tx, "0x%2x", mux_mode_uart1_tx);
fflush(ofp_uart1_tx); 

//configure uart1 for transmission
ofp_uart1_rx = fopen("/sys/kernel/debug/omap_mux/uart1_rxd", "w");
if(ofp_uart1_rx == NULL) printf("Unable to open uart1 rx file.\n");
fseek(ofp_uart1_rx, 0, SEEK_SET);
fprintf(ofp_uart1_rx, "0x%2x", mux_mode_uart1_rx);
fflush(ofp_uart1_rx); 

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

char byte_out[20]; 

//set ASCII charater G repeatedly
while(1)
  {
  printf("Enter letter, word, statement.  Press [Enter].\n\n");
  scanf("%s", byte_out);
  printf("%s\n\n\n", byte_out);
  write(fd, byte_out, strlen(byte_out)+1);
  }

close(fd);
}
//*********************************************************************

