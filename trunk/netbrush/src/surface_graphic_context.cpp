/*  $Id$
**   __      __ __             ___        __   __ __   __
**  /  \    /  \__| ____    __| _/_______/  |_|__|  | |  |   ____
**  \   \/\/   /  |/    \  / __ |/  ___/\   __\  |  | |  | _/ __ \
**   \        /|  |   |  \/ /_/ |\___ \  |  | |  |  |_|  |_\  ___/
**    \__/\  / |__|___|  /\____ /____  > |__| |__|____/____/\___  >
**         \/          \/      \/    \/                         \/
**  Copyright (C) 2005 Ingo Ruhnke <grumbel@gmx.de>
**
**  This program is free software; you can redistribute it and/or
**  modify it under the terms of the GNU General Public License
**  as published by the Free Software Foundation; either version 2
**  of the License, or (at your option) any later version.
**
**  This program is distributed in the hope that it will be useful,
**  but WITHOUT ANY WARRANTY; without even the implied warranty of
**  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**  GNU General Public License for more details.
** 
**  You should have received a copy of the GNU General Public License
**  along with this program; if not, write to the Free Software
**  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
**  02111-1307, USA.
*/

#include "SDL_gfx/SDL_gfxPrimitives.h"
#include "surface_graphic_context.hpp"

SurfaceGraphicContext::SurfaceGraphicContext(SDL_Surface* surface)
  : target(surface),
    anti_aliasing(false)
{
}

SurfaceGraphicContext::~SurfaceGraphicContext()
{
  SDL_FreeSurface(target);
}

void
SurfaceGraphicContext::fill_rect(const Rect& rect, const Color& color)
{
  boxRGBA(target,
          rect.left, rect.top, rect.right, rect.bottom,
          color.r, color.g, color.b, color.a);
}

void
SurfaceGraphicContext::draw_rect(const Rect& rect, const Color& color)
{
  boxRGBA(target,
          rect.left, rect.top, rect.right, rect.bottom,
          color.r, color.g, color.b, color.a);
}
  
void
SurfaceGraphicContext::fill_circle(const Point& pos, int radius, const Color& color)
{
  filledCircleRGBA(target,
                   pos.x, pos.y, radius,
                   color.r, color.g, color.b, color.a);
}

void
SurfaceGraphicContext::draw_circle(const Point& pos, int radius, const Color& color)
{
  circleRGBA(target,
             pos.x, pos.y, radius,
             color.r, color.g, color.b, color.a);
}

void
SurfaceGraphicContext::draw_line(const Point& p1, const Point& p2, const Color& color)
{
  aalineRGBA(target,
             p1.x, p1.y, p2.x, p2.y,
             color.r, color.g, color.b, color.a);
}

void
SurfaceGraphicContext::blit(SDL_Surface* source, const Point& pos)
{
  SDL_Rect target_rect;
  target_rect.x = pos.x;
  target_rect.y = pos.y;

  SDL_BlitSurface(source, 0, target, &target_rect);
}

void
SurfaceGraphicContext::blit(SDL_Surface* source, const Rect& src_rect, const Point& pos)
{
  SDL_Rect source_rect;
  source_rect.x = src_rect.left;
  source_rect.y = src_rect.right;
  source_rect.w = src_rect.get_width();
  source_rect.h = src_rect.get_height();

  SDL_Rect target_rect;
  target_rect.x = pos.x;
  target_rect.y = pos.y;

  SDL_BlitSurface(source, &source_rect, target, &target_rect);  
}

/* EOF */
