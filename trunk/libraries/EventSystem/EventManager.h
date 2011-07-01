/**
 * @file EventManager.cpp
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

#include "WProgram.h"
#include <EventElement.h>

#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

/**
 * Stores the elements to be processed.
 */
class EventManager {
	public:
		/**
		* Constant: MAX_ELEMENTS
		*     Maximum number of EventElement entries
		*     can be changed to save memory or allow more elements to be registered.
		*/
		static const byte MAX_ELEMENTS = 20; ///< Maximum number of EventElement entries
		                                     ///< can be changed to save memory or allow more elements to be registered.

		/**
		 * Constructor
		 */
		EventManager();

		/**
		 * Add an EventElement to the processing list.
		 *
		 * @param element EventButton pointer.
		 *
		 * @return Returns @b true if the EventElement is successfully installed,
		 *         @b false otherwise (e.g. the elements table is full)
		 */
		boolean addEventElement(EventElement *element);

		/**
		 * This must be continuously called (in loop()).
		 */
		void run();
	private:
		byte numElements;                     ///< Actual number of EventElement elements registered.
		EventElement *elements[MAX_ELEMENTS]; ///< Pointers to EventElement elements.
};

#endif
