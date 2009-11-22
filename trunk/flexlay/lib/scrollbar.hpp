//  Flexlay - A Generic 2D Game Editor
//  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//  
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//  
//  You should have received a copy of the GNU General Public License
//  along with this program.  If not, see <http://www.gnu.org/licenses/>.

#ifndef HEADER_FLEXLAY_SCROLLBAR_HPP
#define HEADER_FLEXLAY_SCROLLBAR_HPP

#include <ClanLib/GUI/component.h>
#include <boost/shared_ptr.hpp>

class ScrollbarImpl;

/** */
class Scrollbar : public CL_Component
{
protected:
  virtual ~Scrollbar() {}
public:
  enum Orientation { HORIZONTAL, VERTICAL };

  Scrollbar(const CL_Rect& rect, Orientation orientation, CL_Component* parent);
  
  void set_range(float min, float max);
  void set_pagesize(float size);
  void set_pos(float pos);
  
  CL_Signal_v1<float>& sig_scrollbar_move();
private:
  boost::shared_ptr<ScrollbarImpl> impl;
};

#endif

/* EOF */
