//  $Id: Dog.cxx,v 1.1 2002/03/19 17:56:53 grumbel Exp $
//
//  Pingus - A free Lemmings clone
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

#include "GameWorld.hxx"
#include "Dog.hxx"

Dog::Dog (const CL_Vector& arg_pos, Direction arg_dir) 
  : sprite (sprite_storage->create ("dog")),
pos (arg_pos),
 direction (arg_dir)
{
}

void 
Dog::draw ()
{
  if (direction == WEST)
    sprite->setScale (-1.0, 1.0);
  else
    sprite->setScale (1.0, 1.0);

  sprite->setHotSpot(24, 36);
	
  sprite->draw (int (pos.x), int (pos.y));
}

void
Dog::update (float delta)
{
  sprite->update (delta);

  CL_Vector tmp_pos (pos);

  if (direction == WEST)
    pos.x -= 200 * delta;
  else
    pos.x += 200 * delta;

  if (pos.x < 0)
    direction = EAST;
  else if (pos.x > 800)
    direction = WEST;

  if (!on_ground ())
    {
      float movement = 300 * delta;
      for (float i = 0; i < movement * 10 && !on_ground (); ++i)
	pos.y += 0.1;
    }

  if (stuck ())
    {
      pos = tmp_pos;
      if (direction == EAST) direction = WEST;
      else direction = EAST;
    }
}

bool
Dog::on_ground () 
{
  return get_world ()->get_tilemap()->is_ground (pos.x, pos.y+2);
}

bool
Dog::stuck () 
{
  return get_world ()->get_tilemap()->is_ground (pos.x, pos.y);
}

/* EOF */