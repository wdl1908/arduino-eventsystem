#include <Events.h>
#include <EventQueue.h>
#include <EventDispatcher.h>

// the event queue
EventQueue q;

// the event dispatcher
EventDispatcher disp(&q);

// time event handler
void timeHandler(int event, int param) {
    Serial.print("Time elapsed: ");
    Serial.println(millis() / 1000);
}

// this function generates an EV_TIME event
// each 1000 ms
void timeManager() {
    static unsigned long prevMillis = 0;
    unsigned long currMillis = millis();
    if (currMillis - prevMillis >= 1000) {
        prevMillis = currMillis;
        q.enqueueEvent(Events::EV_TIME, 0);    // param is not used here
    }
}

// program setup
void setup() {
    Serial.begin(115200);
    
    // make the dispatcher call timeHandler function
    // when an EV_TIME occurs
    disp.addEventListener(Events::EV_TIME, timeHandler);
}

// loop
void loop() {
    // call the event generating function
    timeManager();

    // get events from the queue and call the
    // registered function(s)
    disp.run();
}
 
