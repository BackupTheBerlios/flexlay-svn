//  $Id: windstille_editor.cxx,v 1.1 2003/08/10 19:56:40 grumbel Exp $
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

#include <ClanLib/core.h>
#include <ClanLib/display.h>

#include "editor_tilemap.hxx"
#include "editor_tilemapview.hxx"
#include "windstille_editor.hxx"

WindstilleEditor::WindstilleEditor ()
  : tilemap (0)
{
}

void
WindstilleEditor::display ()
{
  std::cout << "Starting Editor..." << std::endl;

  //tilemap = new EditorTileMap ("../data/levels/level1.xml");
  if (!tilemap)
    {
      // FIXME: Move this to the scripting level
      tilemap = new EditorTileMap (50, 25);
    }

  view = new EditorTileMapView (tilemap);

  while (true)
    {
      //std::cout << "." << std::flush;
      CL_Display::clear ();
      view->draw ();
      view->update ();
      CL_Display::flip ();
      CL_System::keep_alive ();
    }
}

void
WindstilleEditor::load (const std::string& filename)
{
  tilemap = new EditorTileMap (filename);  
}

/* EOF */
