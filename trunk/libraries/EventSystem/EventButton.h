/**
 * File: EventButtons.h
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

#ifndef EVENTBUTTON_H
#define EVENTBUTTON_H

#include "WProgram.h"

/**
 * Class: EventButton
 *     Generates press/release events.
 *
 */
class EventButton {
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
		EventButton(byte buttonPin, int HoldTime = 0, int RepeatTime = 0);
		
		/**
		 * Method: Check
		 *     Check the button and generate events when the button state changes.
		 */
		void Check();

	private:
		/**
		 * Property: pin
		 *     Pin number of the arduino board.
		 */
		uint8_t pin;

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
		uint16_t holdTime;

		/**
		 * Property: repeatTime
		 *     Time to wait between repeats.
		 */
		uint16_t repeatTime;

		/**
		 * Property: changeTime
		 *    Last time the button changed state.
		 */
		unsigned long changeTime;
};

#endif
