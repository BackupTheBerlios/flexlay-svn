##  $Id$
## 
##  Flexlay - A Generic 2D Game Editor
##  Copyright (C) 2002 Ingo Ruhnke <grumbel@gmx.de>
##
##  This program is free software: you can redistribute it and/or modify
##  it under the terms of the GNU General Public License as published by
##  the Free Software Foundation, either version 3 of the License, or
##  (at your option) any later version.
##  
##  This program is distributed in the hope that it will be useful,
##  but WITHOUT ANY WARRANTY; without even the implied warranty of
##  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
##  GNU General Public License for more details.
##  
##  You should have received a copy of the GNU General Public License
##  along with this program.  If not, see <http://www.gnu.org/licenses/>.

# Handle command line arguments
if ARGV != []
  puts "Usage: ./netpanzer-editor"
  exit
end

require "flexlay_wrap"
include Flexlay_wrap

require "flexlay.rb"
require "netpanzer_wrap"
include Netpanzer_wrap

require "netpanzerbrushes.rb"
require "level.rb"
require "gameobjects.rb"
require "gui.rb"

$screen  = CL_Size.new(640, 480)

$flexlay = Flexlay.new()
if ENV["FLEXLAY_DATADIR"] then
  $flexlay.set_datadir(ENV["FLEXLAY_DATADIR"])
  $flexlay_datadir = ENV["FLEXLAY_DATADIR"]
end
$flexlay.init("netPanzer Editor", $screen.width, $screen.height, false, true)

class Config
  attr_accessor :datadir, :recent_files

  def initialize()
    @datadir      = "."
    @flexlay_datadir = "."
    @recent_files = []
  end
end

$config = Config.new()

if ENV["NETPANZER_DATADIR"] then
  $netpanzer_datadir = ENV["NETPANZER_DATADIR"]
else
  $netpanzer_datadir = "/home/ingo/projects/netpanzer/netpanzer"
end

$brushes.each_with_index{|(start, width, height, name), index|
  NetPanzerData::instance().register_tilegroup(start, width, height)
}

NetPanzerData::instance().load_data($netpanzer_datadir)

$tileset = NetPanzerData::instance().get_tileset()

if ENV["NETPANZER_EDITOR_DATADIR"] then
  $config.datadir = ENV["NETPANZER_EDITOR_DATADIR"]
  $resources = CL_ResourceManager.new(ENV["NETPANZER_EDITOR_DATADIR"] + "/netpanzersprites.xml")
else
  $resources = CL_ResourceManager.new("netpanzersprites.xml")
end

# Tools
$tilemap_paint_tool  = TileMapPaintTool.new()
$tilemap_select_tool = TileMapSelectTool.new()
$workspace_move_tool = WorkspaceMoveTool.new()
$zoom_tool           = ZoomTool.new()
$objmap_select_tool  = ObjMapSelectTool.new()


def generate_sprites()
  $brushes.each_with_index{|(start, width, height, name), index|
    puts "#{index}"
    buffer = make_pixelbuffer(width * 32, height * 32)

    (0..(height-1)).each {|y|
      (0..(width-1)).each {|x|
        tile = $tileset.create(start + width * y + x)
        blit(buffer, tile.get_pixelbuffer(), x * 32, y * 32)
      }
    }
    
    CL_ProviderFactory.save(buffer, "sprites/#{index}.png")
  }
end

# generate_sprites()

$gui = GUI.new()

# $gui.set_tilemap_paint_tool()

$gui.gui_level_new()

# generate_sprites()
$gui.run()

# flexlay.deinit()
# print "deinit done"

# EOF #
