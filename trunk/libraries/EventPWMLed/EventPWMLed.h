/**
 * @file EventPWMLed.h
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
#include <EventLed.h>

#ifndef EVENTLED_H
#define EVENTLED_H

#define LED_FADETIME  2000

/**
 * Led Control. The led must be connected to GND on a PWM pin with a serie resistor.
 */
class EventPWMLed : public EventLed {
	public:
		/**
		 * Create an EventPWMLed object.
		 *
		 * @param ledPin          The pin number where the led is connected to.
		 * @param ledFadeTime     The time neede to fade a led in or out. Default is 2000ms.
		 * @param ledBlinkOnTime  Time the led is on when blinking. Default is 250ms.
		 * @param ledBlinkOffTime Time the led is off when blinking. Default is 250ms.
		 */
		EventPWMLed(
			byte ledPin,
			int ledFadeTime = LED_FADETIME,
			int ledBlinkOnTime = LED_BLINKTIME,
			int ledBlinkOffTime = LED_BLINKTIME
		);
		
		/**
		 * Check the state of the led and process Blink / FadeIn / FadeOut actions.
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
		 * Turn the led on with a fading effect.
		 */
		void FadeIn();

		/**
		 * Turn the led off with a fading effect.
		 */
		void FadeOut();

	private:
		unsigned int fadeTime;       ///< Time the FadeIn / FadeOut should take.
};

#endif
