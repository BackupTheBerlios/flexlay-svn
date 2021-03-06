//  $Id$
// 
//  Flexlay - A Generic 2D Game Editor
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
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

#ifndef HEADER_EDITOR_MAP_COMPONENT_HXX
#define HEADER_EDITOR_MAP_COMPONENT_HXX

#include <vector>
#include <ClanLib/Display/sprite.h>
#include <ClanLib/GUI/component.h>
#include <ClanLib/Core/Math/point.h>
#include "field.hxx"
#include "editor_objmap.hxx"
#include "editor_tilemap.hxx"
#include "graphic_context_state.hxx"

class Workspace;
class EditorMap;
class TileMapTool;

/** Object which represents a level, quirled together with the GUI
    stuff */
class EditorMapComponent : public CL_Component
{
private:
  CL_SlotContainer slots;
  Workspace* workspace;

  static EditorMapComponent* current_; 
public:
  static EditorMapComponent* current() { return current_; } 

  EditorMapComponent(const CL_Rect& rect, CL_Component* parent);
  ~EditorMapComponent();
 
  Workspace* get_workspace() const;
  void       set_workspace(Workspace* m);

  void  set_zoom(float z);
  void  zoom_to(CL_Rect rect);
  void  zoom_out(CL_Point pos);
  void  zoom_in (CL_Point pos);

  void move_to(int x, int y);

  void draw();

  void mouse_up  (const CL_InputEvent& event);
  void mouse_down(const CL_InputEvent& event);
  void mouse_move(const CL_InputEvent& event);

  CL_Point screen2world(const CL_Point& pos);

  CL_Rect get_clip_rect();
};

#endif

/* EOF */
