/**
 * File: EventTimer.h
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
 *    1.0 2011-06-30 - Willy De la Court : Initial Version
 *
 */

#include <EventSystem.h>
#include <EventElement.h>

#ifndef EVENTTIMER_H
#define EVENTTIMER_H

/**
 * Class: EventTimer
 *     Generates press/release events.
 *
 */
class EventTimer : public EventElement {
	public:
		/**
		 * Constructor: EventTimer
		 *     Create an timer object.
		 *
		 * Parameters:
		 *     eventCode     - <Event> to add in the queue when interval expires.
		 *     timerInterval - Timer interval.
		 */
		EventTimer(byte eventCode, unsigned int timerInterval = 1000);
		
		/**
		 * Method: Check
		 *     Check the timer and generate an <Event> when the timer count expires.
		 */
		virtual void Check();

	private:
		/**
		 * Property: event
		 *     <Event> to add in the <EventQueue> when interval expires.
		 */
		byte event;

		/**
		 * Property: interval
		 *     Timer interval.
		 */
		unsigned int interval;

		/**
		 * Property: lastTimerEvent
		 *     The last time the timer has fired an <Event>.
		 */
		unsigned long lastTimerEvent;
};

#endif
