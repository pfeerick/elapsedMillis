/*
  Using timeouts for user interaction
  
  A more "real" example than blinking a LED - demonstrate waiting for user input while 
  flashing a LED in an arbitrary sequence.
 
  This example code is in the public domain.

  The elapsedMillis() and elapsedMicros() code was originally developed for
  the Teensy USB development board (http://www.pjrc.com/teensy/)

  More examples can be found at http://www.pjrc.com/teensy/td_timing.html

  Note that elapsedMillis variables should usually have global scope.  If they're 
  local, they restart from zero every time the function runs, which might be useful 
  in some cases, but usually you want them to retain their value over longer time.  
 */

#include <elapsedMillis.h>
#include <ctype.h>

#define LEDPIN 13         // The usual Arduino LED port...
#define USERWAITTIME 6000 // milliseconds
#define LEDWAITTIME 35    // milliseconds

// Many non-trivial Arduino programs benefit from being expressed as a state machine.
// This one encodes the various nuances of accepting user input while still doing
// background work (flashing the LED...)
//
// State machine:  a device that can be in one of a set number of stable conditions
//                 depending on its previous condition and on the present values of
//                 its inputs.
//
// Alan Skorkin wrote a nice blog about using state machines:
//    http://www.skorks.com/2011/09/why-developers-never-use-state-machines/
// in response to this (non-Arduino) post:
//    http://www.shopify.com/technology/3383012-why-developers-should-be-force-fed-state-machines#axzz2jvAUuwUj
//
enum State
{
    INIT,
    NEEDINPUT,
    WAITING,
    TIMEOUT,
    PROCESSING,
    FINISHED,
    ERROR
} state;

// The LED would be really boring if it just sat there being either always on or always off
// The array encodes a flash pattern to let you know that nothing is hung...
boolean flashPattern[] = {1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0};
unsigned int ledIndex = 0;

elapsedMillis timeout; // Globally scoped - see comment above
elapsedMillis pulserate;
char userinput;
boolean ledBrightness = HIGH;
String validInput = "YN";

void setup()
{
    //set the LED pin as an output
    pinMode(LEDPIN, OUTPUT);

    //Initialize serial and wait for port to open:
    Serial.begin(9600);
    while (!Serial)
    {
        ; // wait for serial port to connect. Needed for Leonardo only
    }
    state = INIT;
}

void loop()
{
    // Every time through loop(), the state variable controls what we do.
    // As things get done, the state variable is updated to hold the next state.
    // The power of a state machine is that it can clearly describe the program
    // flow through a complicated decision tree as opposed to a monoithic structure.

    switch (state)
    {
    case INIT:
        Serial.println("Welcome to the world of elapsed time");
        Serial.println("This is a Simple light sequence controller.");
        Serial.print("Watch the LED on pin");
        Serial.print(LEDPIN, DEC);
        Serial.println("as you interact with the program.");
        state = NEEDINPUT;
        break;
    case NEEDINPUT:
        Serial.print("Toggle LED? (Y/n): ");
        timeout = 0;
        state = WAITING;
        break;
    case WAITING:
        if (Serial.available())
        {
            userinput = toupper(Serial.read());
            if (validInput.indexOf(userinput) == -1)
            {
                state = ERROR;
            }
            else
            {
                state = PROCESSING;
            }
            break;
        }
        else if (timeout > USERWAITTIME)
        {
            state = TIMEOUT;
        }
        break;
    case TIMEOUT: // If you wanted to be obnoxious, you could ring a bell to get the user's attention at this point
        Serial.println("<took too long>");
        state = NEEDINPUT;
        break;
    case PROCESSING:
        Serial.println(userinput);
        // The whole point is to make the flashpattern invert when the user says "Y"
        if (userinput == 'Y')
            ledBrightness = !ledBrightness;
        state = NEEDINPUT;
        break;
    default:
    case ERROR:
        Serial.println(" Braap!");
        Serial.print("Expected [");
        Serial.print(validInput);
        Serial.println("], please follow directions!");
        state = NEEDINPUT;
        break;
    }

    if (pulserate > LEDWAITTIME)
    {
        // Demonstrate doing 2 things at once - waiting for input (above) while flashing a LED in a sequence (here)
        digitalWrite(LEDPIN, flashPattern[ledIndex++] ? ledBrightness : !ledBrightness);
        if (ledIndex > sizeof(flashPattern))
            ledIndex = 0;
        pulserate = 0;
    }
}
