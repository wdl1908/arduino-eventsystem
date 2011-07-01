/**
 * @file EventTimer.h
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
#include <EventElement.h>

#ifndef EVENTTIMER_H
#define EVENTTIMER_H

/**
 * Generates timer Events.
 */
class EventTimer : public EventElement {
	public:
		/**
		 * Create an EventTimer object.
		 *
		 * @param eventCode      Events to add in the queue when interval expires.
		 * @param timerInterval  Timer interval.
		 */
		EventTimer(byte eventCode, unsigned int timerInterval = 1000);
		
		/**
		 * Check the timer and generate an Event when the timer count expires.
		 */
		virtual void Check();

	private:
		byte event;                   ///< Events to add in the EventQueue when interval expires.
		unsigned int interval;        ///< Timer interval.
		unsigned long lastTimerEvent; ///< The last time the timer has fired an Events.
};

#endif
