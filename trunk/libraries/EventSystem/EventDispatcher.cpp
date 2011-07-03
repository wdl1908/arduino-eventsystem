/**
 * @file EventDispatcher.cpp
 *
 * @about Part of Arduino Event System.
 *
 * @authors
 *     Marcello Romani     mromani@ottotecnica.com
 *     Willy De la Court   wdlarduino@linux-lovers.be
 *
 * @version 1.2
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
 *    - 1.2 2011-06-30 - Willy De la Court : Code cleanup
 *    - 1.1 2011-06-29 - Willy De la Court : Doc changes
 *    - 1.0 2010-07-14 - Marcello Romani : Initial Version
 *
 */

#include <EventDispatcher.h>

EventDispatcher::EventDispatcher(EventQueue* evQueue) {

	q = evQueue;
	numListeners = 0;
	head = 0;
	tail = 0;
}

boolean EventDispatcher::addEventElement(EventElement *element) {

	// argument check
	if (element == 0) {
		return false;
	}

	element->next = 0;
	if (head == 0) {
		head = element;
		tail = element;
	} else {
		tail->next = element;
		tail = element;
	}
	return true;
}

boolean EventDispatcher::addEventListener(byte event, EventListener f, OverwriteOption overwrite) {
	char k;
	
	// argument check
	if (f == 0) {
		return false;
	}
	
	if (overwrite == OVERWRITE_EVENT) {
		k = _searchEventCode(event);
		if (k >= 0) {           // event code found
			callback[k] = f;    // replace function
			enabled[k] = true;  // it's an add(), so enable the listener
			return true;
		}
	}
	
	// APPEND or (OVERWRITE and NOT FOUND)
	
	// dispatch table is full
	if (numListeners == MAX_LISTENERS) {
		return false;
	}
	
	callback[numListeners] = f;
	eventCode[numListeners] = event;
	enabled[numListeners] = true;
	
	numListeners++;

	return true;
}


boolean EventDispatcher::removeEventListener(byte event, EventListener f) {
	byte i;
	char k;

	if (numListeners == 0) {
		return false;
	}

	k = _searchEventListener(event, f);
	if (k < 0) {
		return false;
	}
	
	for (i = k; i < numListeners - 1; i++) {
		callback[i] = callback[i + 1];
		eventCode[i] = eventCode[i + 1];
		enabled[i] = enabled[i + 1];
	}

	numListeners--;

	return true;
}


boolean EventDispatcher::enableEventListener(byte event, EventListener f, boolean enable) {
	char k;
	
	if (numListeners == 0) {
		return false;
	}
	
	k = _searchEventListener(event, f);
	if (k < 0) {
		return false;
	}

	enabled[k] = enable;

	return true;
}


boolean EventDispatcher::isEventListenerEnabled(byte event, EventListener f) {
	char k;

	if (numListeners == 0) {
		return false;
	}

	k = _searchEventListener(event, f);
	if (k < 0) {
		return false;
	}

	return enabled[k];
}


void EventDispatcher::run() {
	byte event;
	int param;
	byte i;
	boolean handlerFound;
	EventElement *element;

	// Start checking all the registered EventElement entries.
	element = head;
	while (element) {
		element->Check();
		element = element->next;
	}

	// Process all the added Events and dispatches them to the registered EventListener.
	handlerFound = false;

	if (q->dequeueEvent(&event, &param)) {
		for (i = 0; i < numListeners; i++) {
			if ((callback[i] != 0) && (eventCode[i] == event) && enabled[i]) {
				handlerFound = true;
				(*callback[i])(event, param);
			}
		}

		if (!handlerFound) {
			if ((defaultCallback != 0) && (defaultCallbackEnabled)) {
				(*defaultCallback)(event, param);
			}
		}
	}
}


boolean EventDispatcher::setDefaultListener(EventListener f) {
	
	if (f == 0) {
		return false;
	}

	defaultCallback = f;
	defaultCallbackEnabled = true;
	return true;
}


void EventDispatcher::removeDefaultListener() {
	
	defaultCallback = 0;
	defaultCallbackEnabled = false;
}


void EventDispatcher::enableDefaultListener(boolean enable) {
	
	defaultCallbackEnabled = enable;
}


char EventDispatcher::_searchEventListener(byte event, EventListener f) {
	byte i;

	for (i = 0; i < numListeners; i++) {
		if ((eventCode[i] == event) && (callback[i] == f)) {
			return i;
		}
	}

	return -1;
}


char EventDispatcher::_searchEventCode(byte event) {
	byte i;

	for (i = 0; i < numListeners; i++) {
		if (eventCode[i] == event) {
			return i;
		}
	}

	return -1;
}
