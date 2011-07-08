/*
*/
#include <EventSystem.h>
#include <EventButton.h>
#include <EventTimer.h>
#include <EventAnalog.h>
#include <EventLed.h>
#include <LiquidCrystal.h>

#define BUTTON_DOWN  6
#define BUTTON_UP    7
#define BUTTON_RESET 8

#define HOLD_TIME   1000
#define REPEAT_TIME 400

EventButton btnDown  = EventButton(BUTTON_DOWN, HOLD_TIME, REPEAT_TIME);
EventButton btnUp    = EventButton(BUTTON_UP,   HOLD_TIME, REPEAT_TIME);
EventButton btnReset = EventButton(BUTTON_RESET);
// Connect a Led on pin 10
EventLed led = EventLed(10, 2000, 250, 250);

EventTimer secs = EventTimer(Events::EV_TIME, 1000);

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
int count;
int timecount;

void timerHandler(byte event, int param) {
	timecount = param;
	systemEventQueue.enqueueEvent(Events::EV_PAINT, 0);
}

void lcdHandler(byte event, int param) {
	lcd.setCursor(0, 1);
	lcd.print(timecount);
	lcd.print(" ");
	lcd.print(count);
	lcd.print("   ");
}

void buttonHandler(byte event, int param) {

	if(event == Events::EV_BUTTON_PRESS) {

		switch (param) {
			case BUTTON_UP:
				systemEventQueue.enqueueEvent(Events::EV_LED_BLINK, 10);
				count++;
				break;

			case BUTTON_DOWN:
				systemEventQueue.enqueueEvent(Events::EV_LED_TOGGLE, 10);
				count--;
				break;

			case BUTTON_RESET:
				systemEventQueue.enqueueEvent(Events::EV_LED_OFF, 10);
				count = 0;
				break;
		}
		systemEventQueue.enqueueEvent(Events::EV_PAINT, 0);
	}
}

void setup() {
	lcd.begin(16, 2);
	// Print a message to the LCD.
	lcd.print("hello, world!");
	count = 0;
	systemEventDispatcher.addEventListener(Events::EV_BUTTON_PRESS, buttonHandler);
	systemEventDispatcher.addEventListener(Events::EV_TIME, timerHandler);
	systemEventDispatcher.addEventListener(Events::EV_PAINT, lcdHandler);
}

void loop() {
	systemEventDispatcher.run();
}

