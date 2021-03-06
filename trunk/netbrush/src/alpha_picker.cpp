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

#include <vector>
#include "video.hpp"
#include "color.hpp"
#include "globals.hpp"
#include "drawing_parameter.hpp"
#include "widget/widget_manager.hpp"
#include "alpha_picker.hpp"

AlphaPicker::AlphaPicker(const Rect& rect_)
  : Widget(rect_), dragging(0)
{
  std::vector<Color> colors;

  colors.push_back(Color(255,   0,   0));
  colors.push_back(Color(255,   0, 255));
  colors.push_back(Color(  0,   0, 255));
  colors.push_back(Color(  0, 255, 255));
  colors.push_back(Color(  0, 255,   0));
  colors.push_back(Color(255, 255,   0));
  colors.push_back(Color(255,   0,   0));

  surface = create_surface(rect_.get_width(), rect_.get_height());
  set_color(Color(255,255,0));
}

void
AlphaPicker::on_mouse_motion(const MouseMotionEvent& motion)
{
  set_dirty(true);
  if (dragging)
    {
      click_pos.x = motion.x;
      click_pos.y = motion.y;
      client_draw_param->opacity = 255 * click_pos.x/get_rect().get_width();
    }
}

void
AlphaPicker::on_mouse_button(const MouseButtonEvent& button)
{
  if (button.button == 1)
    {
      if (button.state == SDL_RELEASED)
        {
          dragging = false;
          widget_manager->ungrab(this);
        }
      else if (button.state == SDL_PRESSED)
        {
          dragging = true;

          click_pos.x = button.x;
          click_pos.y = button.y;

          client_draw_param->opacity = 255 * click_pos.x/get_rect().get_width();

          set_dirty(true);
          widget_manager->grab(this);
        }
    }
}

void
AlphaPicker::draw(GraphicContext& gc)
{
  gc.blit(surface, Point(0, 0));
  gc.draw_line(Point(click_pos.x, 0),
               Point(click_pos.x, get_rect().get_height()),
               Color(0, 0, 0));
}

void
AlphaPicker::set_color(const Color& color)
{
  client_draw_param->color = color;

  SDL_LockSurface(surface);
  Uint8* data = static_cast<Uint8*>(surface->pixels);

  for(int y = 0; y < surface->h; ++y)
    for(int x = 0; x < surface->w; ++x)
      {
        Uint8 c = 255 * x / surface->w;

        Uint8 check = 0;
        if (((x / 8) % 2) ^ (y / 8) % 2)
          check = 128;

        data[3*(y * surface->w + x)+0] = (color.r*c + (255 - c)*check)/255;
        data[3*(y * surface->w + x)+1] = (color.g*c + (255 - c)*check)/255;
        data[3*(y * surface->w + x)+2] = (color.b*c + (255 - c)*check)/255;
      }
  SDL_UnlockSurface(surface);  
  
  set_dirty(true);  
}

/* EOF */
