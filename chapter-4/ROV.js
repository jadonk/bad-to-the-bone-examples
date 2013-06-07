//***********************************************************************

var b = require('bonescript');

//Old bonescript defines 'bone' globally
var pins = (typeof bone != 'undefined') ? bone : b.bone.pins;

var joystick_horz = pins.P9_39;            //joystick horizontal signal
var joystick_vert = pins.P9_40;            //joystick vertical signal
var joystick_sel  = pins.P8_10;            //joystick select button

var left_motor_pin  = pins.P9_14;          //PWM pin for left thruster
var right_motor_pin = pins.P9_16;          //PWM pin for right thruster
var vertical_motor_pin = pins.P8_13;       //output pin for vert thruster

var left_LED_pin  = pins.P8_7;             //left LED
var vert_LED_pin  = pins.P8_8;             //vertical LED
var right_LED_pin = pins.P8_9;             //right LED

var joystick_horizontal;
var joystick_vertical;
var vertical_thrust_on;

b.pinMode(joystick_sel, b.INPUT);
b.pinMode(vertical_motor_pin, b.OUTPUT);
b.pinMode(left_LED_pin, b.OUTPUT);
b.pinMode(vert_LED_pin, b.OUTPUT);
b.pinMode(right_LED_pin, b.OUTPUT);

//Read the joystick and react every 500 ms
setInterval(readJoystickAndDrive, 500);

function readJoystickAndDrive()
{
b.digitalWrite(vert_LED_pin, b.LOW);        //de-assert vertical LED
b.digitalWrite(left_LED_pin, b.LOW);        //de-assert left LED
b.digitalWrite(right_LED_pin, b.LOW);       //de-assert right LED
    
joystick_horizontal = b.analogRead(joystick_horz); //read horz position
joystick_vertical   = b.analogRead(joystick_vert); //read vert position
vertical_thrust_on  = b.digitalRead(joystick_sel); //vertical selected?

//Determine joystick position and desired thrust PWM relative
//to neutral (0.9 VDC, 0.9 VDC) position

if(joystick_horizontal > 0.9)
   joystick_horizontal = joystick_horizontal - 0.9;
else
   joystick_horizontal = 0.9 - joystick_horizontal;

if(joystick_vertical > 0.9)
   joystick_vertical = joystick_vertical - 0.9;
else
   joystick_vertical = 0.9 - joystick_vertical;

//If vertical thruster asserted - dive!
if(vertical_thrust_on)
  {
  b.digitalWrite(vertical_motor_pin, b.HIGH);   //assert vertical thruster 
  b.digitalWrite(vert_LED_pin, b.HIGH);         //assert vertical LED
  }
else
  {
  b.digitalWrite(vertical_motor_pin, b.LOW);    //de-assert vert thruster 
  }


//Update left and right thrusters

//Case 1: 
//  - Joystick horizontal has positive value
//  - Joystick vertical not asserted
//  - Move ROV forward
//      - Assert right and left thrusters
//      - Duty cycle determined by joystick position 
if((joystick_horizontal > 0) && (joystick_vertical == 0)) 
  {
  b.analogWrite(left_motor_pin,  joystick_horizontal);
  b.analogWrite(right_motor_pin, joystick_horizontal);
  b.digitalWrite(left_LED_pin, b.HIGH);     //assert left LED
  b.digitalWrite(right_LED_pin, b.HIGH);    //assert right LED
  }

//insert other cases
/*  
  :
  :
  :
*/
}

//***********************************************************************
