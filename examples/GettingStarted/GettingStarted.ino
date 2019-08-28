/*  
  Simple example of using elapsedMillis library
  
  This example does nothing more than blinking a LED... but the difference 
  here to just using delay(1000) to control the delay between blinks is that 
  you can do more in the loop - like get user input, check buttons, get sensor
  input and other tasks that take time - while you wait for the next time the 
  LED is to change state. All you need to do is add it before or after the 
  'if' statement that controls the check of the time elapsed. 
  
  This example code is in the public domain.
*/

#include <elapsedMillis.h>

elapsedMillis timeElapsed; //declare global if you don't want it reset every time loop runs

// Pin 13 has an LED connected on most Arduino boards.
int led = 13;

// delay in milliseconds between blinks of the LED
unsigned int interval = 1000;

// state of the LED = LOW is off, HIGH is on
boolean ledState = LOW;

void setup()
{
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
}

void loop()
{
  if (timeElapsed > interval)
  {
    ledState = !ledState; // toggle the state from HIGH to LOW to HIGH to LOW ...
    digitalWrite(led, ledState);
    timeElapsed = 0; // reset the counter to 0 so the counting starts over...
  }
}
