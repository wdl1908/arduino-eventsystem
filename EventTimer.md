# EventTimer #

Generate timer events for a set interfval.


## Construct a Timer Object ##

```
EventTimer timer = EventTimer(Events::EV_TIME, 2000);
```

## Parameters ##

  * **eventCode**      Events to add in the queue when interval expires.
  * **timerInterval**  Timer interval.

## Events Generated ##

  * **Events::EV\_TIME**