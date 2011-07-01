/**
 * @file Events.h
 *
 * @about
 *     Part of Arduino Event System.
 *
 * @authors
 *     Marcello Romani     mromani@ottotecnica.com
 *     Willy De la Court   wdlarduino@linux-lovers.be
 *
 * @version 1.1
 *
 * @copyright (c) 2010 OTTOTECNICA Italy
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
 *    - 1.1 2011-06-29 - Willy De la Court : Doc changes and 2 new events
 *    - 1.0 2010-07-14 - Marcello Romani : Initial Version
 *
 */

#ifndef EVENTS_H
#define EVENTS_H

#include <WProgram.h>

/**
 * Some common events.
 * Codes 0..199 are available for user defined events.
 */
class Events {
	
	public:
		enum eventType {
			EV_NONE = 200,       ///< no event occurred     - param: none
			EV_KEY_PRESS,        ///< a key was pressed     - param: key code
			EV_KEY_RELEASE,      ///< a key was released    - param: key code
			EV_BUTTON_PRESS,     ///< a button was pressed  - param: pin number
			EV_BUTTON_RELEASE,   ///< a button was released - param: pin number
			EV_CHAR,             ///< a character was received - param: the character to be notified
			EV_TIME,             ///< generic time event    - param: a time value
			                     ///< (exact meaning is defined by the code
			                     ///< inserting this event into the queue)
			EV_TIMER0,           ///< generic timer events  - param: same as EV_TIME
			EV_TIMER1,           ///< generic timer events  - param: same as EV_TIME
			EV_TIMER2,           ///< generic timer events  - param: same as EV_TIME
			EV_TIMER3,           ///< generic timer events  - param: same as EV_TIME
			EV_ANALOG0,          ///< analog read (last number = analog channel) - param: value read
			EV_ANALOG1,          ///< analog read (last number = analog channel) - param: value read
			EV_ANALOG2,          ///< analog read (last number = analog channel) - param: value read
			EV_ANALOG3,          ///< analog read (last number = analog channel) - param: value read
			EV_ANALOG4,          ///< analog read (last number = analog channel) - param: value read
			EV_ANALOG5,          ///< analog read (last number = analog channel) - param: value read
			EV_MENU0,
			EV_MENU1,
			EV_MENU2,
			EV_MENU3,
			EV_MENU4,
			EV_MENU5,
			EV_MENU6,
			EV_MENU7,
			EV_MENU8,
			EV_MENU9,
			EV_SERIAL,           ///< serial event - param: the return value of Serial.read()
			EV_PAINT             ///< LCD screen needs to be refreshed - param: none
		};
};

#endif
