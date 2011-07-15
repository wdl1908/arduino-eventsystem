/**
 * @file HAL_DigitalMuxOnAnalogPin.cpp
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

#include <HAL_DigitalMuxOnAnalogPin.h>

HAL_DigitalMuxOnAnalogPin::HAL_DigitalMuxOnAnalogPin(byte pin, byte nrPins) {
	analogPin = pin;
	nrDigitalPins = nrPins;
	analogValue = 0;
	pinMode(analogPin, INPUT);
}

void HAL_DigitalMuxOnAnalogPin::HAL_pinMode(byte pin, byte mode) {
	// pinMode has no effect as this are only inputs
}

int  HAL_DigitalMuxOnAnalogPin::HAL_digitalRead(byte pin) {
	int value;
	byte cnt;
	int step;
	int hysteresis;
	
	value = analogRead(analogPin);
	// Calculate 10% of the distributionn / pin
	step = 1023 / nrDigitalPins;
	hysteresis = step / 10;
	if (value < analogValue - hysteresis || analogValue + hysteresis < value) {
		analogValue = value;
		digitalValue = 0;
		for (cnt = 1; cnt <= nrDigitalPins; cnt++) {
			value = step * cnt;
			if (value - hysteresis <= analogValue && analogValue <= value + hysteresis) {
				digitalValue = cnt;
				break;
			}
		}
	}
	return (digitalValue != pin);
}

void HAL_DigitalMuxOnAnalogPin::HAL_digitalWrite(byte pin, byte val) {
	// digitalWrite has no effect as this are only inputs
}

void HAL_DigitalMuxOnAnalogPin::HAL_pullUp(byte pin, byte val) {
	// pullUp has no effect as this are only inputs
}

int  HAL_DigitalMuxOnAnalogPin::HAL_analogRead(byte pin) {
	return analogRead(analogPin);
}

void HAL_DigitalMuxOnAnalogPin::HAL_analogWrite(byte pin, byte val) {
	// analogWrite has no effect as this are only inputs
}
