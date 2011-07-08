/**
 * @file EventQueue.h
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
 *    - 1.1 2011-06-29 - Willy De la Court : Doc changes and 2 new events
 *    - 1.0 2010-07-14 - Marcello Romani : Initial Version
 *
 */

#include <WProgram.h>
#include <Events.h>

#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

/**
 * Stores the events to be processed.
 */
class EventQueue {
	
	public:
		/**
		 * The maximum number of events
		 * the queue can hold is EVQUEUE_SIZE - 1.
		 * Increasing this number will consume sizeof(int) + sizeof(byte)
		 * bytes of RAM for each unit.
		 */
		static const byte EVQUEUE_SIZE = 10;
		
		///  Queue constructor
		EventQueue();
		
		/**
		 * @return
		 *     Returns @b true if no events are in the queue.
		 */
		boolean isEmpty();
		
		/**
		 * @return
		 *     Returns @b true if no more events can be inserted into the queue.
		 */
		boolean isFull();
		
		/**
		 * @return
		 *     Returns the actual number of events in queue.
		 */
		byte getNumEvents();
		
		/**
		 * Tries to insert an event into the queue.
		 *
		 * @param event Events code
		 * @param param Value associated with the Event
		 *
		 * @return
		 *     Returns @b true if successful, @b false if the
		 *     queue is full and the event cannot be inserted.
		 */
		boolean enqueueEvent(byte event, int param = 0);
		
		/**
		 * Tries to extract an event from the queue.
		 *
		 * @param event Events code
		 * @param param Value associated with the Event
		 *
		 * @return
		 *     returns @b true if successful, @b false if the
		 *     queue is empty (the parameters are not touched
		 *     in this case)
		 */
		boolean dequeueEvent(byte* event, int* param);
		
	private:
		byte eventQueue[EVQUEUE_SIZE]; ///< Each event is represented by an byte code.
		int eventParam[EVQUEUE_SIZE];  ///< Each event has a single integer parameter.
		byte eventQueueHead;           ///< Index of event queue head.
		byte eventQueueTail;           ///< Index of event queue tail.
		byte numEvents;                ///< Actual number of events in queue.
};

#endif
