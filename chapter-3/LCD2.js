//******************************************************************

var b = require ('bonescript');

//Old bonescript defines 'bone' globally
var pins = (typeof bone != 'undefined') ? bone : b.bone.pins;

var LCD_RS  = pins.P8_9;     //LCD Register Set (RS) control 
var LCD_E   = pins.P8_10;    //LCD Enable (E) control
var LCD_DB0 = pins.P8_11;    //LCD Data line DB0 
var LCD_DB1 = pins.P8_12;    //LCD Data line DB1 
var LCD_DB2 = pins.P8_13;    //LCD Data line DB2 
var LCD_DB3 = pins.P8_14;    //LCD Data line DB3 
var LCD_DB4 = pins.P8_15;    //LCD Data line DB4 
var LCD_DB5 = pins.P8_16;    //LCD Data line DB5 
var LCD_DB6 = pins.P8_17;    //LCD Data line DB6 
var LCD_DB7 = pins.P8_18;    //LCD Data line DB7 

b.pinMode(LCD_RS,  b.OUTPUT);       //set pin to digital output
b.pinMode(LCD_E,   b.OUTPUT);       //set pin to digital output
b.pinMode(LCD_DB0, b.OUTPUT);       //set pin to digital output
b.pinMode(LCD_DB1, b.OUTPUT);       //set pin to digital output
b.pinMode(LCD_DB2, b.OUTPUT);       //set pin to digital output
b.pinMode(LCD_DB3, b.OUTPUT);       //set pin to digital output
b.pinMode(LCD_DB4, b.OUTPUT);       //set pin to digital output
b.pinMode(LCD_DB5, b.OUTPUT);       //set pin to digital output
b.pinMode(LCD_DB6, b.OUTPUT);       //set pin to digital output
b.pinMode(LCD_DB7, b.OUTPUT);       //set pin to digital output
LCD_init(firstLine);                //call LCD initialize
function firstLine()
{
LCD_print(1, "BeagleBone", nextLine);
}
function nextLine()
{
LCD_print(2, "Bonescript");
}

//******************************************************************
//LCD_print
//******************************************************************

function LCD_print(line, message, callback)
{
var i = 0;

if(line == 1)
  {
  LCD_putcommand(0x80, writeNextCharacter);//print to LCD line 1
  }
else
  {
  LCD_putcommand(0xc0, writeNextCharacter);//print to LCD line 2
  }

function writeNextCharacter()
  {
  //if we already printed the last character, stop and callback
  if(i == message.length)
    {
    if(callback) callback();
    return;
    }

  //get the next character to print
  var chr = message.substring(i, i+1);
  i++;
  
  //print it using LCD_putchar and come back again when done
  LCD_putchar(chr, writeNextCharacter);
  }
}

//******************************************************************
//LCD_init
//******************************************************************

function LCD_init(callback)
{
//LCD Enable (E) pin low
b.digitalWrite(LCD_E, b.LOW);
  
//Start at the beginning of the list of steps to perform
var i = 0;

//List of steps to perform
var steps =
  [
  function(){ setTimeout(next, 15); },          //delay 15ms
  function(){ LCD_putcommand(0x38, next); },    //set for 8-bit operation 
  function(){ setTimeout(next, 5); },           //delay 5ms
  function(){ LCD_putcommand(0x38, next); },    //set for 8-bit operation
  function(){ LCD_putcommand(0x38, next); },    //set for 5 x 7 character
  function(){ LCD_putcommand(0x0E, next); },    //display on
  function(){ LCD_putcommand(0x01, next); },    //display clear
  function(){ LCD_putcommand(0x06, next); },    //entry mode set
  function(){ LCD_putcommand(0x00, next); },    //clear display, cursor at home
  function(){ LCD_putcommand(0x00, callback); } //clear display, cursor at home
  ];

next(); //Execute the first step

//Function for executing the next step
function next()
  {
  i++;
  steps[i-1]();
  }
}

//******************************************************************
//LCD_putcommand
//******************************************************************

function LCD_putcommand(cmd, callback)
{
//parse command variable into individual bits for output
//to LCD
if((cmd & 0x0080)== 0x0080) b.digitalWrite(LCD_DB7, b.HIGH);
  else b.digitalWrite(LCD_DB7, b.LOW);
if((cmd & 0x0040)== 0x0040) b.digitalWrite(LCD_DB6, b.HIGH);
  else b.digitalWrite(LCD_DB6, b.LOW);
if((cmd & 0x0020)== 0x0020) b.digitalWrite(LCD_DB5, b.HIGH);
  else b.digitalWrite(LCD_DB5, b.LOW);
if((cmd & 0x0010)== 0x0010) b.digitalWrite(LCD_DB4, b.HIGH);
  else b.digitalWrite(LCD_DB4, b.LOW);
if((cmd & 0x0008)== 0x0008) b.digitalWrite(LCD_DB3, b.HIGH);
  else b.digitalWrite(LCD_DB3, b.LOW);
if((cmd & 0x0004)== 0x0004) b.digitalWrite(LCD_DB2, b.HIGH);
  else b.digitalWrite(LCD_DB2, b.LOW);
if((cmd & 0x0002)== 0x0002) b.digitalWrite(LCD_DB1, b.HIGH);
  else b.digitalWrite(LCD_DB1, b.LOW);
if((cmd & 0x0001)== 0x0001) b.digitalWrite(LCD_DB0, b.HIGH);
  else b.digitalWrite(LCD_DB0, b.LOW);
 
//LCD Register Set (RS) to logic zero for command input
b.digitalWrite(LCD_RS, b.LOW);
//LCD Enable (E) pin high
b.digitalWrite(LCD_E, b.HIGH);
    
//End the write after 1ms
setTimeout(endWrite, 1);

function endWrite()
  {
  //LCD Enable (E) pin low
  b.digitalWrite(LCD_E, b.LOW);
  //delay 1ms before calling 'callback'
  setTimeout(callback, 1);
  }
}

//******************************************************************
//LCD_putchar
//******************************************************************

function LCD_putchar(chr1, callback)
{
//Convert chr1 variable to UNICODE (ASCII) 
var chr = chr1.toString().charCodeAt(0);

//parse character variable into individual bits for output
//to LCD
if((chr & 0x0080)== 0x0080) b.digitalWrite(LCD_DB7, b.HIGH);
  else b.digitalWrite(LCD_DB7, b.LOW);
if((chr & 0x0040)== 0x0040) b.digitalWrite(LCD_DB6, b.HIGH);
  else b.digitalWrite(LCD_DB6, b.LOW);
if((chr & 0x0020)== 0x0020) b.digitalWrite(LCD_DB5, b.HIGH);
  else b.digitalWrite(LCD_DB5, b.LOW);
if((chr & 0x0010)== 0x0010) b.digitalWrite(LCD_DB4, b.HIGH);
  else b.digitalWrite(LCD_DB4, b.LOW);
if((chr & 0x0008)== 0x0008) b.digitalWrite(LCD_DB3, b.HIGH);
  else b.digitalWrite(LCD_DB3, b.LOW);
if((chr & 0x0004)== 0x0004) b.digitalWrite(LCD_DB2, b.HIGH);
  else b.digitalWrite(LCD_DB2, b.LOW);
if((chr & 0x0002)== 0x0002) b.digitalWrite(LCD_DB1, b.HIGH);
  else b.digitalWrite(LCD_DB1, b.LOW);
if((chr & 0x0001)== 0x0001) b.digitalWrite(LCD_DB0, b.HIGH);
  else b.digitalWrite(LCD_DB0, b.LOW);

//LCD Register Set (RS) to logic one for character input
b.digitalWrite(LCD_RS, b.HIGH);
//LCD Enable (E) pin high
b.digitalWrite(LCD_E, b.HIGH);

//End the write after 1ms
setTimeout(endWrite, 1);

function endWrite()
  {
  //LCD Enable (E) pin low and call scheduleCallback when done
  b.digitalWrite(LCD_E, b.LOW);
  //delay 1ms before calling 'callback'
  setTimeout(callback, 1);
  }
}

//******************************************************************
