//  $Id: LaserShoot.cxx,v 1.1 2002/03/19 17:56:57 grumbel Exp $
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

#include "StringConverter.hxx"
#include "GameWorld.hxx"
#include "AnimationObj.hxx"
#include "LaserShoot.hxx"

LaserShoot::LaserShoot (const CL_Vector& arg_pos, Direction arg_dir, int arg_stage)
  : pos (arg_pos), direction (arg_dir), stage (arg_stage)
{
  assert(stage >= 1 && stage <= 5);

  sprite = sprite_storage->create (std::string("shoot/laser/stage") + to_string(stage));
}

void
LaserShoot::draw ()
{
  if (direction == WEST)
    sprite->setScale (-1.0, 1.0);
  sprite->draw (int (pos.x), int (pos.y));
}

void 
LaserShoot::update (float delta)
{
  sprite->update (delta);
  if (direction == WEST)
    pos.x -= 2000 * delta;
  else
    pos.x += 2000 * delta;

  if (get_world ()->get_tilemap()->is_ground (pos.x, pos.y))
    { 
      get_world ()->add (new AnimationObj ("shoot/explosion", pos));
      remove ();
    }
}

/* EOF */