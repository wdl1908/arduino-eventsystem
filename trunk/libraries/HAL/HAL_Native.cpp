/**
 * @file HAL_Native.cpp
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

#include <HAL_Native.h>

HAL_Native::HAL_Native() {
}

void HAL_Native::HAL_pinMode(byte pin, byte mode) {
	pinMode(pin, mode);
}

int  HAL_Native::HAL_digitalRead(byte pin) {
	return digitalRead(pin);
}

void HAL_Native::HAL_digitalWrite(byte pin, byte val) {
	digitalWrite(pin, val);
}

void HAL_Native::HAL_pullUp(byte pin, byte val) {
	digitalWrite(pin, val);
}

int  HAL_Native::HAL_analogRead(byte pin) {
	return analogRead(pin);
}

void HAL_Native::HAL_analogWrite(byte pin, byte val) {
	return analogWrite(pin, val);
}

HAL_Native nativePinHAL = HAL_Native();
