/*
 $Id: square_walkable_info.h,v 1.1 2007/06/10 03:58:22 ksterker Exp $
 
 Copyright (C) 2002 Alexandre Courbot <alexandrecourbot@linuxgames.com>
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
 * @file   world/square_walkable_info.h
 * @author Alexandre Courbot <alexandrecourbot@linuxgames.com>
 * 
 * @brief  Declares the square_walkable_info class.
 * 
 * 
 */

#ifndef WORLD_WALKABLE_INFO_H
#define WORLD_WALKABLE_INFO_H

#include "base/flat.h"

namespace world
{
/**
 * Walkability info class.
 */
class square_walkable_info
{
public:
    square_walkable_info () 
    {
        Walkable = true;  
    }

    bool is_walkable () const
    {
        return Walkable; 
    }

    void set_walkable (bool b) 
    {
        Walkable = b; 
    }

    void put_state (base::flat & file) const;

    bool get_state (base::flat & file);

    bool does_intersect(const square_walkable_info & mwi, const u_int16 ox, const u_int16 oy) const
    {
        return (is_walkable() && mwi.is_walkable());
    }
    
private:
    bool Walkable;
};

}

#endif // WORLD_WALKABLE_INFO_H
