 /**
 * @file EventButton.cpp
 *
 * @about Part of Arduino Event System.
 *
 * @author Willy De la Court
 *
 * @version 1.2
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
 *    - 1.3 2011-07-07 - Willy De la Court : Comments and params for press release events
 *    - 1.2 2011-06-30 - Willy De la Court : Added EventElement inheritance
 *    - 1.1 2011-06-30 - Willy De la Court : Code cleanup
 *    - 1.0 2011-06-29 - Willy De la Court : Initial Version
 *
 */

#include <EventSystem.h>
#include <EventButton.h>

EventButton::EventButton(
		byte buttonPin,
		unsigned int buttonHoldTime,
		unsigned int buttonRepeatTime,
		byte pressEvent,
		byte releaseEvent
	):EventElement() {

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
	
	// Set press / release event codes.
	press = pressEvent;
	release = releaseEvent;
}

void EventButton::Check() {
	unsigned long time;
	
	time = millis();
	// Check if in repeat mode and the timer exired
	if (repeatTime != 0 && changeTime != 0 && changeTime < time) {
		// Simulate a button release
		stateCurrent = false;
		statePrevious = false;
		stateRepeat = true;
	}

	statePrevious = stateCurrent;
	if (digitalRead(pin)) {
		// If the pin is High the button is not pressed.
		stateCurrent = false;
		stateRepeat = false;
		changeTime = 0;
	} else {
		// If the pin is Low the button is pressed.
		stateCurrent = true;
	}
	if (stateCurrent != statePrevious) {
		// Do we need to repeat?
		if (stateCurrent && repeatTime != 0) {
			// Is this the first time the repeat action is called for?
			if (stateRepeat) {
				changeTime = time + repeatTime;
			} else {
				changeTime = time + holdTime;
			}
		}
		// Send events when the status changes
		if (stateCurrent) {
			systemEventQueue.enqueueEvent(press, (int)pin);
		} else {
			systemEventQueue.enqueueEvent(release, (int)pin);
		}
	}
}
