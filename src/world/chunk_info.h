/*
 $Id: chunk_info.h,v 1.2 2009/01/09 22:39:41 ksterker Exp $
 
 Copyright (C) 2008/2009 Kai Sterker <kaisterker@linuxgames.com>
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
 * @file   world/chunk_info.h
 * @author Kai Sterker <kaisterker@linuxgames.com>
 * 
 * @brief  Declares the chunk_info class.
 * 
 * 
 */


#ifndef WORLD_CHUNK_INFO_H
#define WORLD_CHUNK_INFO_H

#include "world/placeable.h"

namespace world
{
    /**
     * Container to store an object with its world-space coordinates.
     * Coordinates are expressed by an axis aligned bounding box (AABB).
     */
    class chunk_info
    {
    public:
        chunk_info (placeable *o, const vector3<s_int32> & min, const vector3<s_int32> & max) 
        : Object (o), Min (min), Max (max)
        {
        }

        chunk_info (const chunk_info & ci) 
        : Object (ci.Object), Min (ci.Min), Max (ci.Max)
        {
        }

        bool operator == (const chunk_info & ci) const;

        vector3<s_int32> real_min () const
        {
            return Min + vector3<s_int32>(Object->min_x(), Object->min_y(), Object->min_z());
        }

        vector3<s_int32> real_max () const
        {
            return Max + vector3<s_int32>(Object->min_x(), Object->min_y(), Object->min_z());
        }
        
        /// pointer to map object
        placeable * Object;
        /// position of the object
        vector3<s_int32> Min;
        /// extend of the object
        vector3<s_int32> Max;
    };
}

#endif