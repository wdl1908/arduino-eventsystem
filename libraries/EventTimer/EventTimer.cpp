/**
 * @file EventTimer.cpp
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
#include <EventTimer.h>

EventTimer::EventTimer(byte eventCode, unsigned int timerInterval):EventElement() {

	event = eventCode;
	interval = timerInterval;
	lastTimerEvent = millis();
}

void EventTimer::Check() {
	unsigned long time;
	
	time = millis();
	if (lastTimerEvent + interval < time) {
		lastTimerEvent = time;
		systemEventQueue.enqueueEvent(event, (int) (lastTimerEvent / interval));
	}
}
