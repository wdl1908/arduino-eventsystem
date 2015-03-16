# EventPWMLed #

A led must be connected to GND on a digital PWM pin with a serie resistor.

## Construct a PWMLed Object ##

```
EventPWMLed led = EventPWMLed(10);
```

## Parameters ##

  * **ledPin**          The pin number where the led is connected to.
  * **ledFadeTime**     The time neede to fade a led in or out. Default is 2000ms.
  * **ledBlinkOnTime**  Time the led is on when blinking. Default is 250ms.
  * **ledBlinkOffTime** Time the led is off when blinking. Default is 250ms.

## Events Consumed ##

  * **Events::EV\_LED\_ON**
  * **Events::EV\_LED\_OFF**
  * **Events::EV\_LED\_TOGGLE**
  * **Events::EV\_LED\_BLINK**
  * **Events::EV\_LED\_FADEIN**
  * **Events::EV\_LED\_FADEOUT**