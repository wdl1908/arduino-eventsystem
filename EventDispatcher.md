# EventDispatcher #

The EventDispatcher calls every EventElement in the chain to see if nothing has to be done, this includes the following.

  * Check button presses or repeat times on EventButton elements.
  * Check blink time on EventLed elements.
  * Check fade-in fade-out progress of EventPWMLed elements.

The EventDispatcher reads the EventQueue and dispatched the events to all the registered EventElements and to all the registered Handlers.