/**
 * @file EventLed.cpp
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
 *    - 1.0 2011-07-02 - Willy De la Court : Initial Version
 *
 */

#include <EventSystem.h>
#include <EventLed.h>

EventLed::EventLed(
		byte ledPin,
		int ledBlinkOnTime,
		int ledBlinkOffTime
	):EventElement() {

	// Set the pin to output
	pin = ledPin;
	pinMode(pin, OUTPUT);
	
	// Turn the led off
	Off();
	blinkOnTime = ledBlinkOnTime;
	blinkOffTime = ledBlinkOffTime;
}

void EventLed::Check() {
	int timeElapsed;
	byte newState;
	unsigned long time;

	if (lastEvent == Events::EV_LED_BLINK) {
		time = millis();
		if (isOn() && startTime + blinkOnTime < time) {
			state = LED_OFF;
			digitalWrite(pin, state);
			startTime = time;
		} else if (isOff() && startTime + blinkOffTime < time) {
			state = LED_ON;
			digitalWrite(pin, state);
			startTime = time;
		}
	}
}

void EventLed::HandleEvent(byte event, int param) {
	if (event >= Events::EV_LED_ON ||
		event <= Events::EV_LED_BLINK) {
		
		if (param == pin) {
			switch (event) {
				case Events::EV_LED_ON:
					On();
					break;

				case Events::EV_LED_OFF:
					Off();
					break;

				case Events::EV_LED_TOGGLE:
					Toggle();
					break;

				case Events::EV_LED_BLINK:
					Blink();
					break;
			}
		}
	}
}

void EventLed::On() {
	state = LED_ON;
	digitalWrite(pin, state);
	lastEvent = Events::EV_LED_ON;
}

void EventLed::Off() {
	state = LED_OFF;
	digitalWrite(pin, state);
	lastEvent = Events::EV_LED_OFF;
}

void EventLed::Toggle() {
	if (isOn()) {
		Off();
	} else {
		On();
	}
}

void EventLed::Blink() {
	state = LED_ON;
	digitalWrite(pin, state);
	startTime = millis();
	lastEvent = Events::EV_LED_BLINK;
}

