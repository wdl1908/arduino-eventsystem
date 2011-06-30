/**
 * File: EventQueue.cpp
 *
 * About:
 *     Part of Arduino Event System.
 *
 * Authors:
 *     Marcello Romani     mromani@ottotecnica.com
 *     Willy De la Court   wdlarduino@linux-lovers.be
 *
 * Version:
 *     1.2
 *
 * Copyright:
 *     (c) 2010 OTTOTECNICA Italy
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
 *    1.2 2011-06-30 - Willy De la Court : Code cleanup
 *    1.1 2011-06-29 - Willy De la Court : Doc changes
 *    1.0 2010-07-14 - Marcello Romani : Initial Version
 *
 */

#include <EventQueue.h>

EventQueue::EventQueue() {
	eventQueueHead = 0;
	eventQueueTail = EVQUEUE_SIZE - 1;
	numEvents = 0;
}


boolean EventQueue::isEmpty() {
	return (numEvents == 0);
}


boolean EventQueue::isFull() {
	return (eventQueueHead == eventQueueTail);
}


byte EventQueue::getNumEvents() {
	return numEvents;
}


boolean EventQueue::enqueueEvent(byte ev_code, int ev_param) {

	if (isFull()) {
		// log the queue full error
		// Serial.print(millis());
		// Serial.println(" QUEUE FULL");
		return false;
	}
	
	// store the event
	eventQueue[eventQueueHead] = ev_code;
	eventParam[eventQueueHead] = ev_param;
	
	// update queue head value
	eventQueueHead = (eventQueueHead + 1) % EVQUEUE_SIZE;;
	
	// update number of events in queue
	numEvents++;
	
	return true;
}


boolean EventQueue::dequeueEvent(byte* ev_code, int* ev_param) {

	if (numEvents == 0) {
		return false;
	}
	
	eventQueueTail = (eventQueueTail + 1) % EVQUEUE_SIZE;
	
	// store event code and event parameter
	// into the user-supplied variables
	*ev_code = eventQueue[eventQueueTail];
	*ev_param = eventParam[eventQueueTail];
	
	// update number of events in queue
	numEvents--;

	return true;
}
