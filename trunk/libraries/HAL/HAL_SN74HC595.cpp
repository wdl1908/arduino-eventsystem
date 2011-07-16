/**
 * @file HAL_SN74HC595.cpp
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
 *    - 1.0 2011-07-13 - Willy De la Court : Initial Version
 *
 */

#include <HAL_SN74HC595.h>

HAL_SN74HC595::HAL_SN74HC595(byte data, byte clock, byte latch) {
	dataPin = data;
	clockPin = clock;
	latchPin = latch;
	pinMode(dataPin, OUTPUT);
	pinMode(clockPin, OUTPUT);
	pinMode(latchPin, OUTPUT);
}

void HAL_SN74HC595::HAL_pinMode(byte pin, byte mode) {
	// Nothing todo only digital outputs with SN74HC595
}

int  HAL_SN74HC595::HAL_digitalRead(byte pin) {
	return 0; // Nothing todo only digital outputs with SN74HC595
}

void HAL_SN74HC595::HAL_digitalWrite(byte pin, byte val) {
	outputVal &= ~(0x01 << (pin - 1));
	outputVal |= ((val != 0) << (pin - 1));
	digitalWrite(latchPin, LOW);
	shiftOut(dataPin, clockPin, MSBFIRST, outputVal);
	digitalWrite(latchPin, HIGH);
}

void HAL_SN74HC595::HAL_pullUp(byte pin, byte val) {
	// Nothing todo only digital outputs with SN74HC595
}

int  HAL_SN74HC595::HAL_analogRead(byte pin) {
	return 0; // Nothing todo only digital outputs with SN74HC595
}

void HAL_SN74HC595::HAL_analogWrite(byte pin, byte val) {
	// Nothing todo only digital outputs with SN74HC595
}
