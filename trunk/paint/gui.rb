class PaintGUI
  attr_reader :workspace, :selector_window

  def initialize()
    @editor = Editor.new()
    @gui    = @editor.get_gui_manager()
    
    @editor_map = EditorMapComponent.new($screen_rect, @gui.get_component())
    @workspace  = Workspace.new($screen_rect.get_width(), $screen_rect.get_height())
    @editor_map.set_workspace(@workspace)
    @workspace.set_tool($sketch_stroke_tool.to_tool());
    # @workspace.set_tool($layer_move_tool.to_tool());

    @selector_window_main = Window.new(CL_Rect.new(CL_Point.new($screen_rect.get_width()-160, 5), 
                                                   CL_Size.new(128 + 6 + 10, 558)),
                                       "ColorPicker",
                                       @gui.get_component())
    @selector_window = @selector_window_main.get_client_area()

    @colorpicker = ColorPicker.new(CL_Rect.new(CL_Point.new(3, 3), CL_Size.new(128, 128)),
                                   @selector_window)

    connect_v1_Color(@colorpicker.sig_color_change(), proc{|color|
                       $sketch_stroke_tool.set_color(color)
                     })

    @bgcolorpicker = ColorPicker.new(CL_Rect.new(CL_Point.new(3, 300), CL_Size.new(128, 128)),
                                     @selector_window)

    connect_v1_Color(@bgcolorpicker.sig_color_change(), proc{|color|
                       @workspace.get_map().set_background_color(color)
                     })

    @size_slider = Slider.new(CL_Rect.new(CL_Point.new(3, 150), CL_Size.new(128, 16)), @selector_window)
    @size_slider.set_range(0.01, 2.0) # FIXME: using 0 size brush makes clanlib crashi
    @size_slider.set_value(1.0)
    connect_v1_float(@size_slider.sig_on_change, proc{|value|
                       # puts "Value: #{value}"
                       $sketch_stroke_tool.set_size(value)
                     })

    @brush_hardness = Slider.new(CL_Rect.new(CL_Point.new(3, 170), CL_Size.new(128, 16)),
                                 @selector_window)
    @brush_hardness.set_range(0.0, 1.0)
    @brush_hardness.set_value(0.75)
    connect_v1_float(@brush_hardness.sig_on_change, proc{|value|
                       drawer = SpriteStrokeDrawer.new($sketch_stroke_tool.get_drawer())
                       GeneratedBrush.new(drawer.get_brush()).set_hardness(value)
                     })

    @brush_spikes = Slider.new(CL_Rect.new(CL_Point.new(3, 190), CL_Size.new(128, 16)),
                                 @selector_window)
    @brush_spikes.set_range(2, 20)
    @brush_spikes.set_value(2)
    connect_v1_float(@brush_spikes.sig_on_change, proc{|value|
                       drawer = SpriteStrokeDrawer.new($sketch_stroke_tool.get_drawer())
                       GeneratedBrush.new(drawer.get_brush()).set_spikes(value.to_i)
                     })

    @brush_aspects = Slider.new(CL_Rect.new(CL_Point.new(3, 210), CL_Size.new(128, 16)),
                                 @selector_window)
    @brush_aspects.set_range(0.1, 10)
    @brush_aspects.set_value(1)
    connect_v1_float(@brush_aspects.sig_on_change, proc{|value|
                       drawer = SpriteStrokeDrawer.new($sketch_stroke_tool.get_drawer())
                       GeneratedBrush.new(drawer.get_brush()).set_aspect_ratio(value)
                     })

    @brush_angles = Slider.new(CL_Rect.new(CL_Point.new(3, 230), CL_Size.new(128, 16)),
                                 @selector_window)
    @brush_angles.set_range(0, 360)
    @brush_angles.set_value(0)
    connect_v1_float(@brush_angles.sig_on_change, proc{|value|
                       drawer = SpriteStrokeDrawer.new($sketch_stroke_tool.get_drawer())
                       GeneratedBrush.new(drawer.get_brush()).set_angle(value)
                     })

    @brush_shape_circle  = CL_Button.new(CL_Rect.new(CL_Point.new(5, 250), CL_Size.new(40, 25)), "Circ", @selector_window)
    @brush_shape_rect    = CL_Button.new(CL_Rect.new(CL_Point.new(45, 250), CL_Size.new(40, 25)), "Squa", @selector_window)
    @brush_shape_diamond = CL_Button.new(CL_Rect.new(CL_Point.new(85, 250), CL_Size.new(40, 25)), "Diam", @selector_window)

    connect(@brush_shape_circle.sig_clicked(), proc{ 
              drawer = SpriteStrokeDrawer.new($sketch_stroke_tool.get_drawer())
              GeneratedBrush.new(drawer.get_brush()).set_shape(BRUSH_SHAPE_CIRCLE)
            })
    connect(@brush_shape_rect.sig_clicked(), proc{ 
              drawer = SpriteStrokeDrawer.new($sketch_stroke_tool.get_drawer())
              GeneratedBrush.new(drawer.get_brush()).set_shape(BRUSH_SHAPE_SQUARE)
            })
    connect(@brush_shape_diamond.sig_clicked(), proc{ 
              drawer = SpriteStrokeDrawer.new($sketch_stroke_tool.get_drawer())
              GeneratedBrush.new(drawer.get_brush()).set_shape(BRUSH_SHAPE_DIAMOND)
            })

#    @zoom_slider = Slider.new(CL_Rect.new(CL_Point.new(3, 182), CL_Size.new(128, 16)), @selector_window)
#    @zoom_slider.set_range(0.25, 10.0) # FIXME: using 0 size brush makes clanlib crashi
#    @zoom_slider.set_value(1.0)
#    connect_v1_float(@zoom_slider.sig_on_change, proc{|value|
#                       # puts "Value: #{value}"
#                       self.gui_set_zoom(value)
#                     })

    connect_v2(@editor_map.sig_on_key("escape"),  proc{ |x, y| puts "bye, bye"})
    connect_v2(@editor_map.sig_on_key("esc"),  proc{ |x, y| puts "bye, bye2"})
    connect_v2(@editor_map.sig_on_key("q"),  proc{ |x, y| $gui.quit()})
    connect_v2(@editor_map.sig_on_key("s"),  proc{ |x, y| $image.save("/tmp/test.scm")})
    connect_v2(@editor_map.sig_on_key("l"),  proc{ |x, y| 
                 $image = Image.new("/tmp/test.scm")
                 $image.activate($gui.workspace())
               })

    connect_v2(@editor_map.sig_on_key("1"),  proc{ |x, y| $animation.previous_frame()})
    connect_v2(@editor_map.sig_on_key("2"),  proc{ |x, y| $animation.next_frame()})


    connect_v2(@editor_map.sig_on_key("g"),  proc{ |x, y|
                 $gui.workspace.get_gc_state.set_rotation($gui.workspace.get_gc_state.get_rotation() - 10)
               })
    connect_v2(@editor_map.sig_on_key("c"),  proc{ |x, y| 
                 $gui.workspace.get_gc_state.set_rotation($gui.workspace.get_gc_state.get_rotation() + 10)
               })

    @normal_mode = CL_Button.new(CL_Rect.new(CL_Point.new(5, 500), CL_Size.new(40, 25)), "Norm", @selector_window)
    @erase_mode  = CL_Button.new(CL_Rect.new(CL_Point.new(45, 500), CL_Size.new(40, 25)), "Erase", @selector_window)
    @add_mode    = CL_Button.new(CL_Rect.new(CL_Point.new(85, 500), CL_Size.new(40, 25)), "Add", @selector_window)
    @shader_mode = CL_Button.new(CL_Rect.new(CL_Point.new(125, 500), CL_Size.new(40, 25)), "Shad", @selector_window)

    connect(@normal_mode.sig_clicked(), proc{ 
              drawer = SpriteStrokeDrawer.new($sketch_stroke_tool.get_drawer())
              drawer.set_mode(SpriteStrokeDrawer::DM_NORMAL)
            })
    connect(@erase_mode.sig_clicked(),  proc{ 
              drawer = SpriteStrokeDrawer.new($sketch_stroke_tool.get_drawer())
              drawer.set_mode(SpriteStrokeDrawer::DM_ERASE)
            })
    connect(@add_mode.sig_clicked(),    proc{
              drawer = SpriteStrokeDrawer.new($sketch_stroke_tool.get_drawer())
              drawer.set_mode(SpriteStrokeDrawer::DM_ADDITION)
            })
    connect(@shader_mode.sig_clicked(),    proc{
              drawer = SpriteStrokeDrawer.new($sketch_stroke_tool.get_drawer())
              drawer.set_mode(SpriteStrokeDrawer::DM_SHADER)
            })

    button_panel = ButtonPanel.new(0, 0, 33, 33*3, false, @gui.get_component)
    button_panel.add_icon("../data/images/tools/stock-tool-pencil-22.png", proc{ 
                            @workspace.set_tool($sketch_stroke_tool.to_tool())
                          })
    button_panel.add_icon("../data/images/tools/stock-tool-zoom-22.png", proc{ 
                            @workspace.set_tool($zoom_tool.to_tool())
                          })
    button_panel.add_icon("../data/images/tools/stock-tool-move-22.png", proc{ 
                            @workspace.set_tool($layer_move_tool.to_tool())
                          })

    anim_panel = ButtonPanel.new($screen_rect.get_width()/2 - (32*10)/2-16-32, 0, 32*11+1+16, 33,
                                 true, @gui.get_component)
    anim_panel.add_icon("../data/images/icons24/stock_new.png",
                        proc{ $animation.add_frame() })
    anim_panel.add_seperator()
    anim_panel.add_icon("../data/images/icons24/anim_skipbackward.png")
    anim_panel.add_icon("../data/images/icons24/anim_fastbackward.png")
    anim_panel.add_icon("../data/images/icons24/anim_playbackward.png")
    anim_panel.add_icon("../data/images/icons24/anim_slowmotionbackward.png")
    anim_panel.add_icon("../data/images/icons24/anim_previous.png",
                        proc{ $animation.previous_frame()})
    anim_panel.add_icon("../data/images/icons24/anim_next.png",
                        proc{ $animation.next_frame()})
    anim_panel.add_icon("../data/images/icons24/anim_slowmotion.png")
    anim_panel.add_icon("../data/images/icons24/anim_play.png")
    anim_panel.add_icon("../data/images/icons24/anim_fastforward.png")
    anim_panel.add_icon("../data/images/icons24/anim_skipforward.png")
  end

  def quit()
    @gui.quit()
  end

  def run()
    @gui.run()
  end
end

# EOF #