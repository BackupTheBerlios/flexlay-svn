##  $Id$
## 
##  Flexlay - A Generic 2D Game Editor
##  Copyright (C) 2004 Ingo Ruhnke <grumbel@gmx.de>
##
##  This program is free software; you can redistribute it and/or
##  modify it under the terms of the GNU General Public License
##  as published by the Free Software Foundation; either version 2
##  of the License, or (at your option) any later version.
##
##  This program is distributed in the hope that it will be useful,
##  but WITHOUT ANY WARRANTY; without even the implied warranty of
##  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##  GNU General Public License for more details.
## 
##  You should have received a copy of the GNU General Public License
##  along with this program; if not, write to the Free Software
##  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

class Level
  ## Level Properties
  attr_reader :layers, :editormap
  attr_reader :background, :interactive, :foreground

  attr_reader :name
  attr_writer :name

  def initialize(*params)
    if params.length() == 2 then
      initialize_new(*params)
    else 
      initialize_from_file(*params)
    end
  end

  def initialize_new(width, height)
    # New Level
    (@width, @height) = [width, height]
    
    @current_layer = 0
    
    @background  = TilemapLayer.new($tileset, @width, @height)
    @interactive = TilemapLayer.new($tileset, @width, @height)
    @foreground  = TilemapLayer.new($tileset, @width, @height)
    
    @layers = []
    @layers += [@background]
    @layers += [@interactive]
    @layers += [@foreground]
    @layers += [@objects = ObjectLayer.new()]

    @editormap = EditorMap.new()
    @layers.each {|layer| @editormap.add_layer(layer.to_layer()) }
    
    # FIXME: Data might not get freed since its 'recursively' refcounted
    @editormap.set_metadata(make_metadata(self))
  end

  def initialize_from_file(filename)
    tree = sexpr_read_from_file(filename)
    if tree == nil
      raise("Couldn't load level: %s" % filename)
    end
    
    data = tree[1..-1]
    
    @version = get_value_from_tree(["version", "_"], data, 0)
    @name    = get_value_from_tree(["name", "_"],    data, 0)
    @author  = get_value_from_tree(["author", "_"],  data, 0)
    @width   = get_value_from_tree(["width", "_"],   data, 0)
    @height  = get_value_from_tree(["height", "_"],  data, 0)
    @music   = get_value_from_tree(["music", "_"],   data, 0)

    load_tilemap = proc {|name|
      mydata   = get_value_from_tree(["#{name}-tilemap"],  data, 0)
      width  = get_value_from_tree(["width", "_"],  mydata, 0)
      height = get_value_from_tree(["height", "_"],  mydata, 0)

      tilemap = TilemapLayer.new($tileset, width, height)
      tilemap.set_data(get_value_from_tree(["data"], mydata, []))
      tilemap
    }
    
    @background  = load_tilemap.call("background")
    @interactive = load_tilemap.call("interactive")
    @foreground  = load_tilemap.call("foreground")

    @layers = [@background, @interactive, @foreground]

    @editormap = EditorMap.new()
    @layers.each {|layer| @editormap.add_layer(layer.to_layer()) }
    
    # FIXME: Data might not get freed since its 'recursively' refcounted
    @editormap.set_metadata(make_metadata(self))

    @current_layer = 0

    puts @editormap
    puts @layers
  end

  def activate(workspace)
    $gui.workspace.set_map(@editormap)

    TilemapLayer.set_current(@layers[@current_layer])
    ObjectLayer.set_current(@objects)
  end

  def save(filename)
    print "Save Level to '", filename, "'\n"

    ## Insert your load code here
    f = File.new(filename, "w")
    f.write(";; Generated by Flexlay Editor\n")
    f.write("(windstille-sector\n")
    f.write("  (version 1)\n")
    f.write("  (name   \"%s\")\n" % @name)
    f.write("  (author \"%s\")\n" % @author)
    f.write("  (width  %d)\n"  % @width)
    f.write("  (height  %d)\n" % @height)
    
    f.write("  (music  \"%s\")\n" % @music)

    save_tilemap = proc {|name, tilemap|
      width  = tilemap.get_width()
      height = tilemap.get_height()
      f.write("  (%s-tilemap (width %d) (height %d)\n" % \
              [name, width, height])
      f.write("    (data")
      tilemap.get_data().each_with_index {|item, i|
        if (i % width == 0) then
          f.write("\n      ")
        end
        f.write("%d " % item)
      }
      f.write("\n     ))\n")
    }

    save_tilemap.call("background",  @background)
    save_tilemap.call("interactive", @interactive)
    save_tilemap.call("foreground",  @foreground)
    
    f.write(" )\n\n")
    f.write(";; EOF ;;\n")
    f.close()
  end
end

# EOF #
