/**
 * @file EventPWMLed.cpp
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
#include <EventPWMLed.h>

EventPWMLed::EventPWMLed(
		byte ledPin,
		int ledFadeTime,
		int ledBlinkOnTime,
		int ledBlinkOffTime
	):EventLed(ledPin, ledBlinkOnTime, ledBlinkOffTime) {

	fadeTime = ledFadeTime;
}

void EventPWMLed::Check() {
	int timeElapsed;
	byte newState;
	unsigned long temp;

	EventLed::Check();
	if (lastEvent == Events::EV_LED_FADEIN || lastEvent == Events::EV_LED_FADEOUT) {
		timeElapsed = millis() - startTime;
		temp = (uint32_t) timeElapsed * 256L / (uint32_t) fadeTime;
		switch (lastEvent) {
			case Events::EV_LED_FADEIN:
				newState = LED_ON * temp * temp / 65536L;
				state = newState;
				if (state == LED_ON || timeElapsed > fadeTime) {
					On();
				}
				break;
			case Events::EV_LED_FADEOUT:
				newState = -LED_ON * temp * (temp - 512L) / 65536L;
				state = LED_ON - newState;
				if (state == LED_OFF || timeElapsed > fadeTime) {
					Off();
				}
				break;
		}
		analogWrite(pin, state);
	}
}

void EventPWMLed::HandleEvent(byte event, int param) {
	EventLed::HandleEvent(event, param);

	if (event >= Events::EV_LED_FADEIN ||
		event <= Events::EV_LED_FADEOUT) {
		
		if (param == pin) {
			switch (event) {
				case Events::EV_LED_FADEIN:
					FadeIn();
					break;

				case Events::EV_LED_FADEOUT:
					FadeOut();
					break;
			}
		}
	}
}

void EventPWMLed::FadeIn() {
	if (lastEvent == Events::EV_LED_OFF) {
		startTime = millis();
		lastEvent = Events::EV_LED_FADEIN;
	}
}

void EventPWMLed::FadeOut() {
	if (lastEvent == Events::EV_LED_ON) {
		startTime = millis();
		lastEvent = Events::EV_LED_FADEOUT;
	}
}
