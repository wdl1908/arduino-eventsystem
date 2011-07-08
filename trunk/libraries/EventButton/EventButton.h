 /**
 * @file EventButton.h
 *
 * @about Part of Arduino Event System.
 *
 * @author Willy De la Court
 *
 * @version 1.3
 *
 * @copyright (c) 2011 Willy De la Court, Belgium
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
 *    - 1.3 2011-07-07 - Willy De la Court : Comments and params for press release events
 *    - 1.2 2011-06-30 - Willy De la Court : Added EventElement inheritance
 *    - 1.1 2011-06-30 - Willy De la Court : Code cleanup
 *    - 1.0 2011-06-29 - Willy De la Court : Initial Version
 *
 */

#include <EventSystem.h>
#include <EventElement.h>

#ifndef EVENTBUTTON_H
#define EVENTBUTTON_H

#define HOLD_TIME   1000  ///< Time a button needs to be pressed before going into repeat mode.
#define REPEAT_TIME 400   ///< Time between repeat.

/**
 * Generates press/release events.
 */
class EventButton : public EventElement {
	public:
		/**
		 * Create an EventButton object.
		 *
		 * @param buttonPin        The pin number of the digital pin the button is connected to.
		 * @param buttonHoldTime   The time to wait until the button is considered in the hold state.
		 * @param buttonRepeatTime The time between repeats.
		 * @param pressEvent       Event to generate when the button is pressed default is Events::EV_BUTTON_PRESS.
		 * @param releaseEvent     Event to generate when the button is released default is Events::EV_BUTTON_RELEASE.
		 */
		EventButton(
			byte buttonPin, 
			unsigned int buttonHoldTime = 0, 
			unsigned int buttonRepeatTime = 0,
			byte pressEvent = Events::EV_BUTTON_PRESS,
			byte releaseEvent = Events::EV_BUTTON_RELEASE
		);
		
		/**
		 * Check the button and generate events when the button state changes.
		 */
		virtual void Check();

	private:
		byte pin;                   ///< Pin number of the arduino board.
		unsigned millisecs : 1;     ///< Toggle every ms.
		unsigned debounce : 4;      ///< debounce shift register.
		unsigned statePrevious : 1; ///< Previous state of the button.
		unsigned stateCurrent : 1;  ///< Current state of the button.
		unsigned stateRepeat : 1;   ///< Is the button repeating.
		unsigned int holdTime;      ///< Time to wait before going into repeat mode.
		unsigned int repeatTime;    ///< Time to wait between repeats.
		unsigned long changeTime;   ///< Last time the button changed state.
		byte press;                 ///< Event to generate when the button is pressed.
		byte release;               ///< Event to generate when the button is released.
};

#endif
