#include <Events.h>
#include <EventQueue.h>
#include <EventDispatcher.h>

// the event queue
EventQueue q;

// the event dispatcher
EventDispatcher disp(&q);

// use this analog channel
#define AN_CHAN 0

// generate an event when the analog
// channel value changes this much
// increase value for noisy sources
#define AN_DELTA 5

// time event handler
void timeHandler(int event, int param) {
    Serial.print("Time elapsed: ");
    Serial.println(millis() / 1000);
}

// analog event handler
void analogHandler(int event, int param) {
    Serial.print("Analog value: ");
    Serial.println(param);
}

// this function generates an EV_TIME event
// each 1000 ms
void timeManager() {
    static unsigned long prevMillis = 0;
    unsigned long currMillis;

    currMillis = millis();
    if (currMillis - prevMillis >= 1000) {
        prevMillis = currMillis;
        q.enqueueEvent(Events::EV_TIME, 0);    // param is not used here
    }
}

// this function generates an EV_ANALOG event
// whenever the analog channel AN_CHAN changes
void analogManager() {
    static int prevValue = 0;
    int currValue;

    currValue = analogRead(AN_CHAN);

    if (abs(currValue - prevValue) >= AN_DELTA) {
        prevValue = currValue;
        q.enqueueEvent(Events::EV_ANALOG0, currValue);    // use param to pass analog value to event handler
    }
}

// program setup
void setup() {
    Serial.begin(115200);
    
    disp.addEventListener(Events::EV_TIME, timeHandler);
    disp.addEventListener(Events::EV_ANALOG0, analogHandler);
}

// loop
void loop() {
    // call the event generating functions
    timeManager();
    analogManager();

    // get events from the queue and call the
    // registered function(s)
    disp.run();
}
