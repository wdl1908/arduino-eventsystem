/**
 * File: EventQueue.h
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
 *    1.1 2011-06-29 - Willy De la Court : Doc changes and 2 new events
 *    1.0 2010-07-14 - Marcello Romani : Initial Version
 *
 */

#include <WProgram.h>
#include <Events.h>

#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

/**
 * Class: EventQueue
 *     Stores the events to be processed.
 *
 */
class EventQueue {
	
	public:
		/**
		 * Constants: EventQueue
		 *     EVQUEUE_SIZE - Event queue size.
		 *         The maximum number of events
		 *         the queue can hold is EVQUEUE_SIZE - 1.
		 *         Increasing this number will consume 2 * sizeof(int)
		 *         bytes of RAM for each unit.
		 */
		static const byte EVQUEUE_SIZE = 10;
		
		/**
		 * Constructor: EventQueue
		 *     Queue constructor
		 */
		EventQueue();
		
		/**
		 * Function: isEmpty
		 *
		 * Returns:
		 *     Returns *true* if no events are in the queue.
		 */
		boolean isEmpty();
		
		/**
		 * Function: isFull
		 *
		 * Returns:
		 *     Returns *true* if no more events can be inserted into the queue.
		 */
		boolean isFull();
		
		/**
		 * Function: getNumEvents
		 *
		 * Returns:
		 *     Returns the actual number of events in queue.
		 */
		byte getNumEvents();
		
		/**
		 * Method: enqueueEvent
		 *     Tries to insert an event into the queue.
		 *
		 * Parameters:
		 *     ev_code  - <Events> code
		 *     ev_param - Value associated with the Event
		 *
		 * Returns:
		 *     Returns *true* if successful, *false* if the
		 *     queue is full and the event cannot be inserted.
		 */
		boolean enqueueEvent(byte ev_code, int ev_param);
		
		/**
		 * Method: dequeueEvent
		 *     Tries to extract an event from the queue.
		 *
		 * Parameters:
		 *     ev_code  - <Events> code
		 *     ev_param - Value associated with the Event
		 *
		 * Returns:
		 *     returns *true* if successful, *false* if the
		 *     queue is empty (the parameters are not touched
		 *     in this case)
		 */
		boolean dequeueEvent(byte* ev_code, int* ev_param);
		
	private:
		/**
		 * Property: eventQueue
		 *     Each event is represented by an integer code.
		 */
		byte eventQueue[EVQUEUE_SIZE];

		/**
		 * Property: eventParam
		 *     Each event has a single integer parameter.
		 */
		int eventParam[EVQUEUE_SIZE];

		/**
		 * Property: eventQueueHead
		 *     Index of event queue head.
		 */
		byte eventQueueHead;

		/**
		 * Property: eventQueueTail
		 *     Index of event queue tail.
		 */
		byte eventQueueTail;

		/**
		 * Property: numEvents
		 *     Actual number of events in queue.
		 */
		byte numEvents;
};

#endif
