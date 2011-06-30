/**
 * File: EventManager.cpp
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

#include <EventManager.h>

EventManager::EventManager() {
	numElements = 0;
}

boolean EventManager::addEventElement(EventElement *element) {

	// argument check
	if (element == 0) {
		return false;
	}

	// element table is full
	if (numElements == MAX_ELEMENTS) {
		return false;
	}
	
	elements[numElements] = element;
	numElements++;
	return true;
}

void EventManager::run() {
	byte i;
	
	for (i = 0; i < numElements; i++) {
		elements[i]->Check();
	}
}
