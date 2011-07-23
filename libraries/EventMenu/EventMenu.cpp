/**
 * @file: EventMenu.cpp
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

#include <HALLiquidCrystal.h>
#include <EventMenu.h>

// FIXME should be in PROGMEM
/**
 * Character bit matrix for up arrow
 */
byte arrow_up[8]             = {0x04,  // --X--
								0x0A,  // -X-X-
								0x11,  // X---X
								0x00,  // -----
								0x00,  // -----
								0x00,  // -----
								0x00}; // -----

/**
 * Character bit matrix for down arrow
 */
byte arrow_down[8]           = {0x00,  // -----
								0x00,  // -----
								0x00,  // -----
								0x00,  // -----
								0x11,  // X---X
								0x0A,  // -X-X-
								0x04}; // --X--

/**
 * Character bit matrix for up arrow with block
 */
byte arrow_up_block[8]       = {0x04,  // --X--
								0x0A,  // -X-X-
								0x11,  // X---X
								0x00,  // -----
								0x1F,  // XXXXX
								0x1F,  // XXXXX
								0x1F}; // XXXXX

/**
 * Character bit matrix for down arrow with block
 */
byte arrow_down_block[8]     = {0x1F,  // XXXXX
								0x1F,  // XXXXX
								0x1F,  // XXXXX
								0x00,  // -----
								0x11,  // X---X
								0x0A,  // -X-X-
								0x04}; // --X--

EventMenuItem::EventMenuItem(char *menuName, byte eventCode, int param) {
	parent = 0;
	firstChild = 0;
	lastChild = 0;
	prevSibling = 0;
	nextSibling = 0;
	currentLine = 0;
	name = menuName;
	enterEvent = eventCode;
	enterParam = param;
}

void EventMenuItem::addChild(EventMenuItem *child) {
	if (child) {
		child->parent = this;
		if (lastChild) {
			child->prevSibling = lastChild;
			lastChild->nextSibling = child;
			lastChild = child;
		} else {
			firstChild = child;
			lastChild = child;
		}
	}
}

void EventMenuItem::Display(HALLiquidCrystal *lcd, byte line, boolean active) {
	currentLine = line;
	lcd->setCursor(0, line);
	if (active) {
		lcd->print((char)0x7E); // right arrow
	} else {
		lcd->print((char)' ');
	}
	lcd->print(name);
}

EventMenuItem *EventMenuItem::HandleEvent(byte event, byte rows, byte cols) {
	switch (event) {
		case Events::EV_MENU_UP:
			// Is there a previous menu item?
			if (prevSibling) {
				if (currentLine == 0) {
					// Need to scroll up if a menu item exists before this one.
					prevSibling->currentLine = 0;
				} else {
					// No scolling needed just activate the previous menu item.
					prevSibling->currentLine = currentLine - 1;
				}
				return prevSibling;
			} else {
				// No previous menu item exists so nothing to do.
				return this;
			}
			break;
		case Events::EV_MENU_DOWN:
			// Is there a next menu item?
			if (nextSibling) {
				if (currentLine == rows - 1) {
					// Need to scroll down if a menu item exists after this one.
					nextSibling->currentLine = rows - 1;
				} else {
					// No scolling needed just activate the next menu item.
					nextSibling->currentLine = currentLine + 1;
				}
				return nextSibling;
			} else {
				// No next menu item exists so nothing to do.
				return this;
			}
			break;
		case Events::EV_MENU_ENTER:
			systemEventQueue.enqueueEvent(enterEvent, enterParam);
			if (firstChild) {
				firstChild->currentLine = 0;
				return firstChild;
			} else {
				return this;
			}
			break;
		case Events::EV_MENU_BACK:
			return parent;
			break;
	}
}

EventMenuRoot::EventMenuRoot(HALLiquidCrystal *lcdDisplay, byte maxCols, byte maxRows) : EventMenuItem("Root"), EventElement() {
	rows = maxRows;
	cols = maxCols;
	lcd = lcdDisplay;
	current = 0;
}

void EventMenuRoot::begin() {
	lcd->begin(cols, rows);
	lcd->createChar(ARROW_UP,         arrow_up);
	lcd->createChar(ARROW_DOWN,       arrow_down);
	lcd->createChar(ARROW_UP_BLOCK,   arrow_up_block);
	lcd->createChar(ARROW_DOWN_BLOCK, arrow_down_block);
}

// FIXME this is ugly. Need to revise the object inheritance.
void EventMenuRoot::addChild(EventMenuItem *child) {
	EventMenuItem::addChild(child);
	child->parent = 0;
}

void EventMenuRoot::HandleEvent(byte event, int param) {
	if (event == Events::EV_PAINT) {
		Display();
	}
	if (!current)
		current = firstChild;
	if (current)  {
		if (event == Events::EV_MENU_UP    || event == Events::EV_MENU_DOWN ||
			event == Events::EV_MENU_ENTER || event == Events::EV_MENU_BACK) {
			// Pass the number of rows and cols as the event parameter.
			current = current->HandleEvent(event, rows, cols);
			systemEventQueue.enqueueEvent(Events::EV_PAINT);
		}
	}
}

void EventMenuRoot::Display() {
	byte line;
	EventMenuItem *item;
	boolean needTopArrow;
	boolean needBottomArrow;

	if (!current)
		current = firstChild;
	if (current)  {
		lcd->clear();
		needTopArrow = false;
		needBottomArrow = false;
		// Display the current line
		current->Display(lcd, current->currentLine, true);
		// Display all lines above the current line if any.
		line = current->currentLine;
		item = current;
		if (line == 0 && item->prevSibling) {
			needTopArrow = true;
		}
		if (line == rows - 1 && item->nextSibling) {
			needBottomArrow = true;
		}
		while (line > 0) {
			line--;
			item = item->prevSibling;
			if (item) {
				item->Display(lcd, line, false);
				if (line == 0 && item->prevSibling) {
					needTopArrow = true;
				}
			} else {
				line = 0;
			}
		}
		// Display all lines below the current line if any.
		line = current->currentLine;
		item = current;
		while (line < rows - 1) {
			line++;
			item = item->nextSibling;
			if (item) {
				item->Display(lcd, line, false);
				if (line == rows - 1 && item->nextSibling) {
					needBottomArrow = true;
				}
			} else {
				line = rows;
			}
		}
		// All menu items are displayed now calculate the scoll bar
		if (needTopArrow || needBottomArrow) {
			lcd->setCursor(cols - 1, 0);
			if (needTopArrow) {
				lcd->print((char)ARROW_UP_BLOCK);
			} else {
				lcd->print((char)ARROW_UP);
			}
			lcd->setCursor(cols - 1, rows - 1);
			if (needBottomArrow) {
				lcd->print((char)ARROW_DOWN_BLOCK);
			} else {
				lcd->print((char)ARROW_DOWN);
			}
		}
	}
}
