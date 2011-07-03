/**
 * @file EventLed.h
 *
 * @about Part of Arduino Event System.
 *
 * @author Willy De la Court
 *
 * @version 1.0
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
 *    - 1.0 2011-07-02 - Willy De la Court : Initial Version
 *
 */

#include <EventSystem.h>
#include <EventElement.h>

#ifndef EVENTLED_H
#define EVENTLED_H

/**
 * Generates analog Events.
 */
class EventLed : public EventElement {
	public:
		/**
		 * Create an EventLed object.
		 *
		 * @param ledPin       The pin number where the led is connected to.
		 */
		EventLed(
			byte ledPin,
			int ledFadeTime = 2000,
			int ledBlinkOnTime = 1000,
			int ledBlinkOffTime = 2000
		);
		
		/**
		 * Check the state of the led and process FadeIn / FadeOut actions.
		 */
		virtual void Check();

		virtual void HandleEvent(byte event, int param);

		void On();
		void Off();
		void Toggle();
		void FadeIn();
		void FadeOut();
		void Blink();
		boolean isOn()  { return state == 255; };
		boolean isOff() { return state == 0; };
	private:
		byte pin;       ///< Pin number of the arduino board.
		byte state;     ///< state of the led 255 is on 0 is off.
		byte lastEvent; ///< Last event that was requested for this led.
		unsigned long fadeStartTime; ///< Time the FadeIn / FadeOut started.
		unsigned int fadeTime;       ///< Time the FadeIn / FadeOut should take.
		unsigned int blinkOnTime;    ///< Time a blinking led stays on.
		unsigned int blinkOffTime;   ///< Time a blinking led stays on.
};

void ledHandler(byte event, int param);

#endif
