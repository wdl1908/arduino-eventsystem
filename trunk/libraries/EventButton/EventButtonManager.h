/**
 * File: EventButtonManager.h
 *
 * About:
 *     Part of Arduino Event System.
 *
 * Author:
 *     Willy De la Court
 *
 * Version:
 *     1.1
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
 *    1.1 2011-06-30 - Willy De la Court : Code cleanup
 *    1.0 2011-06-29 - Willy De la Court : Initial Version
 *
 */

#ifndef EVENTBUTTONMANAGER_H
#define EVENTBUTTONMANAGER_H

#include "WProgram.h"
#include <EventButton.h>

class EventButtonManager {
	public:
		/**
		* Constant: MAX_BUTTONS
		*     Maximum number of <EventButton> entries
		*     can be changed to save memory or allow more buttons to be registered.
		*/
		static const byte MAX_BUTTONS = 20;

		/**
		 * Constructor: EventButtonManager
		 *
		 */
		EventButtonManager();

		/**
		 * Method: addEventListener
		 *     The function f will be called when event ev_code will be dequeued
		 *
		 * Parameters:
		 *     button - <EventButton> pointer.
		 *
		 * Returns:
		 *     Returns *true* if the <EventButton> is successfully installed,
		 *     *false* otherwise (e.g. the buttons table is full)
		 */
		boolean addEventButton(EventButton *button);

		/**
		 * Procedure: run
		 *     This must be continuously called (in loop()).
		 */
		void run();
	private:
		/**
		 * Property: numButtons
		 *     Actual number of <EventButton> elements registered.
		 */
		byte numButtons;

		/**
		 * Property: buttons
		 *     Pointers to <EventButton> elements.
		 */
		EventButton *buttons[MAX_BUTTONS];

};

/**
 * Variable: eventButtonManager
 *     The system <EventButtonManager>
 */
extern EventButtonManager eventButtonManager;

#endif
