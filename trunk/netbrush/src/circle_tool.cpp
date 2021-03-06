/*            _   ___              _   
**   _ _  ___| |_| _ )_ _ _  _ _ _| |_ 
**  | ' \/ -_)  _| _ \ '_| || (_-<|   |
**  |_||_\___|\__|___/_|  \_,_/__/|_|_|
**  netBrush - Copyright (C) 2006 Ingo Ruhnke <grumbel@gmx.de>
**
**  This program is free software: you can redistribute it and/or modify
**  it under the terms of the GNU General Public License as published by
**  the Free Software Foundation, either version 3 of the License, or
**  (at your option) any later version.
**  
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
**  
**  You should have received a copy of the GNU General Public License
**  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <sstream>
#include <iostream>
#include "SDL_gfx/SDL_gfxPrimitives.h"
#include "globals.hpp"
#include "screen_buffer.hpp"
#include "drawing_parameter.hpp"
#include "server_connection.hpp"
#include "circle_tool.hpp"

CircleTool::CircleTool()
  : radius(0.0f), dragging(false)
{
}

void
CircleTool::on_motion(const ToolMotionEvent& ev)
{
  Vector pos(ev.x, ev.y);
  radius = (click_pos - pos).length();

  if (dragging)
    screen_buffer->force_full_refresh();
  
  //std::cout << "drawing: " << click_pos.x << " " << click_pos.y << " " << radius << std::endl;
}

void
CircleTool::on_button_press(const ToolButtonEvent& ev)
{
  dragging = true;

  click_pos.x = ev.x;
  click_pos.y = ev.y;
}

void
CircleTool::on_button_release(const ToolButtonEvent& ev)
{
  dragging = false;

  Vector pos(ev.x, ev.y);
  radius = (click_pos - pos).length();

  std::ostringstream str;
  str << "set_color "
      << int(client_draw_param->color.r) << " " 
      << int(client_draw_param->color.g) << " " 
      << int(client_draw_param->color.b) << std::endl;

  str << "set_opacity " << int(client_draw_param->opacity) << std::endl;

  str << "fill_circle "
      << int(click_pos.x) << " " << int(click_pos.y) << " "
      << int(radius)
      << std::endl;

  server->send(str.str());
}

void
CircleTool::draw(SDL_Surface* target, const Rect& rect, int x_of, int y_of)
{
  if (dragging)
    filledCircleRGBA(target,
                     int(click_pos.x + x_of), 
                     int(click_pos.y + y_of),
                     int(radius),
                     client_draw_param->color.r,
                     client_draw_param->color.g,
                     client_draw_param->color.b,
                     client_draw_param->opacity);
}

/* EOF */
