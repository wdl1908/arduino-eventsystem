/**
 * @file EventAnalog.h
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

#ifndef EVENTANALOG_H
#define EVENTANALOG_H

/**
 * Generates analog Events.
 */
class EventAnalog : public EventElement {
	public:
		/**
		 * Create an EventAnalog object.
		 *
		 * @param analogPin       The pin number of the digital pin the button is connected to.
		 * @param eventCode       Events to add in the queue when analog pin changes.
		 * @param hysteresisValue The value of the analog pin needs to change with this value to generate an Events.
		 */
		EventAnalog(byte analogPin, byte eventCode, int hysteresisValue);
		
		/**
		 * Check the analog pin and generate an Events when the value falls outside the hysteresis.
		 */
		virtual void Check();

	private:
		byte pin;       ///< Pin number of the arduino board.
		byte event;     ///< Events to add in the EventQueue when analog pin changes.
		int lastValue;  ///< Last value of the analog pin.
		int hysteresis; ///< minimum change needed to generate an Events.
};

#endif
