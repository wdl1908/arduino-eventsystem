# EventButton #

A button must be connected to GND one one side and a digital pin on the other side. Internal pull-up resistors are used.


## Construct a Button Object ##

```
EventButton button = EventButton(2);
```

## Parameters ##

  * **buttonPin**        The pin number of the digital pin the button is connected to.
  * **buttonHoldTime**   The time to wait until the button is considered in the hold state, default is 0 (no repeat).
  * **buttonRepeatTime** The time between repeats, default is 0 (no repeat).
  * **pressEvent**       Event to generate when the button is pressed, default is Events::EV\_BUTTON\_PRESS.
  * **releaseEvent**     Event to generate when the button is released, default is Events::EV\_BUTTON\_RELEASE.

## Events Generated ##

  * **Events::EV\_BUTTON\_PRESS**
  * **Events::EV\_BUTTON\_RELEASE**