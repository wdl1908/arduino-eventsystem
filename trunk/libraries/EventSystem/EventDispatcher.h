/**
 * File: EventDispatcher.h
 *
 * About:
 *     Part of Arduino Event System.
 *
 * Authors:
 *     Marcello Romani     mromani@ottotecnica.com
 *     Willy De la Court   wdlarduino@linux-lovers.be
 *
 * Version:
 *     1.1
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
 *    1.1 2011-06-29 - Willy De la Court : Doc changes
 *    1.0 2010-07-14 - Marcello Romani : Initial Version
 *
 */

#ifndef EVENTDISPATCHER_H
#define EVENTDISPATCHER_H

#include <WProgram.h>
#include <Events.h>
#include <EventQueue.h>

/**
* Function: EventListener
 *     <EventListener> function prototype.
 *
 * Parameters:
 *     ev_code  - <Events> code
 *     ev_param - Value associated with the Event
 */
typedef void (*EventListener)(int ev_code, int ev_param);

/**
 * Class: EventDispatcher
 *
 */
class EventDispatcher {

	public:
		/**
		* Constant: MAX_LISTENERS
		*     Maximum number of event/callback entries
		*     can be changed to save memory or allow more events to be dispatched.
		*/
		static const int MAX_LISTENERS = 20;

		/**
		* Enumerations: OverwriteOption
		*     ALWAYS_APPEND   - Just add ev_code/f to the list.
		*     OVERWRITE_EVENT - If a <EventListener> with the same <Events> is found, 
		*                       replace its function with f.
		*/
		enum OverwriteOption { ALWAYS_APPEND, OVERWRITE_EVENT };

		/**
		 * Constructor: EventDispatcher
		 *     A dispatcher is used to process events of a particular queue.
		 */
		EventDispatcher(EventQueue* evQueue);

		/**
		 * Method: addEventListener
		 *     The function f will be called when event ev_code will be dequeued
		 *
		 * Parameters:
		 *     ev_code   - <Events> code.
		 *     f         - <EventListener> function to call when event is dequeued.
		 *     overwrite - <OverwriteOption> Overwrite or append the <EventListener> default is append.
		 *
		 * Returns:
		 *     Returns *true* if the <EventListener> is successfully installed,
		 *     *false* otherwise (e.g. the dispatch table is full)
		 */
		boolean addEventListener(int ev_code, EventListener f, OverwriteOption overwrite = ALWAYS_APPEND);

		/**
		 * Method: removeEventListener
		 *     Remove <EventListener> other listeners with the same function
		 *     or ev_code will not be affected
		 *
		 * Parameters:
		 *     ev_code   - <Events> code.
		 *     f         - <EventListener> function to call when event is dequeued.
		 */
		boolean removeEventListener(int ev_code, EventListener f);

		/**
		 * Method: enableEventListener
		 *     Enable or disable a <EventListener>
		 *
		 * Parameters:
		 *     ev_code   - <Events> code.
		 *     f         - <EventListener> function to call when event is dequeued.
		 *     enable    - Enable or disable.
		 *
		 * Returns:
		 *     Returns *true* if the <EventListener> was successfully enabled or disabled,
		 *     *false* if the <EventListener> was not found
		*/
		boolean enableEventListener(int ev_code, EventListener f, boolean enable);

		/**
		 * Function: isEventListenerEnabled
		 *     Check if a <EventListener> is enabled.
		 *
		 * Parameters:
		 *     ev_code   - <Events> code.
		 *     f         - <EventListener> function to call when event is dequeued.
		 *
		 * Returns:
		 *     Returns *true* if the <EventListener> is enabled and *false* if it is disabled.
		*/
		boolean isEventListenerEnabled(int ev_code, EventListener f);

		/**
		 * Method: setDefaultListener
		 *    The default <EventListener> is a callback function that is called when
		 *    an <Events> with no <EventListener> is dequeued
		 *
		 * Parameters:
		 *     f         - <EventListener> function to call when event is dequeued.
		 */
		boolean setDefaultListener(EventListener f);

		/**
		 * Method: removeDefaultListener
		 *    Remove the default <EventListener>
		 */
		void removeDefaultListener();

		/**
		 * Method: removeEventListener
		 *     Enable or disable the default <EventListener>
		 *
		 * Parameters:
		 *     enable    - Enable or disable.
		 */
		void enableDefaultListener(boolean enable);

		/**
		 * Procedure: run
		 *     This must be continuously called (in loop()).
		 */
		void run();

		/**
		 * Function: getNumEntries
		 *     Get the current number of entries in the dispatch table.
		 *
		 * Returns:
		 *     Returns the number of <EventListener> in the dispatch table.
		 */
		int getNumEntries() { return numListeners; }

		/**
		 * Function: getEventQueue
		 *     Get a reference to the underlying event queue.
		 *
		 * Returns:
		 *     Returns <EventQueue>
		 */
		EventQueue* getEventQueue() { return q; }

	private:
		/**
		 * Property: q
		 *     <EventQueue> to be managed.
		 */
		EventQueue* q;

		/**
		 * Property: numListeners
		 *     Actual number of <EventListener> elements registered.
		 */
		int numListeners;

		/**
		 * Property: callback
		 *     Pointers to <EventListener> callback functions.
		 */
		EventListener callback[MAX_LISTENERS];

		/**
		 * Property: eventCode
		 *     Each <EventListener> observes a specific <Events> type.
		 */
		int eventCode[MAX_LISTENERS];

		/**
		 * Property: enabled
		 *     Each <EventListener> can be enabled or disabled.
		 */
		boolean enabled[MAX_LISTENERS];

		/**
		 * Property: defaultCallback
		 *     Callback function to be called for event types
		 *     which have no <EventListener>.
		 */
		EventListener defaultCallback;

		/**
		 * Property: defaultCallbackEnabled
		 *     once set, the default callback function can be 
		 *     enabled or disabled.
		 */
		boolean defaultCallbackEnabled;

		/**
		 * Method: _searchEventListener
		 *     Search for a specific <Events> and <EventListener>
		 *
		 * Parameters:
		 *     ev_code   - <Events> code.
		 *     f         - <EventListener> function to call when event is dequeued.
		 *
		 * Returns:
		 *     Returns the array index of the specified <EventListener>
		 *     or -1 if no such event/function couple is found.
		*/
		int _searchEventListener(int ev_code, EventListener f);

		/**
		 * Method: _searchEventCode
		 *     Search for a specific <Events>
		 *
		 * Parameters:
		 *     ev_code   - <Events> code.
		 *
		 * Returns:
		 *     Returns the array index of the specified <EventListener>
		 *     or -1 if no such event is found.
		*/
		int _searchEventCode(int ev_code);
};

#endif
