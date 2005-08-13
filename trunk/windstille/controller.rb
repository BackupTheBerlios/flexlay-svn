class Controller
  attr_reader :tilemap_paint_tool, :tilemap_select_tool, :zoom_tool, :objmap_select_tool, :recent_files

  def initialize()
    @tilemap_paint_tool  = TileMapPaintTool.new()
    @tilemap_select_tool = TileMapSelectTool.new()
    @zoom_tool           = ZoomTool.new()
    @objmap_select_tool  = ObjMapSelectTool.new()
    @recent_files        = []
  end
    
  def set_tilemap_paint_tool()
    $gui.workspace.set_tool(@tilemap_paint_tool.to_tool())
    $gui.set_tool_icon(:tilemap_paint)
  end

  def set_tilemap_select_tool()
    $gui.workspace.set_tool(@tilemap_select_tool.to_tool())
    $gui.set_tool_icon(:tilemap_select)
  end

  def set_zoom_tool()
    $gui.workspace.set_tool(@zoom_tool.to_tool())
    $gui.set_tool_icon(:zoom)
  end

  def set_objmap_select_tool()
    $gui.workspace.set_tool(@objmap_select_tool.to_tool())
    $gui.set_tool_icon(:object_select)
  end  

  def load_level(filename)
    $startlevel = Sector.new(filename)
    $startlevel.activate($workspace)
  end

  def save_level(filename)
    $startlevel.save(filename)
  end
end

# EOF #
