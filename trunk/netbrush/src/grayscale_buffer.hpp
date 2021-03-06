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

#ifndef HEADER_GRAYSCALE_BUFFER_HPP
#define HEADER_GRAYSCALE_BUFFER_HPP

#include <assert.h>
#include "SDL.h"

class Rect;

class GrayscaleBuffer
{
private:
  int    width;
  int    height;
  Uint8* buffer;

public:
  enum BlendMode { OPAQUE, ALPHA, ADDITION, SUBTRACT };

  GrayscaleBuffer(SDL_Surface* surface);
  GrayscaleBuffer(int w, int h, Uint8 c);
  GrayscaleBuffer(int w, int h);
  ~GrayscaleBuffer();
  
  void blit(GrayscaleBuffer* source, SDL_Rect* srcrect, int of_x, int of_y);
  void blit(GrayscaleBuffer* source, int of_x, int of_y, Uint8 alpha, BlendMode mode);

  GrayscaleBuffer* scale(float sx, float sy);

  Uint8 interpolated_at(float x, float y) const;

  inline Uint8& at(int x, int y) 
  { 
    assert(x >= 0 && x < width && y >= 0 && y < height);
    return buffer[y * width + x];
  }

  inline Uint8 at(int x, int y) const
  { 
    assert(x >= 0 && x < width && y >= 0 && y < height);
    return buffer[y * width + x];
  }

  void clear(Uint8 c);
  void fill_rect(const Rect& rect, Uint8 c);

  Uint8* get_data() { return buffer; }

  int get_width()  const { return width; }
  int get_height() const { return height; }
};

#endif

/* EOF */
