# EventLed #

A led must be connected to GND on a digital pin with a serie resistor.


## Construct a Led Object ##

```
EventLed led = EventLed(10);
```

## Parameters ##

  * **ledPin**          The pin number where the led is connected to.
  * **ledBlinkOnTime**  Time the led is on when blinking. Default is 250ms.
  * **ledBlinkOffTime** Time the led is off when blinking. Default is 250ms.

## Events Consumed ##

  * **Events::EV\_LED\_ON**
  * **Events::EV\_LED\_OFF**
  * **Events::EV\_LED\_TOGGLE**
  * **Events::EV\_LED\_BLINK**