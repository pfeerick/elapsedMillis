/*  
  Simple demo of using all the timing helpers elapsedMillis makes available.

  Either attach LEDs with series resistors to the indicated pins, or a
  six led / six bit 'Chartreuse' module plugged into pins 8 through GND. 
  
  Wired up in order, the leds have a nice walking/counting effect.
  
  This example code is in the public domain.
*/

#include <elapsedMillis.h>

//declare these global if you don't want them reset every time loop runs
elapsedMicros LED1micro;
elapsedMicros LED2micro;
elapsedMillis LED3millis;
elapsedMillis LED4millis;
elapsedSeconds LED5seconds;
elapsedSeconds LED6seconds;

const int LED1 = 8;
const int LED2 = 9;
const int LED3 = 10;
const int LED4 = 11;
const int LED5 = 12;
const int LED6 = 13;

// delay between blinks of the LED
unsigned long LED1_Interval = 62500;
unsigned long LED2_Interval = 125000;
unsigned int LED3_Interval = 250;
unsigned int LED4_Interval = 500;
unsigned int LED5_Interval = 1;
unsigned int LED6_Interval = 2;

void setup()
{
  // initialize the LED pins as outputs
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
  pinMode(LED5, OUTPUT);
  pinMode(LED6, OUTPUT);
}

void loop()
{
  if (LED1micro >= LED1_Interval)
  {
    digitalWrite(LED1, !(digitalRead(LED1))); // toggle the LED state
    LED1micro = 0;                            // reset the counter to 0 so the counting starts over...
  }

  if (LED2micro >= LED2_Interval)
  {
    digitalWrite(LED2, !(digitalRead(LED2))); // toggle the LED state
    LED2micro = 0;                            // reset the counter to 0 so the counting starts over...
  }

  if (LED3millis >= LED3_Interval)
  {
    digitalWrite(LED3, !(digitalRead(LED3))); // toggle the LED state
    LED3millis = 0;                           // reset the counter to 0 so the counting starts over...
  }

  if (LED4millis >= LED4_Interval)
  {
    digitalWrite(LED4, !(digitalRead(LED4))); // toggle the LED state
    LED4millis = 0;                           // reset the counter to 0 so the counting starts over...
  }

  if (LED5seconds >= LED5_Interval)
  {
    digitalWrite(LED5, !(digitalRead(LED5))); // toggle the LED state
    LED5seconds = 0;                          // reset the counter to 0 so the counting starts over...
  }

  if (LED6seconds >= LED6_Interval)
  {
    digitalWrite(LED6, !(digitalRead(LED6))); // toggle the LED state
    LED6seconds = 0;                          // reset the counter to 0 so the counting starts over...
  }
}
