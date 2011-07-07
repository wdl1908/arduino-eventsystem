/**
 * @file: EventMenu.h
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

#include <EventSystem.h>
#include <EventElement.h>
#include <LiquidCrystal.h>

#ifndef  EVENTMENU_H
#define  EVENTMENU_H

#define ARROW_UP         0
#define ARROW_DOWN       1
#define ARROW_UP_BLOCK   2
#define ARROW_DOWN_BLOCK 3

class EventMenuRoot;
class EventMenuItem {
	friend class EventMenuRoot;
	public:
		EventMenuItem(char *menuName, byte eventCode = Events::EV_NONE);
		virtual void addChild(EventMenuItem *child);
		EventMenuItem *HandleEvent(byte event, byte rows, byte cols);
		void Display(LiquidCrystal *lcd, byte line, boolean active = false);

	protected:
		EventMenuItem *parent;
		EventMenuItem *firstChild;
		EventMenuItem *lastChild;
		EventMenuItem *prevSibling;
		EventMenuItem *nextSibling;
		byte currentLine;
		byte event;

	private:
		char *name;
};

class EventMenuRoot : public EventMenuItem, EventElement {
	public:
		EventMenuRoot(LiquidCrystal *lcdDisplay, byte maxCols, byte maxRows);
		virtual void HandleEvent(byte event, int param);
		void Display();
	private:
		LiquidCrystal *lcd;
		byte rows;
		byte cols;
		EventMenuItem *current;
};

#endif
