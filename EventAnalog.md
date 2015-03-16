# EventAnalog #

Generates Analog events when an analog pin changes.

## Construct a Analog Object ##

```
EventAnalog analog = EventAnalog(2, Events::EV_ANALOG0, 10);
```

## Parameters ##

  * **analogPin**       The pin number of the digital pin the button is connected to.
  * **eventCode**       Events to add in the queue when analog pin changes.
  * **hysteresisValue** The value of the analog pin needs to change with this value to generate an Events.


## Events Generated ##

  * **Events::EV\_ANALOG0**