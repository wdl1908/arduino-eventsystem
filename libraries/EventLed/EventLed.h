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
		 * @param ledPin          The pin number where the led is connected to.
		 * @param ledFadeTime     The time neede to fade a led in or out.
		 * @param ledBlinkOnTime  Time the led is on when blinking.
		 * @param ledBlinkOffTime Time the led is off when blinking.
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

		/**
		 * Handle events destined for this element.
		 *
		 * @param event Events code
		 * @param param Value associated with the Event
		 */
		virtual void HandleEvent(byte event, int param);

		/**
		 * Turn the led on.
		 */
		void On();

		/**
		 * Turn the led off.
		 */
		void Off();

		/**
		 * Turn the led off when on and on when off.
		 */
		void Toggle();

		/**
		 * Turn the led on with a fading effect.
		 */
		void FadeIn();

		/**
		 * Turn the led off with a fading effect.
		 */
		void FadeOut();

		/**
		 * Turn the led on and off continuously.
		 */
		void Blink();

		/**
		 * @return @b true if the led is on.
		 */
		boolean isOn()  { return state == 255; };

		/**
		 * @return @b true if the led is off.
		 */
		boolean isOff() { return state == 0; };
	private:
		byte pin;       ///< Pin number of the arduino board.
		byte state;     ///< state of the led 255 is on 0 is off.
		byte lastEvent; ///< Last event that was requested for this led.
		unsigned long fadeStartTime; ///< Time the FadeIn / FadeOut started.
		unsigned int fadeTime;       ///< Time the FadeIn / FadeOut should take.
		unsigned int blinkOnTime;    ///< Time a blinking led stays on.
		unsigned int blinkOffTime;   ///< Time a blinking led stays off.
};

#endif
