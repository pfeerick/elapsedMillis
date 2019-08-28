/*
  Blink with elapsed time
  Shows how to use elapsed time to free up your sketch to do interesting work
 
  This example code is in the public domain.

  The elapsedMillis() and elapsedMicros() code was originally developed for
  the Teensy USB development board (http://www.pjrc.com/teensy/)

  Using timers in your code introduces a new concept - variables that
  change their value "by themselves"

  The advantage of using timers or elapsed time counters is that you
  can use them to free yourself from the busy-wait limitations of
  delay(), allowing you to do other work in your sketch.

  Unlike the "int led" variable used below, which is initialized once
  and then assumed to always hold the same value, or the ledState
  variable that is explicitly set to a new value every time the LED is
  turned on or off, the elapsed time datatypes introduced here
  automatically update themselves as time passes; their "value" is the
  amount of time that has passed since the variable was created or
  set. When you set an elapsedMillis variable to 0 (zero), 1
  millisecond later it will contain 1, not 0.  1385 milliseconds
  later, it will contain 1385.

  You can set/reset these variables to whatever value you want,
  whenever you want, and they will be incremented by 1 after each
  milli/micro-second of time has passed.  You can use them to easily
  decide in your program when to do stuff.

  But be careful!  Most of the time you will probably want to declare
  variables of the elapsedMillis/elpasedMicros data-type globally, at
  the top of your sketch.  If you define them inside a function() or
  in loop(), they will be reset to 0 (zero) each time the function is
  called; there they will do a good (but probably unintended) job of
  counting the only elapsed time taken since the function was called.

  Both milliseconds and mimicrosecond based interval counters are 
  supported:
     elapsedmillis em1;
	 elapsedmicros em2;
	
  All the standard operations are supported on them.

  There are 3 examples below that blink a LED every second.  
    * The first is the venerable blink sketch that uses delay() to 
      "do nothing" while waiting for time to pass.
    * The second uses calls to millis() to calculate if enough 
      time has passed, and
    * The third is similar, but uses an elapsedmillis variable.

  All three of these are examples of an explicit polling mechanism
  - your code continually asks itself "is it time yet", and if so,
  does something.  The alternative, in situations where much more
  exact timing is needed, or if further decoupling is required
  between your time-aware code and the rest of your application is
  an interrupt handler that takes advantage of the various TIMER
  mechanisms that are supported directly by your microcontroller.
  For more on using the TIMER hardware directly, see the Arduino
  Timer examples on playground:
        http://playground.arduino.cc/code/timer1

  More examples can be found at http://www.pjrc.com/teensy/td_timing.html

 */

#include <elapsedMillis.h>

// Pin 13 has an LED connected on most Arduino boards.
int led = 13;

// the setup routine runs once when you press reset:
void setup()
{
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
}

elapsedMillis elapsedTime; // used by elapsedmilis example
                           // Globally scoped - see comment above

unsigned long lasttime = millis(); // used by millis() example...

unsigned int interval = 1000;
boolean ledState = LOW;

void loop()
{
  // delayloop();
  // millisloop();
  elapsedmillisloop();
}

// ##########################  delay() based loop ###########################
//
// the loop routine runs over and over again forever,
// but that is all it can do, since the delay() calls preclude
// doing other work...
//
// In this example, the LED blinks on and off once per invocation of loop()

void delayloop()
{
  // Note that any "real code" you put here will cause the time between blinks to grow
  delay(1000); // wait for a second
  // and, finally, blink the lights:

  ledState = !ledState; // toggle the state from HIGH to LOW to HIGH to LOW ...
  digitalWrite(led, ledState);
}

// ##########################  millis() based loop ###########################
//
// the loop routine runs over and over again forever,
// with the blink rate decoupled from however much time the "real code" of the sketch takes
//
// In this example, the blink rate of the LED is independent of the number of times loop()
// is invoked as well as how long it takes to the rest of loop()'s code to run (presuming,
// of course, that the desired blink interval is significantly larger than than that "other"
// time)

void millisloop()
{

  // your "real" code goes here:
  //      read sensors
  //      compute new servo positions
  //      update motor driver output
  // and, finally, blink the lights:

  if (millis() - lasttime >= interval)
  {
    ledState = !ledState; // toggle the state from HIGH to LOW to HIGH to LOW ...
    digitalWrite(led, ledState);
    lasttime = millis();
  }
}

// ##########################  elapsedmillis() based loop ###########################
//
// the loop routine runs over and over again forever,
// with the blink rate decoupled from however much time the "real code" of the sketch takes
//
// This example is almost the same as the millis() one, with the various accounting details
// abstracted by the new datatype.

void elapsedmillisloop()
{

  // your "real" code goes here:
  //      read sensors
  //      compute new servo positions
  //      update motor driver output
  // and, finally, blink the lights:

  if (elapsedTime > interval)
  {                       // Again, note that "elapsedTime" is global scope
    ledState = !ledState; // toggle the state from HIGH to LOW to HIGH to LOW ...
    digitalWrite(led, ledState);
    elapsedTime = 0; // reset the counter to 0 so the counting starts over...
  }
}
