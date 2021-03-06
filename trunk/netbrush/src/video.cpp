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

#include <algorithm>
#include "math/rect.hpp"
#include "video.hpp"

SDL_Surface* screen = 0;

void clip_to(SDL_Rect* rect, SDL_Rect* clip_rect)
{
  int x1 = std::max(clip_rect->x, rect->x);
  int y1 = std::max(clip_rect->y, rect->y);

  int x2 = std::min(clip_rect->x + clip_rect->w, rect->x + rect->w);
  int y2 = std::min(clip_rect->y + clip_rect->h, rect->y + rect->h);  

  rect->x = x1;
  rect->y = y1;

  rect->w = x2 - x1;
  rect->h = y2 - y1;
}

void clip_to(Rect& rect, const Rect& clip_rect)
{
  rect.left   = std::max(rect.left,   clip_rect.left);
  rect.right  = std::min(rect.right,  clip_rect.right);
  rect.top    = std::max(rect.top,    clip_rect.top);
  rect.bottom = std::min(rect.bottom, clip_rect.bottom);
}

SDL_Surface* create_surface(int w, int h)
{
  Uint32 rmask, gmask, bmask, amask;

  /* SDL interprets each pixel as a 32-bit number, so our masks must depend
     on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
  rmask = 0xff000000;
  gmask = 0x00ff0000;
  bmask = 0x0000ff00;
  amask = 0; //0x000000ff;
#else
  rmask = 0x000000ff;
  gmask = 0x0000ff00;
  bmask = 0x00ff0000;
  amask = 0; //0xff000000;
#endif

  SDL_Surface* drawable = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 24,
                                  rmask, gmask, bmask, amask);
  if(drawable == NULL) {
    fprintf(stderr, "CreateRGBSurface failed: %s\n", SDL_GetError());
    exit(1);
  }

  return drawable;
}

/* EOF */
