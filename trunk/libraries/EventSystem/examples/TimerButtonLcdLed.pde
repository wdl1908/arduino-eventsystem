/**
 * @file: TimerButtonLcdLed.pde
 *
 * @about Part of Arduino Event System.
 *
 * @author Willy De la Court
 *
 * @version 1.0
 *
 * @copyright (c) 2011 Willy De la Court, Belgium
 *
 * @license
 *
 * This library is free software; you can redistribute it
 * and/or modify it under the terms of the GNU Lesser
 * General Public License as published by the Free Software
 * Foundation; either version 2.1 of the License, or (at
 * your option) any later version.
 *
 * This library is distributed in the hope that it will
 * be useful, but WITHOUT ANY WARRANTY; without even the
 * implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE.  See the GNU Lesser General Public
 * License for more details.
 *
 * You should have received a copy of the GNU Lesser
 * General Public License along with this library; if not,
 * write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
 *
 * @changelog
 *    - 1.0 2011-07-08 - Willy De la Court : Initial Version
 *
 */

#include <EventSystem.h>
#include <EventButton.h>
#include <EventTimer.h>
#include <EventLed.h>
#include <LiquidCrystal.h>

// Buttons need to be connected to GND
#define BUTTON_UP     6
#define BUTTON_DOWN   7
#define BUTTON_RESET  8

// Led must be connected to GND and serie resistor
#define LED           10

EventButton btnDown  = EventButton(BUTTON_DOWN, HOLD_TIME, REPEAT_TIME);
EventButton btnUp    = EventButton(BUTTON_UP,   HOLD_TIME, REPEAT_TIME);
EventButton btnReset = EventButton(BUTTON_RESET);
// Connect a Led on pin 10
EventPWMLed led = EventPWMLed(LED, LED_FADETIME, LED_BLINKTIME, LED_BLINKTIME);

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

