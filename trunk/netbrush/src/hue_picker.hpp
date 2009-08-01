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

#ifndef HEADER_HUE_PICKER_HPP
#define HEADER_HUE_PICKER_HPP

#include "widget/widget.hpp"

/** */
class HuePicker : public Widget
{
private:
  SDL_Surface* surface;
  bool  dragging;
  Point click_pos;

public:
  HuePicker(const Rect& rect);

  void on_mouse_motion(const MouseMotionEvent& motion);
  void on_mouse_button(const MouseButtonEvent& button);

  void set_hue(Uint8 hue);

  void on_enter() {}
  void on_leave() {}

  void draw(GraphicContext& gc);
 
private:
  HuePicker (const HuePicker&);
  HuePicker& operator= (const HuePicker&);
};

#endif

/* EOF */
