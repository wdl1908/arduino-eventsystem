/**
 * File: EventManager.h
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

#include "WProgram.h"
#include <EventElement.h>

#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

/**
 * Class: EventManager
 *     Stores the elements to be processed.
 *
 */
class EventManager {
	public:
		/**
		* Constant: MAX_ELEMENTS
		*     Maximum number of <EventElement> entries
		*     can be changed to save memory or allow more elements to be registered.
		*/
		static const byte MAX_ELEMENTS = 20;

		/**
		 * Constructor: EventManager
		 *
		 */
		EventManager();

		/**
		 * Method: addEventElement
		 *     Add an <EventElement> to the processing list.
		 *
		 * Parameters:
		 *     element - <EventButton> pointer.
		 *
		 * Returns:
		 *     Returns *true* if the <EventElement> is successfully installed,
		 *     *false* otherwise (e.g. the elements table is full)
		 */
		boolean addEventElement(EventElement *element);

		/**
		 * Procedure: run
		 *     This must be continuously called (in loop()).
		 */
		void run();
	private:
		/**
		 * Property: numElements
		 *     Actual number of <EventElement> elements registered.
		 */
		byte numElements;

		/**
		 * Property: elements
		 *     Pointers to <EventElement> elements.
		 */
		EventElement *elements[MAX_ELEMENTS];
};

#endif
