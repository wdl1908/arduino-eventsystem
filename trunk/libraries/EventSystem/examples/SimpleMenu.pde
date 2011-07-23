/**
 * @file: SimpleMenu.pde
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
 *    - 1.0 2011-07-07 - Willy De la Court : Initial Version
 *
 */

#include "WProgram.h"
#include <EventSystem.h>
#include <EventMenu.h>
#include <EventButton.h>

// Buttons need to be connected to GND
#define BUTTON_UP    6
#define BUTTON_DOWN  7
#define BUTTON_RESET 8
#define BUTTON_BACK  9

EventButton btnUp    = EventButton(BUTTON_UP,    HOLD_TIME, REPEAT_TIME, Events::EV_MENU_UP);
EventButton btnDown  = EventButton(BUTTON_DOWN,  HOLD_TIME, REPEAT_TIME, Events::EV_MENU_DOWN);
EventButton btnEnter = EventButton(BUTTON_RESET, 0,         0,           Events::EV_MENU_ENTER);
EventButton btnBack  = EventButton(BUTTON_BACK,  0,         0,           Events::EV_MENU_BACK);

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

EventMenuRoot Root = EventMenuRoot(&lcd, 16, 2);

EventMenuItem Menu1 = EventMenuItem("Menu1");
EventMenuItem Menu2 = EventMenuItem("Menu2");
EventMenuItem Menu3 = EventMenuItem("Menu3");
EventMenuItem Menu4 = EventMenuItem("Menu4");
EventMenuItem Menu11 = EventMenuItem("Menu11");
EventMenuItem Menu12 = EventMenuItem("Menu12");
EventMenuItem Menu13 = EventMenuItem("Menu13");
EventMenuItem Menu21 = EventMenuItem("Menu21");
EventMenuItem Menu31 = EventMenuItem("Menu31");

void setup() {
	Root.addChild(&Menu1);
	Root.addChild(&Menu2);
	Root.addChild(&Menu3);
	Root.addChild(&Menu4);
	Menu1.addChild(&Menu11);
	Menu1.addChild(&Menu12);
	Menu1.addChild(&Menu13);
	Menu2.addChild(&Menu21);
	Menu3.addChild(&Menu31);
	Root.begin();

	systemEventQueue.enqueueEvent(Events::EV_PAINT, 0);
}

void loop() {
	systemEventDispatcher.run();
}
