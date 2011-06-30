/**
 * File: EventButton.h
 *
 * About:
 *     Part of Arduino Event System.
 *
 * Author:
 *     Willy De la Court
 *
 * Version:
 *     1.2
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
 *    1.2 2011-06-30 - Willy De la Court : Added EventElement inheritance
 *    1.1 2011-06-30 - Willy De la Court : Code cleanup
 *    1.0 2011-06-29 - Willy De la Court : Initial Version
 *
 */

#include <EventSystem.h>
#include <EventElement.h>

#ifndef EVENTBUTTON_H
#define EVENTBUTTON_H

/**
 * Constant: HOLD_TIME
 *     Time a button needs to be pressed before going into repeat mode.
 */
#define HOLD_TIME   1000

/**
 * Constant: REPEAT_TIME
 *     Time between repeat.
 */
#define REPEAT_TIME 400

/**
 * Class: EventButton
 *     Generates press/release events.
 *
 */
class EventButton : public EventElement {
	public:
		/**
		 * Constructor: EventButton
		 *     Create an button object.
		 *
		 * Parameters:
		 *     buttonPin  - The pin number of the digital pin the button is connected to.
		 *     HoldTime   - The time to wait until the button is considered in the hold state.
		 *     RepeatTime - The time between repeats.
		 */
		EventButton(byte buttonPin, unsigned int HoldTime = 0, unsigned int RepeatTime = 0);
		
		/**
		 * Method: Check
		 *     Check the button and generate events when the button state changes.
		 */
		virtual void Check();

	private:
		/**
		 * Property: pin
		 *     Pin number of the arduino board.
		 */
		byte pin;

		/**
		 * Property: stateCurrent
		 *     Current state of the button.
		 */
		unsigned stateCurrent  : 1;

		/**
		 * Property: statePrevious
		 *     Previous state of the button.
		 */
		unsigned statePrevious : 1;

		/**
		 * Property: stateRepeat
		 *     Is the button repeating.
		 */
		unsigned stateRepeat   : 1;

		/**
		 * Property: holdTime
		 *     Time to wait before going into repeat mode.
		 */
		unsigned int holdTime;

		/**
		 * Property: repeatTime
		 *     Time to wait between repeats.
		 */
		unsigned int repeatTime;

		/**
		 * Property: changeTime
		 *    Last time the button changed state.
		 */
		unsigned long changeTime;
};

#endif
