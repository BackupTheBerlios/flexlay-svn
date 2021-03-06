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
#include <fstream>
#include <ClanLib/Display/palette.h>
#include "globals.hxx"
#include "tile.hxx"
#include "../tileset.hxx"
#include "../editor_tilemap.hxx"
#include "../editor_map.hxx"
#include "../editor_names.hxx"
#include "netpanzer.hxx"

void netpanzer_set_id_header(NetPanzerFileStruct* npm, std::string s)   { npm->id_header = s; }
void netpanzer_set_name(NetPanzerFileStruct* npm, std::string s)        { npm->name = s; }
void netpanzer_set_description(NetPanzerFileStruct* npm, std::string s) { npm->description = s; }
void netpanzer_set_tilemap(NetPanzerFileStruct* npm, EditorMapLayer* t)     { npm->tilemap = t; }

std::string netpanzer_get_id_header(NetPanzerFileStruct* npm) { return npm->id_header; }
std::string netpanzer_get_name(NetPanzerFileStruct* npm) { return npm->name; }
std::string netpanzer_get_description(NetPanzerFileStruct* npm) { return npm->description; }
EditorMapLayer* netpanzer_get_tilemap(NetPanzerFileStruct* npm) { return npm->tilemap; }

CL_Palette netpanzer_load_palette(const char* filename)
{
  CL_Palette palette;
  unsigned char color_array[256 * 3];

  std::ifstream in(filename);

  if (!in)
    {
      std::cout << "Couldn't load palette" << std::endl;
      return palette;
    }

  in.read(reinterpret_cast<char*>(color_array), sizeof(color_array));

  for(int i = 0; i < 256; ++i)
    {
      palette.colors[i].set_red  (color_array[3*i + 0]);
      palette.colors[i].set_green(color_array[3*i + 1]);
      palette.colors[i].set_blue (color_array[3*i + 2]);
    }

  return palette;
}

unsigned char find_nearest_color(const CL_Palette& palette, const CL_Color& rgb)
{ // Copyright (C) 1998 Pyrosoft Inc. (www.pyrosoftgames.com), Matthew Bogue
  float bestDist = 10000000.0f;
  int   best     = 0;
                                                                                                                
  float vPic = sqrt(rgb.get_red() * rgb.get_red() 
                    + rgb.get_green() * rgb.get_green()
                    + rgb.get_blue() * rgb.get_blue()) * 0.57735027;
 
  for (int i = 0; i < 256; i++) {
    float vPal = sqrt(palette.colors[i].get_red()     * palette.colors[i].get_red()
                      + palette.colors[i].get_green() * palette.colors[i].get_green()
                      + palette.colors[i].get_blue()  * palette.colors[i].get_blue()) * 0.57735027;
                                                                                                                
    float dr = palette.colors[i].get_red()   - rgb.get_red();
    float dg = palette.colors[i].get_green() - rgb.get_green();
    float db = palette.colors[i].get_blue()  - rgb.get_blue();
    float dv = vPal-vPic;
    float dist = dr * dr * 0.3 + dg * dg * 0.59 + db * db * 0.11 + dv * dv * 0.7;
                                                                                                                
    if (dist < bestDist) {
      bestDist = dist;
      best = i;
    }
  }
                                                                                                                
  return best;
                                                                                                                
}

void
save_netpanzer_map(const char* filename, EditorMap* m, 
                   const char* id_header_, const char* name_, const char* description_)
{
  EditorTileMap* tilemap = dynamic_cast<EditorTileMap*>(m->get_layer_by_name(TILEMAP_NAME));

  if (!tilemap)
    return;
    
  unsigned char   netp_id_header[64];
  strcpy(reinterpret_cast<char*>(netp_id_header), id_header_);
  unsigned short  id       = 0; // ?
  char   name[256];
  strcpy(name, name_);
  char   description[1024];
  strcpy(description, description_);
  unsigned short  x_size   = tilemap->get_width();
  unsigned short  y_size   = tilemap->get_height();
  char            tile_set[256] = "summer12mb.tls";
 
  unsigned short  thumbnail_x_pix = tilemap->get_width();
  unsigned short  thumbnail_y_pix = tilemap->get_height();
    
  std::ofstream out(filename);

  out.write(reinterpret_cast<char*>(&netp_id_header), sizeof(netp_id_header));
  out.write(reinterpret_cast<char*>(&id), sizeof(short));
  out.write(reinterpret_cast<char*>(&name), sizeof(name));
  out.write(reinterpret_cast<char*>(&description), sizeof(description));
  out.write(reinterpret_cast<char*>(&x_size), sizeof(short));
  out.write(reinterpret_cast<char*>(&y_size), sizeof(short));
  out.write(reinterpret_cast<char*>(&tile_set), sizeof(tile_set));
  out.write(reinterpret_cast<char*>(&thumbnail_x_pix), sizeof(short));
  out.write(reinterpret_cast<char*>(&thumbnail_y_pix), sizeof(short));

  std::vector<unsigned short> vec(x_size * y_size);

  Field<int>* field = tilemap->get_map();
  for(int i = 0; i < x_size * y_size; ++i)
    {
      vec[i] = (*field)[i];
    }
  out.write(reinterpret_cast<char*>(&(*vec.begin())), 
            sizeof(unsigned short)*vec.size());

  // Generate thumbnail
  CL_Palette palette = netpanzer_load_palette((datadir + "netp.act").c_str());
  
  std::vector<unsigned char> thumbnail(x_size * y_size);
  for(int i = 0; i < int(thumbnail.size()); ++i)
    {
      Tile* tile = Tileset::current()->create((*field)[i]);
      if (tile)
        thumbnail[i] = find_nearest_color(palette, tile->get_color());
    }

  out.write(reinterpret_cast<char*>(&(*thumbnail.begin())), 
            sizeof(unsigned char)*thumbnail.size());
}

NetPanzerFileStruct*
load_netpanzer_map(const char* filename)
{
  // FIXME: endian issues
  unsigned char   netp_id_header[64]; // Copyright PyroSoft Inc.  ...
  unsigned short  id; // What is this?
  char   name[256];
  char   description[1024];
  unsigned short  x_size; // width
  unsigned short  y_size; // height
  char            tile_set[256]; // name of the tileset: "summer12mb.tls"
 
  unsigned short  thumbnail_x_pix;
  unsigned short  thumbnail_y_pix;

  std::ifstream file(filename);

  if (!file)
    return 0;

  file.read(reinterpret_cast<char*>(&netp_id_header), sizeof(netp_id_header));
  file.read(reinterpret_cast<char*>(&id), sizeof(short));
  file.read(reinterpret_cast<char*>(&name), sizeof(name));
  file.read(reinterpret_cast<char*>(&description), sizeof(description));
  file.read(reinterpret_cast<char*>(&x_size), sizeof(short));
  file.read(reinterpret_cast<char*>(&y_size), sizeof(short));
  file.read(reinterpret_cast<char*>(&tile_set), sizeof(tile_set));
  file.read(reinterpret_cast<char*>(&thumbnail_x_pix), sizeof(short));
  file.read(reinterpret_cast<char*>(&thumbnail_y_pix), sizeof(short));

  EditorTileMap* tilemap = new EditorTileMap(0, x_size, y_size, 32);
  Field<int>* field      = tilemap->get_map();

  std::vector<unsigned short> vec;
  vec.resize(x_size * y_size);
  file.read(reinterpret_cast<char*>(&(*vec.begin())), sizeof(unsigned short)*vec.size());

  for(int i = 0; i < x_size*y_size; ++i)
    (*field)[i] = vec[i];

  std::cout << "Thumbnail: " << thumbnail_x_pix << " " << thumbnail_y_pix << std::endl;

  NetPanzerFileStruct* netpanzer_file = new NetPanzerFileStruct;

  netpanzer_file->tilemap     = tilemap;
  netpanzer_file->id_header   = reinterpret_cast<char*>(netp_id_header);
  netpanzer_file->name        = name;
  netpanzer_file->description = description;

  return netpanzer_file;
}

/* EOF */
