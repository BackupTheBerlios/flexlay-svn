//  $Id: dog.hxx,v 1.3 2003/09/12 16:31:21 grumbel Exp $
// 
//  Windstille - A Jump'n Shoot Game
//  Copyright (C) 2000 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software; you can redistribute it and/or
//  modify it under the terms of the GNU General Public License
//  as published by the Free Software Foundation; either version 2
//  of the License, or (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
// 
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

#ifndef DOG_HXX
#define DOG_HXX

#include <ClanLib/Core/Math/cl_vector.h>
#include <ClanLib/Display/sprite.h>
#include "gameobj.hxx"
#include "globals.hxx"

class Dog : public GameObj
{
private:
  CL_Sprite sprite;
  CL_Vector pos;
  Direction direction;
public:
  Dog (const CL_Vector& arg_pos, Direction);
  virtual ~Dog () {}
  
  void draw ();
  void update (float);

  bool on_ground ();
  bool stuck ();
};

#endif

/* EOF */