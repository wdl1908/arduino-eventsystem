/**
 * @file EventAnalog.cpp
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
 *    - 1.0 2011-06-30 - Willy De la Court : Initial Version
 *
 */

#include <EventSystem.h>
#include <EventAnalog.h>

EventAnalog::EventAnalog(
		byte analogPin, 
		byte eventCode, 
		int hysteresisValue
	):EventElement() {

	// Set the pin to input
	pin = analogPin;
	pinMode(pin, INPUT);

	event = eventCode;
	hysteresis = hysteresisValue;
	lastValue = -9999; // Force first event
}

void EventAnalog::Check() {
	int currentValue;

	currentValue = analogRead(pin);
	
	// Check if the currect value of the analog pin falls outside the range of the hysteresis.
	if (currentValue < lastValue - hysteresis || currentValue > lastValue + hysteresis) {
		lastValue = currentValue;
		systemEventQueue.enqueueEvent(event, currentValue);
	}
}
