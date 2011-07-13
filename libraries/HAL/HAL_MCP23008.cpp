/**
 * @file HAL_MCP23008.cpp
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

#include <HAL_MCP23008.h>

HAL_MCP23008::HAL_MCP23008(byte addr) {
	i2cAddr = MCP23008_BASE_ADDRESS | (addr & 0x07);
	i2cPinMode = 0xFF;
	i2cData = 0x00;
	i2cPullUp = 0x00;
	
	Wire.begin();

	Wire.beginTransmission(i2cAddr);
	Wire.send(MCP23008_IODIR);
	Wire.send(0xFF); // set all pins to input.
	Wire.send(0x00); // reset all other registers
	Wire.send(0x00);
	Wire.send(0x00);
	Wire.send(0x00);
	Wire.send(0x00);
	Wire.send(0x00);
	Wire.send(0x00);
	Wire.send(0x00);
	Wire.send(0x00);
	Wire.endTransmission();
}

void HAL_MCP23008::HAL_pinMode(byte pin, byte mode) {
	if (mode == INPUT) {
		i2cPinMode |= 1 << pin;
	} else {
		i2cPinMode &= ~(1 << pin);
	}

	Wire.beginTransmission(i2cAddr);
	Wire.send(MCP23008_IODIR);
	Wire.send(i2cPinMode);
	Wire.endTransmission();
}

int  HAL_MCP23008::HAL_digitalRead(byte pin) {
	return digitalRead(pin);
}

void HAL_MCP23008::HAL_digitalWrite(byte pin, byte val) {
	if (val) {
		i2cData |= 1 << pin;
	} else {
		i2cData &= ~(1 << pin);
	}

	Wire.beginTransmission(i2cAddr);
	Wire.send(MCP23008_GPIO);
	Wire.send(i2cData);
	Wire.endTransmission();
}

void HAL_MCP23008::HAL_pullUp(byte pin, byte val) {
	if (val) {
		i2cPullUp |= 1 << pin;
	} else {
		i2cPullUp &= ~(1 << pin);
	}

	Wire.beginTransmission(i2cAddr);
	Wire.send(MCP23008_GPPU);
	Wire.send(i2cPullUp);
	Wire.endTransmission();
}

int  HAL_MCP23008::HAL_analogRead(byte pin) {
	return 0;
}

void HAL_MCP23008::HAL_analogWrite(byte pin, byte val) {
	HAL_digitalWrite(pin, val != 0);
}
