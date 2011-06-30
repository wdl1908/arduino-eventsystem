/**
 * File: EventButtonManager.cpp
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

#include <EventButtonManager.h>

EventButtonManager::EventButtonManager() {
	numButtons = 0;
}

boolean EventButtonManager::addEventButton(EventButton *button) {

	// argument check
	if (button == 0) {
		return false;
	}

	// buttons table is full
	if (numButtons == MAX_BUTTONS) {
		return false;
	}
	
	buttons[numButtons] = button;
	numButtons++;
	return true;
}

void EventButtonManager::run() {
	byte i;
	
	for (i = 0; i < numButtons; i++) {
		buttons[i]->Check();
	}
}

EventButtonManager eventButtonManager;
