/**
 * @file EventDispatcher.h
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

#ifndef EVENTDISPATCHER_H
#define EVENTDISPATCHER_H

#include <WProgram.h>
#include <Events.h>
#include <EventQueue.h>

/**
 * EventListener function prototype.
 *
 * @param ev_code  Events code
 * @param ev_param Value associated with the Event
 */
typedef void (*EventListener)(byte ev_code, int ev_param);

/**
 * EventDispatcher
 */
class EventDispatcher {

	public:
		static const byte MAX_LISTENERS = 20; ///< Maximum number of event/callback entries
		                                      ///< can be changed to save memory or allow more events to be dispatched.
		enum OverwriteOption { 
			ALWAYS_APPEND,     ///< Just add ev_code/f to the list.
			OVERWRITE_EVENT    ///< If a EventListener with the same Events is found, 
		                       ///< replace its function with f.
		};

		/**
		 * A dispatcher is used to process events of a particular queue.
		 */
		EventDispatcher(EventQueue* evQueue);

		/**
		 * The function f will be called when event ev_code will be dequeued
		 *
		 * @param ev_code   Events code.
		 * @param f         EventListener function to call when event is dequeued.
		 * @param overwrite Overwrite or append the <ventListener default is append.
		 *
		 * @return Returns @b true if the EventListener is successfully installed,
		 *         @b false otherwise (e.g. the dispatch table is full)
		 */
		boolean addEventListener(byte ev_code, EventListener f, OverwriteOption overwrite = ALWAYS_APPEND);

		/**
		 * Remove EventListener other listeners with the same function
		 * or ev_code will not be affected
		 *
		 * @param ev_code   Events code.
		 * @param f         EventListener function to call when event is dequeued.
		 */
		boolean removeEventListener(byte ev_code, EventListener f);

		/**
		 * Enable or disable a EventListener
		 *
		 * @param ev_code   Events code.
		 * @param f         EventListener function to call when event is dequeued.
		 * @param enable    Enable or disable.
		 * @return Returns @b true if the <EventListener> was successfully enabled or disabled,
		 *         @b false if the <EventListener> was not found
		*/
		boolean enableEventListener(byte ev_code, EventListener f, boolean enable);

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
		boolean isEventListenerEnabled(byte ev_code, EventListener f);

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
		byte getNumEntries() { return numListeners; }

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
		byte numListeners;

		/**
		 * Property: callback
		 *     Pointers to <EventListener> callback functions.
		 */
		EventListener callback[MAX_LISTENERS];

		/**
		 * Property: eventCode
		 *     Each <EventListener> observes a specific <Events> type.
		 */
		byte eventCode[MAX_LISTENERS];

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
		byte _searchEventListener(byte ev_code, EventListener f);

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
		byte _searchEventCode(byte ev_code);
};

#endif
