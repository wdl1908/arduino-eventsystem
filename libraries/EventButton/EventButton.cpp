/**
 * File: EventButtons.cpp
 *
 * About:
 *     Part of Arduino Event System.
 *
 * Author:
 *     Willy De la Court
 *
 * Version:
 *     1.0
 *
 * Copyright:
 *     (c) 2011 Willy De la Court, Belgium
 *
 * License:
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
 * Changelog:
 *    1.0 2011-06-29 - Willy De la Court : Initial Version
 *
 */

#include <EventSystem.h>

EventButton::EventButton(byte buttonPin, int buttonHoldTime, int buttonRepeatTime) {

	// Set button pin to input
	pin = buttonPin;
	pinMode(pin, INPUT);

	// Activate the internal PullUp resistor
	digitalWrite(pin, HIGH);

	// Reset state of the button
	stateCurrent = false;
	statePrevious = false;
	stateRepeat = false;

	// Set repeat timer values for this button
	holdTime   = buttonHoldTime;
	repeatTime = buttonRepeatTime;
	changeTime = 0;
	eventButtonManager.addEventButton(this);
}

void EventButton::Check(void) {

	if (repeatTime != 0 && changeTime != 0 && changeTime < millis()) {
		stateCurrent = false;
		statePrevious = false;
		stateRepeat = true;
	}

	statePrevious = stateCurrent;
	if (digitalRead(pin)) {
		stateCurrent = false;
		stateRepeat = false;
		changeTime = 0;
	} else {
		stateCurrent = true;
	}
	if (stateCurrent != statePrevious) {
		if (stateCurrent && repeatTime != 0) {
			if (stateRepeat) {
				changeTime = millis() + repeatTime;
			} else {
				changeTime = millis() + holdTime;
			}
		}
		if (stateCurrent) {
			systemEventQueue.enqueueEvent(Events::EV_BUTTON_PRESS, (int)pin);
		} else {
			systemEventQueue.enqueueEvent(Events::EV_BUTTON_RELEASE, (int)pin);
		}
	}
}
