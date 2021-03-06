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

#ifndef HEADER_EDITOR_MAP_HXX
#define HEADER_EDITOR_MAP_HXX

#include <vector>
#include <ClanLib/Display/sprite.h>
#include <ClanLib/GUI/component.h>
#include <ClanLib/Core/Math/point.h>
#include "field.hxx"
#include "editor_objmap.hxx"
#include "editor_tilemap.hxx"
#include "editor_map_layer.hxx"

class EditorMapComponent;
class TileMapTool;

/** Object which represents a level, quirled together with the GUI
    stuff */
class EditorMap
{
private:
  std::string filename;

  /** Flag if the map got modified, used for 'Some maps are unsaved'
      style massages */
  bool modified;

  /** Gets incremented with each map change so that other component
      can update if required */
  int serial;

  typedef std::vector<EditorMapLayer*> Layers;
  Layers layers;

  std::vector<std::string> scripts;
  
  CL_Color background_color;
  CL_Color foreground_color;

  /** Metadata attached to this map (ie. mapname, description, scripts, etc.) */
  SCMObj metadata;
public:
  EditorMap(const std::string& filename_);
  ~EditorMap();

  std::string get_filename() const { return filename; }
  void        set_filename(const std::string& f) { filename = f; }

  void draw(EditorMapComponent* parent);

  void add_layer(EditorMapLayer* layer);

  bool is_modified() const { return modified; }
  void set_unmodified() { modified = false; }
  void modify()       { modified = true; serial += 1; }

  int get_serial() const { return serial; }

  EditorMapLayer* get_layer_by_name(int i);
  EditorMapLayer* get_layer(int i);
  void set_active_layer(int i);

  void   set_metadata(const SCMObj& obj);
  SCMObj get_metadata() const;

  bool has_bounding_rect() const { return true; }
  CL_Rect get_bounding_rect();

  void set_background_color(const CL_Color& color);
  
  std::vector<std::string> get_scripts() { return scripts; }
};

#endif

/* EOF */
