//  $Id$
//
//  Pingus - A free Lemmings clone
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

#include <iostream>
#include <ClanLib/Display/display.h>
#include <ClanLib/Display/keys.h>
#include "tileset.hxx"
#include "editor_names.hxx"
#include "editor_map.hxx"
#include "tool_manager.hxx"
#include "tilemap_tool.hxx"
#include "editor.hxx"
#include "editor_map_component.hxx"

EditorMapComponent* EditorMapComponent::current_ = 0; 

EditorMapComponent::EditorMapComponent(const CL_Rect& rect, CL_Component* parent)
  : CL_Component(rect, parent),
    gc_state(this)
{
  current_ = this;

  slots.connect(sig_paint(),      this, &EditorMapComponent::draw);
  slots.connect(sig_mouse_up(),   this, &EditorMapComponent::mouse_up);
  slots.connect(sig_mouse_down(), this, &EditorMapComponent::mouse_down);
  slots.connect(sig_mouse_move(), this, &EditorMapComponent::mouse_move);

  zoom_factor = 0;

  editor_map = 0;

  scrolling = false;
}

EditorMapComponent::~EditorMapComponent()
{
}

void
EditorMapComponent::mouse_up(const CL_InputEvent& event)
{
  switch (event.id)
    {
    case CL_MOUSE_LEFT:
    case CL_MOUSE_RIGHT:
      Editor::current()->get_tool_manager()->current_tool()->on_mouse_up(event);
      break;

    case CL_MOUSE_MIDDLE:
      scrolling = false;
      gc_state.set_pos(CL_Pointf(old_trans_offset.x - (click_pos.x - event.mouse_pos.x),
                                 old_trans_offset.y - (click_pos.y - event.mouse_pos.y)));
      old_trans_offset = gc_state.get_pos();
      release_mouse();
      break;
    }
}

void
EditorMapComponent::mouse_move(const CL_InputEvent& event)
{
  Editor::current()->get_tool_manager()->current_tool()->on_mouse_move(event);

  if (scrolling)
    {
      gc_state.set_pos(CL_Pointf(old_trans_offset.x - (click_pos.x - event.mouse_pos.x),
                                 old_trans_offset.y - (click_pos.y - event.mouse_pos.y)));
    }
}

void
EditorMapComponent::mouse_down(const CL_InputEvent& event)
{
  switch (event.id)
    {
    case CL_MOUSE_LEFT:
    case CL_MOUSE_RIGHT:
      Editor::current()->get_tool_manager()->current_tool()->on_mouse_down(event);
      break;

    case CL_MOUSE_MIDDLE:
      scrolling = true;
      old_trans_offset = gc_state.get_pos();
      click_pos = event.mouse_pos;
      capture_mouse();
      break;
           
    case CL_MOUSE_WHEEL_UP:
      zoom_in();
      break;

    case CL_MOUSE_WHEEL_DOWN:
      zoom_out();
      break;
    }
}
  
void
EditorMapComponent::draw ()
{
  gc_state.push();

  CL_Display::clear(CL_Color(100, 0, 100));

  if (editor_map)
    editor_map->draw(this);

  if (1) // has_mouse_over()) FIXME: Seperate cursor and state here
    Editor::current()->get_tool_manager()->current_tool()->draw();
    
  CL_Display::flush();

  gc_state.pop();
}

CL_Point
EditorMapComponent::screen2world(const CL_Point& pos)
{
  return gc_state.screen2world(pos);
}

void
EditorMapComponent::zoom_out()
{
  gc_state.set_zoom(gc_state.get_zoom()/1.25f);
  //zoom_factor -= 1;
  //std::cout << "Zoom: " << get_zoom() << std::endl;
}

void
EditorMapComponent::zoom_in()
{
  gc_state.set_zoom(gc_state.get_zoom()*1.25f);
  //zoom_factor += 1;
  //std::cout << "Zoom: " << get_zoom() << std::endl;
}

float
EditorMapComponent::get_zoom()
{
  return gc_state.get_zoom();
  /*
  if (zoom_factor > 0)
    return 1.0f * (zoom_factor + 1);
  else if (zoom_factor < 0)
    return 1.0f / (-zoom_factor + 1);
  else
    return 1.0f;
  */
}

void
EditorMapComponent::set_zoom(float z)
{
  gc_state.set_zoom(z);
  /*
    if (z > 0)
    {
    if (z == 1.0f)
    zoom_factor = 0;
    else if (z < 1.0f)
    zoom_factor = int(1 - 1/z);
    else if (z > 1.0f)
    zoom_factor = int(z);

    gc.set_zoom(z);
    }
    else
    {
    std::cout << "Illegal zoom value: " << z << std::endl;
    }
  */
}

CL_Rect
EditorMapComponent::get_clip_rect()
{
  return gc_state.get_clip_rect();
}

void
EditorMapComponent::move_to(int x, int y)
{
  gc_state.set_pos(CL_Pointf(x, y));
}

/* EOF */
