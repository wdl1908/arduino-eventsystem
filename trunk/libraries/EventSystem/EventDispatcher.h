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
#include <EventElement.h>

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
		static const byte MAX_LISTENERS = 20; ///< Maximum number of Events/EventListener entries
		                                      ///< can be changed to save memory or allow more events to be dispatched.
		static const byte MAX_ELEMENTS = 20;  ///< Maximum number of EventElement entries
		                                      ///< can be changed to save memory or allow more elements to be registered.

		/**
		 * Enum for addEventListener
		 */
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
		 * Add an EventElement to the processing list.
		 *
		 * @param element EventButton pointer.
		 *
		 * @return Returns @b true if the EventElement is successfully installed,
		 *         @b false otherwise (e.g. the elements table is full)
		 */
		boolean addEventElement(EventElement *element);

		/**
		 * The function f will be called when event ev_code will be dequeued
		 *
		 * @param ev_code   Events code.
		 * @param f         EventListener function to call when event is dequeued.
		 * @param overwrite Overwrite or append the EventListener default is append.
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
		 * @return Returns @b true if the EventListener was successfully enabled or disabled,
		 *         @b false if the EventListener was not found
		*/
		boolean enableEventListener(byte ev_code, EventListener f, boolean enable);

		/**
		 * Check if a EventListener is enabled.
		 *
		 * @param ev_code   Events code.
		 * @param f         EventListener function to call when event is dequeued.
		 *
		 * @return Returns @b true if the EventListener is enabled and @b false if it is disabled.
		*/
		boolean isEventListenerEnabled(byte ev_code, EventListener f);

		/**
		 * The default EventListener is a callback function that is called when
		 * an Events with no EventListener is dequeued
		 *
		 * @param f         EventListener function to call when event is dequeued.
		 */
		boolean setDefaultListener(EventListener f);

		/**
		 * Remove the default EventListener
		 */
		void removeDefaultListener();

		/**
		 * Enable or disable the default EventListener
		 *
		 * @param enable    Enable or disable.
		 */
		void enableDefaultListener(boolean enable);

		/**
		 * This must be continuously called (in loop()).
		 */
		void run();

		/**
		 * Get the current number of entries in the dispatch table.
		 *
		 * @return Returns the number of EventListener in the dispatch table.
		 */
		byte getNumEntries() { return numListeners; }

		/**
		 * Get a reference to the underlying event queue.
		 *
		 * @return Returns EventQueue
		 */
		EventQueue* getEventQueue() { return q; }

	private:
		EventQueue* q;                         ///< EventQueue to be managed.
		byte numListeners;                     ///<  Actual number of EventListener elements registered.
		EventListener callback[MAX_LISTENERS]; ///< Pointers to EventListener callback functions.
		byte eventCode[MAX_LISTENERS];         ///< Each EventListener observes a specific Events type.
		boolean enabled[MAX_LISTENERS];        ///< Each EventListener can be enabled or disabled.
		EventListener defaultCallback;         ///< Callback function to be called for event types which have no EventListener.
		boolean defaultCallbackEnabled;        ///< once set, the default callback function can be enabled or disabled.
		byte numElements;                      ///< Actual number of EventElement elements registered.
		EventElement *elements[MAX_ELEMENTS];  ///< Pointers to EventElement elements.

		/**
		 * Search for a specific Events and EventListener
		 *
		 * @param ev_code   Events code.
		 * @param f         EventListener function to call when event is dequeued.
		 *
		 * @return Returns the array index of the specified EventListener
		 *         or -1 if no such event/function couple is found.
		*/
		byte _searchEventListener(byte ev_code, EventListener f);

		/**
		 * Search for a specific Events
		 *
		 * @param ev_code   Events code.
		 *
		 * @return Returns the array index of the specified EventListener
		 *         or -1 if no such event is found.
		*/
		byte _searchEventCode(byte ev_code);
};

#endif
