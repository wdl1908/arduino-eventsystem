/**
 * File: EventSystem.h
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
 *    1.0 2011-06-29 - Willy De la Court : Initial Version
 *
 */

#ifndef EVENTSYSTEM_h
#define EVENTSYSTEM_h

#include <Events.h>
#include <EventQueue.h>
#include <EventDispatcher.h>
#include <EventButton.h>
#include <EventButtonManager.h>

/**
 * Variable: systemEventQueue
 *     The system <EventQueue>
 */
extern EventQueue systemEventQueue;

/**
* Variable: systemEventDispatcher
*     The system <EventDispatcher>
*/
extern EventDispatcher systemEventDispatcher;

#endif