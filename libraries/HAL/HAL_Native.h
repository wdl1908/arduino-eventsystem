/**
 * @file HAL_Native.h
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

#include <WProgram.h>
#include <HAL.h>

#ifndef HAL_NATIVE_H
#define HAL_NATIVE_H

class HAL_Native : public HAL {
	public:
		HAL_Native();
		void HAL_pinMode(byte pin, byte mode);
		int  HAL_digitalRead(byte pin);
		void HAL_digitalWrite(byte pin, byte val);
		void HAL_pullUp(byte pin, byte val);
		int  HAL_analogRead(byte pin);
		void HAL_analogWrite(byte pin, byte val);
};

extern HAL_Native nativePinHAL;

#endif
