/**
 * @file EventLed.cpp
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
#include <EventLed.h>

EventLed::EventLed(
		byte ledPin,
		int ledFadeTime,
		int ledBlinkOnTime,
		int ledBlinkOffTime
	):EventElement() {

	// Set the pin to output
	pin = ledPin;
	pinMode(pin, OUTPUT);
	
	// Turn the led off
	Off();
	fadeTime = ledFadeTime;
	blinkOnTime = ledBlinkOnTime;
	blinkOffTime = ledBlinkOffTime;
	systemEventDispatcher.addEventListener(Events::EV_LED_ON,      ledHandler, EventDispatcher::OVERWRITE_EVENT);
	systemEventDispatcher.addEventListener(Events::EV_LED_OFF,     ledHandler, EventDispatcher::OVERWRITE_EVENT);
	systemEventDispatcher.addEventListener(Events::EV_LED_TOGGLE,  ledHandler, EventDispatcher::OVERWRITE_EVENT);
	systemEventDispatcher.addEventListener(Events::EV_LED_FADEIN,  ledHandler, EventDispatcher::OVERWRITE_EVENT);
	systemEventDispatcher.addEventListener(Events::EV_LED_FADEOUT, ledHandler, EventDispatcher::OVERWRITE_EVENT);
	systemEventDispatcher.addEventListener(Events::EV_LED_BLINK,   ledHandler, EventDispatcher::OVERWRITE_EVENT);
}

void EventLed::Check() {
	int timeElapsed;
	byte newState;
	unsigned long temp;

	if (lastEvent == Events::EV_LED_FADEIN || lastEvent == Events::EV_LED_FADEOUT) {
		timeElapsed = millis() - fadeStartTime;
		temp = (uint32_t) timeElapsed * 256L / (uint32_t) fadeTime;
		switch (lastEvent) {
			case Events::EV_LED_FADEIN:
				newState = 255 * temp * temp / 65536L;
				state = newState;
				if (state == 255 || timeElapsed > fadeTime) {
					On();
				}
				break;
			case Events::EV_LED_FADEOUT:
				newState = -255 * temp * (temp - 512L) / 65536L;
				state = 255 - newState;
				if (state == 0 || timeElapsed > fadeTime) {
					Off();
				}
				break;
		}
		analogWrite(pin, state);
	} else if (lastEvent == Events::EV_LED_BLINK) {
		temp = millis();
		if (isOn() && fadeStartTime + blinkOnTime < temp) {
			state = 0;
			analogWrite(pin, state);
			fadeStartTime = temp;
		} else if (isOff() && fadeStartTime + blinkOffTime < temp) {
			state = 255;
			analogWrite(pin, state);
			fadeStartTime = temp;
		}
	}
}

void EventLed::HandleEvent(byte event, int param) {
	if (	event == Events::EV_LED_ON ||
			event == Events::EV_LED_OFF ||
			event == Events::EV_LED_TOGGLE ||
			event == Events::EV_LED_FADEIN ||
			event == Events::EV_LED_FADEOUT ||
			event == Events::EV_LED_BLINK) {
		
		if (param == pin) {
			switch (event) {
				case Events::EV_LED_ON:
					On();
					break;

				case Events::EV_LED_OFF:
					Off();
					break;

				case Events::EV_LED_TOGGLE:
					Toggle();
					break;

				case Events::EV_LED_FADEIN:
					FadeIn();
					break;

				case Events::EV_LED_FADEOUT:
					FadeOut();
					break;

				case Events::EV_LED_BLINK:
					Blink();
					break;
			}
		}
	}
}

void EventLed::On() {
	state = 255;
	analogWrite(pin, state);
	lastEvent = Events::EV_LED_ON;
}

void EventLed::Off() {
	state = 0;
	analogWrite(pin, state);
	lastEvent = Events::EV_LED_OFF;
}

void EventLed::Toggle() {
	if (isOn()) {
		Off();
	} else {
		On();
	}
}

void EventLed::Blink() {
	state = 255;
	analogWrite(pin, state);
	fadeStartTime = millis();
	lastEvent = Events::EV_LED_BLINK;
}

void EventLed::FadeIn() {
	if (lastEvent == Events::EV_LED_OFF) {
		fadeStartTime = millis();
		lastEvent = Events::EV_LED_FADEIN;
	}
}

void EventLed::FadeOut() {
	if (lastEvent == Events::EV_LED_ON) {
		fadeStartTime = millis();
		lastEvent = Events::EV_LED_FADEOUT;
	}
}

void ledHandler(byte event, int param) {
	EventElement *element;

	element = systemEventDispatcher.getEventElementHead();
	while (element) {
		element->HandleEvent(event, param);
		element = element->getNext();
	}
}