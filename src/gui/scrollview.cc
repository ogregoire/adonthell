/*
 Copyright (C) 2010 Kai Sterker <kai.sterker@gmail.com>
 Part of the Adonthell Project http://adonthell.linuxgames.com

 Adonthell is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 Adonthell is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with Adonthell; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

/**
 * @file   gui/scrollview.cc
 * @author Kai Sterker <kai.sterker@gmail.com>
 * @brief  Implements the scrollview class.
 */

#include "gui/scrollview.h"

using gui::scrollview;

// render scrollview
void scrollview::draw(const s_int16 & x, const s_int16 & y, const gfx::drawing_area * da, gfx::surface * target) const
{
    if (!Visible) return;

    // draw ourself
    widget::draw (x, y, da, target);

    // draw scrolled widget
	if (!Children.empty())
	{
	    gfx::drawing_area client_area (x, y, length(), height());
	    client_area.shrink (Look->border ());
	    client_area.assign_drawing_area (da);
	    Children[0].Child->draw (x - Ox, y - Oy, &client_area, target);
	}

    // Todo: draw the scrollbars
}

// set the container that should be scrolled
void scrollview::set_child (layout & c)
{
	bool refocus = focused;
	if (!Children.empty())
	{
		remove_child (*Children[0].Child);
	}

	add_child (c, 0, 0);
	if (refocus) focus();
}

// set the scroll mode
void scrollview::set_scroll_mode (const scroll_mode & m)
{
	ScrollMode = m;
	if (!Children.empty())
	{
		gui::layout *container = (gui::layout*) Children[0].Child;
		container->set_auto_grow ((resize_mode) m);
	}
}

// make sure the given widget is visible in the view
void scrollview::show (const gui::widget & c)
{
	gui::layout *container = (gui::layout*) Children[0].Child;
	gfx::drawing_area pos = container->get_location (c);
	pos.grow (Look->border ());

	if ((ScrollMode & SCROLL_X) == SCROLL_X)
	{
		if (pos.x() < Ox)
		{
			Ox = pos.x();
		}
		else if (pos.x() + pos.length() > Ox + length())
		{
			Ox = pos.x() + pos.length() - length();
		}
	}

	if ((ScrollMode & SCROLL_Y) == SCROLL_Y)
	{
		if (pos.y() < Oy)
		{
			Oy = pos.y();
		}
		else if (pos.y() + pos.height() > Oy + height())
		{
			Oy = pos.y() + pos.height() - height();
		}
	}
}

// center the given widget in the view
void scrollview::center (const gui::widget & c)
{
	gui::layout *container = (gui::layout*) Children[0].Child;
	gfx::drawing_area pos = container->get_location (c);
	pos.grow (Look->border ());

	if ((ScrollMode & SCROLL_X) == SCROLL_X)
	{
		Ox = pos.x() + (pos.length() - length()) / 2;
	}

	if ((ScrollMode & SCROLL_Y) == SCROLL_Y)
	{
		Oy = pos.y() + (pos.height() - height()) / 2;
	}
}

// update scroll offset
bool scrollview::keydown(input::keyboard_event & k)
{
	bool consumed = layout::keydown (k);
	if (consumed)
	{
		if (k.key() == input::keyboard_event::LEFT_KEY ||
			k.key() == input::keyboard_event::RIGHT_KEY ||
			k.key() == input::keyboard_event::TAB_KEY ||
			k.key() == input::keyboard_event::DOWN_KEY ||
			k.key() == input::keyboard_event::UP_KEY)
		{
			gui::layout *container = (gui::layout*) Children[0].Child;
			show (container->get_child (container->current()));
		}
	}

	return consumed;
}
