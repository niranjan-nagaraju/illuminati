#include "illuminati.h"

GtkWidget* new_button;
GtkWidget* open_button;
GtkWidget* save_button;
GtkWidget* print_button;
GtkWidget* undo_button;
GtkWidget* redo_button;
GtkWidget* cut_button;
GtkWidget* copy_button;
GtkWidget* paste_button;
GtkWidget* zoom_in_button;
GtkWidget* zoom_out_button;
GtkWidget* what_is_button;


GtkWidget* get_main_toolbar()
{
  /* Ok, we need a toolbar, an icon with a mask (one for all of 
     the buttons) and an icon widget to put this icon in (but 
     we'll create a separate widget for each button) */
  GtkWidget * toolbar;
  GtkWidget * iconw;


  /* typically we quit if someone tries to close us */
  /* toolbar will be horizontal, with both icons and text, and
   * with 5pxl spaces between items and finally, 
   * we'll also put it into our handlebox */

  toolbar = gtk_toolbar_new ();
 
  gtk_toolbar_set_orientation (GTK_TOOLBAR (toolbar), GTK_ORIENTATION_HORIZONTAL);
 
  gtk_toolbar_set_style (GTK_TOOLBAR (toolbar), GTK_TOOLBAR_BOTH);
 
  gtk_container_set_border_width (GTK_CONTAINER (toolbar), 0);

  
 
  iconw = gtk_image_new_from_stock (GTK_STOCK_NEW,2); /*<new> icon widget */

  new_button = gtk_toolbar_append_item (GTK_TOOLBAR (toolbar), /* our toolbar */
                            "New",               /* button label */
                            "Opens the new file",/* this button's tooltip */
                            "Private",           /* tooltip private info */
                            iconw,               /* icon widget */
                            GTK_SIGNAL_FUNC (new_file), /* a signal */
                            NULL);

  iconw = gtk_image_new_from_stock (GTK_STOCK_OPEN,2); /*<open> icon widget */

  open_button = gtk_toolbar_append_item (GTK_TOOLBAR (toolbar), /* our toolbar */
                            "Open",               /* button label */
                            "Opens the existing file",/* this button's tooltip */
                            "Private",           /* tooltip private info */
                            iconw,               /* icon widget */
                            GTK_SIGNAL_FUNC (open_file), /* a signal */
                            NULL);
  iconw = gtk_image_new_from_stock (GTK_STOCK_SAVE,2); /*<save> icon widget */

  save_button = gtk_toolbar_append_item (GTK_TOOLBAR (toolbar), /* our toolbar */
                            "Save",               /* button label */
                            "Save the buffer",   /* this button's tooltip */
                            "Private",           /* tooltip private info */
                            iconw,               /* icon widget */
                            GTK_SIGNAL_FUNC (save_file), /* a signal */
                            NULL);
 
  gtk_toolbar_append_space (GTK_TOOLBAR (toolbar)); /* space after item */

  iconw = gtk_image_new_from_stock (GTK_STOCK_UNDO,2); /*<undo> icon widget */

  undo_button = gtk_toolbar_append_item (GTK_TOOLBAR (toolbar), /* our toolbar */
                            "Undo",               /* button label */
                            "Undoes the last action",/* this button's tooltip */
                            "Private",           /* tooltip private info */
                            iconw,               /* icon widget */
                            GTK_SIGNAL_FUNC (undo), /* a signal */
                            NULL);

  iconw = gtk_image_new_from_stock (GTK_STOCK_REDO,2); /*<redo> icon widget */

  redo_button = gtk_toolbar_append_item (GTK_TOOLBAR (toolbar), /* our toolbar */
                            "Redo",               /* button label */
                            "Redo the last action",/* this button's tooltip */
                            "Private",           /* tooltip private info */
                            iconw,               /* icon widget */
                            GTK_SIGNAL_FUNC (redo), /* a signal */
                            NULL);



  iconw = gtk_image_new_from_stock (GTK_STOCK_CUT,2); /*<cut> icon widget */

  cut_button = gtk_toolbar_append_item (GTK_TOOLBAR (toolbar), /* our toolbar */
                            "Cut",               /* button label */
                            "Cut the selected object",/* this button's tooltip */
                            "Private",           /* tooltip private info */
                            iconw,               /* icon widget */
                            GTK_SIGNAL_FUNC (cut), /* a signal */
                            NULL);
  gtk_button_set_focus_on_click(GTK_BUTTON(cut_button),TRUE);

  iconw = gtk_image_new_from_stock (GTK_STOCK_COPY,2); /*<copy> icon widget */

  copy_button = gtk_toolbar_append_item (GTK_TOOLBAR (toolbar), /* our toolbar */
                            "Copy",               /* button label */
                            "Copy the selected object",/* this button's tooltip */
                            "Private",           /* tooltip private info */
                            iconw,               /* icon widget */
                            GTK_SIGNAL_FUNC (copy), /* a signal */
                            NULL);
  gtk_button_set_focus_on_click(GTK_BUTTON(copy_button),TRUE);

  iconw = gtk_image_new_from_stock (GTK_STOCK_PASTE,2); /*<paste> icon widget */

  paste_button = gtk_toolbar_append_item (GTK_TOOLBAR (toolbar), /* our toolbar */
                            "Paste",               /* button label */
                            "Paste at selected location",/* this button's tooltip */
                            "Private",           /* tooltip private info */
                            iconw,               /* icon widget */
                            GTK_SIGNAL_FUNC (paste), /* a signal */
                            NULL);
  gtk_button_set_focus_on_click(GTK_BUTTON(copy_button),TRUE);

  gtk_toolbar_append_space (GTK_TOOLBAR (toolbar)); /* space after item */


  iconw = gtk_image_new_from_stock (GTK_STOCK_ZOOM_IN,2); /*<zoom-in> icon widget */

  zoom_in_button = gtk_toolbar_append_item (GTK_TOOLBAR (toolbar), /* our toolbar */
                            "Zoom",               /* button label */
                            "Zoom In the image",/* this button's tooltip */
                            "Private",           /* tooltip private info */
                            iconw,               /* icon widget */
                            GTK_SIGNAL_FUNC (zoom), /* a signal */
                            (gpointer)2);
  iconw = gtk_image_new_from_stock (GTK_STOCK_ZOOM_OUT,2); /*<zoom-out> icon widget */

  zoom_out_button = gtk_toolbar_append_item (GTK_TOOLBAR (toolbar), /* our toolbar */
                            "Zoom",               /* button label */
                            "Zoom Out the image",/* this button's tooltip */
                            "Private",           /* tooltip private info */
                            iconw,               /* icon widget */
                            GTK_SIGNAL_FUNC (zoom), /* a signal */
                           (gpointer)1);



  iconw = gtk_image_new_from_file ("icons/apple-red.png"); /*<what's> icon widget */

  what_is_button = gtk_toolbar_append_item (GTK_TOOLBAR (toolbar), /* our toolbar */
                             NULL,               /* button label */
                            "About Illuminati",/* this button's tooltip */
                            "Private",           /* tooltip private info */
                            iconw,               /* icon widget */
                            GTK_SIGNAL_FUNC (about_illuminatti), /* a signal */
                            NULL);

   gtk_widget_show(toolbar);

   return toolbar;
}

GtkWidget*  select_rect_button;

GtkWidget*   eraser_button;

GtkWidget*   line_button;

GtkWidget*   text_button;

GtkWidget*   paintbrush_button;

GtkWidget*   spraycan_button;

GtkWidget*   bucketfill_button;

GtkWidget*   colorpick_button;

GtkWidget*   polyline_button;

GtkWidget*   ellipse_button ;

GtkWidget*    polygon_button;

GtkWidget*    rectangle_button;

GtkWidget*     round_rect_button;



void setcurrenttool(GtkWidget *w,gpointer data)
{
  GError *error= NULL;
  gtk_button_set_relief(GTK_BUTTON(pencil_button),GTK_RELIEF_NONE);

  switch((gint)data)
  {
    case RECT_SEL:
                  tool=RECT_SEL;
                  selected=0;
                  sel_pixmap = gdk_pixmap_new(NULL,640,480,24);
                  display=gdk_display_get_default();              
                  cursor=gdk_cursor_new(GDK_CROSS);
                  gdk_window_set_cursor(drawing_area->window,cursor); 
                  break;

    case ERASER: gdk_draw_drawable(undomap,fg_gc,pixmap,0,0,0,0,-1,-1);
                 undoflag=1;
                 tool=ERASER;
                 display=gdk_display_get_default();              
                 cursor=gdk_cursor_new(GDK_DOTBOX);
                 gdk_window_set_cursor(drawing_area->window,cursor);
                   break;

    case LINE:  gdk_draw_drawable(undomap,fg_gc,pixmap,0,0,0,0,-1,-1);
                undoflag=1;
                tool=LINE; 
                display=gdk_display_get_default();              
                cursor=gdk_cursor_new(GDK_TCROSS);
                gdk_window_set_cursor(drawing_area->window,cursor);
                break;

    case TEXT:  gdk_draw_drawable(undomap,fg_gc,pixmap,0,0,0,0,-1,-1);
                undoflag=1;
                tool=TEXT;
                break;

    case BRUSH: gdk_draw_drawable(undomap,fg_gc,pixmap,0,0,0,0,-1,-1);
                undoflag=1;
                tool=BRUSH;
                display=gdk_display_get_default();              
      cursorbuf=gdk_pixbuf_new_from_file("icons/brush.png",&error); 
      cursor=gdk_cursor_new_from_pixbuf(display,cursorbuf,
                gdk_pixbuf_get_width(cursorbuf)-1,
                gdk_pixbuf_get_height(cursorbuf)-1);            
                gdk_window_set_cursor(drawing_area->window,cursor);

                break;

    case SPRAYCAN: gdk_draw_drawable(undomap,fg_gc,pixmap,0,0,0,0,-1,-1);
                undoflag=1;
                tool=SPRAYCAN;

      display=gdk_display_get_default(); 
      cursorbuf=gdk_pixbuf_new_from_file("icons/tool_spraycan.png",&error); 
      cursor=gdk_cursor_new_from_pixbuf(display,cursorbuf,
                gdk_pixbuf_get_width(cursorbuf)-1,
                gdk_pixbuf_get_height(cursorbuf)-1);            
                gdk_window_set_cursor(drawing_area->window,cursor);

                break;


    case PENCIL: gdk_draw_drawable(undomap,fg_gc,pixmap,0,0,0,0,-1,-1);
                 undoflag=1;
                 tool=PENCIL;
                 display=gdk_display_get_default();              
                 cursor=gdk_cursor_new(GDK_PENCIL);
                 gdk_window_set_cursor(drawing_area->window,cursor);

                 break;

    case BUCKET: gdk_draw_drawable(undomap,fg_gc,pixmap,0,0,0,0,-1,-1);
                 undoflag=1;
                 tool=BUCKET;
      display=gdk_display_get_default(); 
      cursorbuf=gdk_pixbuf_new_from_file("/home/manju/illuminati/icons/bucket-fill.png",&error); 
      cursor=gdk_cursor_new_from_pixbuf(display,cursorbuf,
                gdk_pixbuf_get_width(cursorbuf)-1,
                gdk_pixbuf_get_height(cursorbuf)-1);    
		cursor=gdk_cursor_new(GDK_LEFT_PTR);
                gdk_window_set_cursor(drawing_area->window,cursor);
	        break;
  
    case COLORPICK: tool=COLORPICK;
		      cursor=gdk_cursor_new(GDK_HAND2);
		      gdk_window_set_cursor(drawing_area->window,cursor);
	                    break;

    case POLYLINE: gdk_draw_drawable(undomap,fg_gc,pixmap,0,0,0,0,-1,-1);
                   undoflag=1;
                   poly=0;
                   tool=POLYLINE;
                   display=gdk_display_get_default();              
                   cursor=gdk_cursor_new(GDK_CROSS);
                   gdk_window_set_cursor(drawing_area->window,cursor);
                   break;

    
      
    case ELLIPSE:gdk_draw_drawable(undomap,fg_gc,pixmap,0,0,0,0,-1,-1);
                 undoflag=1; 
                 tool=ELLIPSE;
                 display=gdk_display_get_default();              
                 cursor=gdk_cursor_new(GDK_TCROSS);
                 gdk_window_set_cursor(drawing_area->window,cursor);
                  break;
   
    case POLYGON:gdk_draw_drawable(undomap,fg_gc,pixmap,0,0,0,0,-1,-1);
                 undoflag=1;
                 poly=0;
                 lineflag=0;
                 tool=POLYGON;
                 display=gdk_display_get_default();              
                 cursor=gdk_cursor_new(GDK_CROSS);
                 gdk_window_set_cursor(drawing_area->window,cursor);
                  break;

    case RECTANGLE:gdk_draw_drawable(undomap,fg_gc,pixmap,0,0,0,0,-1,-1);
                   undoflag=1;
                   tool=RECTANGLE;
                 display=gdk_display_get_default();              
                 cursor=gdk_cursor_new(GDK_CROSSHAIR);
                 gdk_window_set_cursor(drawing_area->window,cursor);

                    break;
   }
}


GtkWidget *get_tools_toolbar()
{

  GtkWidget * toolbar;
  GtkWidget * htoolbar;
  GtkWidget * iconw;
  GtkWidget*  hbox;

  toolbar = gtk_toolbar_new ();
 
  gtk_toolbar_set_orientation (GTK_TOOLBAR (toolbar), GTK_ORIENTATION_VERTICAL);
 
  gtk_toolbar_set_style (GTK_TOOLBAR (toolbar), GTK_TOOLBAR_ICONS);
 
  gtk_container_set_border_width (GTK_CONTAINER (toolbar), 1);


  gtk_toolbar_set_show_arrow(GTK_TOOLBAR(toolbar),TRUE);
                                         

 
  iconw = gtk_image_new_from_file ("icons/rect-select.png"); 

  select_rect_button = gtk_toolbar_append_item (GTK_TOOLBAR (toolbar),
                            "Selection",              
                            "Selection",
                            "Private",           
                            iconw,               
                            GTK_SIGNAL_FUNC (setcurrenttool), 
                            (gpointer)RECT_SEL);
  gtk_button_set_focus_on_click(GTK_BUTTON(select_rect_button),TRUE);

  iconw = gtk_image_new_from_file ("icons/eraser.png"); 

  eraser_button = gtk_toolbar_append_item (GTK_TOOLBAR (toolbar), 
                            "eraser",               
                            "Eraser",
                            "Private",           
                            iconw,              
                            GTK_SIGNAL_FUNC (setcurrenttool),
                            (gpointer)ERASER);
  gtk_button_set_focus_on_click   (GTK_BUTTON(eraser_button),TRUE);

 
  iconw = gtk_image_new_from_file ("icons/tool_line.png"); 

  line_button = gtk_toolbar_append_item (GTK_TOOLBAR (toolbar), 
                            "Line",              
                            "Draws a line",
                            "Private",     
                            iconw,         
                            GTK_SIGNAL_FUNC (setcurrenttool), 
                            (gpointer)LINE);
  gtk_button_set_focus_on_click   (GTK_BUTTON(line_button),TRUE);

  iconw = gtk_image_new_from_file ("icons/text.png"); 

  text_button = gtk_toolbar_append_item (GTK_TOOLBAR (toolbar), 
                            "Text",              
                            "Add the text",
                            "Private",     
                            iconw,         
                            GTK_SIGNAL_FUNC (setcurrenttool),
                            (gpointer)TEXT);
  gtk_button_set_focus_on_click   (GTK_BUTTON(text_button),TRUE);


  iconw = gtk_image_new_from_file ("icons/paintbrush.png"); 

  paintbrush_button = gtk_toolbar_append_item (GTK_TOOLBAR (toolbar), 
                            "paintbrush",            
                            "Paintbrush",
                            "Private",   
                            iconw,       
                            GTK_SIGNAL_FUNC (setcurrenttool),
                            (gpointer)BRUSH);
  gtk_button_set_focus_on_click   (GTK_BUTTON(paintbrush_button),TRUE);

  iconw = gtk_image_new_from_file ("icons/tool_spraycan.png"); 

  spraycan_button = gtk_toolbar_append_item (GTK_TOOLBAR (toolbar), 
                            "spraycan",            
                            "SprayCan",
                            "Private",   
                            iconw,       
                            GTK_SIGNAL_FUNC (setcurrenttool),
                            (gpointer)SPRAYCAN);
  gtk_button_set_focus_on_click   (GTK_BUTTON(spraycan_button),TRUE);

  iconw = gtk_image_new_from_file ("icons/pencil.png"); 

  pencil_button = gtk_toolbar_append_item (GTK_TOOLBAR (toolbar), 
                            "PenciRl",               
                            "Pencil",
                            "Private",
                            iconw,    
                            GTK_SIGNAL_FUNC (setcurrenttool),
                            (gpointer)PENCIL);

  gtk_button_set_focus_on_click   (GTK_BUTTON(pencil_button),TRUE);

 
  iconw = gtk_image_new_from_file ("icons/bucket-fill.png"); 

/*  bucketfill_button = gtk_toolbar_append_item (GTK_TOOLBAR (toolbar),
                            "Bucket fill",           
                            "Bucket fill",
                            "Private",    
                            iconw,        
                            GTK_SIGNAL_FUNC (setcurrenttool),
                            (gpointer)BUCKET);

  gtk_button_set_focus_on_click   (GTK_BUTTON(bucketfill_button),TRUE);*/


  iconw = gtk_image_new_from_file ("icons/tool_color_picker.png"); 


  colorpick_button = gtk_toolbar_append_item (GTK_TOOLBAR (toolbar),
                            "ColorPicker",            
                            "ColorPicker",
                            "Private",    
                            iconw,        
                            GTK_SIGNAL_FUNC (setcurrenttool),
                            (gpointer)COLORPICK);
  gtk_button_set_focus_on_click   (GTK_BUTTON(colorpick_button),TRUE);

  iconw = gtk_image_new_from_file ("icons/tool_polyline.png"); 

  polyline_button = gtk_toolbar_append_item (GTK_TOOLBAR (toolbar), 
                            "Polyline",              
                            "Draw polyline",
                            "Private",      
                            iconw,          
                            GTK_SIGNAL_FUNC (setcurrenttool),
                            (gpointer)POLYLINE);
  gtk_button_set_focus_on_click   (GTK_BUTTON(polyline_button),TRUE);

  iconw = gtk_image_new_from_file ("icons/tool_circle.png"); 

  ellipse_button = gtk_toolbar_append_item (GTK_TOOLBAR (toolbar), 
                            "Circle",               
                            "Draw Circle or Ellipse",
                            "Private",    
                            iconw,        
                            GTK_SIGNAL_FUNC (setcurrenttool),
                            (gpointer)ELLIPSE);
  gtk_button_set_focus_on_click   (GTK_BUTTON(ellipse_button),TRUE);

  iconw = gtk_image_new_from_file ("icons/tool_polygon.png"); 

  polygon_button = gtk_toolbar_append_item (GTK_TOOLBAR (toolbar), 
                            "Polygon",           
                            "Draws polygon",
                            "Private",      
                            iconw,          
                            GTK_SIGNAL_FUNC (setcurrenttool), 
                            (gpointer)POLYGON);
  gtk_button_set_focus_on_click   (GTK_BUTTON(polygon_button),TRUE);

  iconw = gtk_image_new_from_file ("icons/tool_rectangle.png"); 

  rectangle_button = gtk_toolbar_append_item (GTK_TOOLBAR (toolbar), 
                            "Rectangle",               
                            "Draw Rectangle",
                            "Private",       
                            iconw,           
                            GTK_SIGNAL_FUNC (setcurrenttool), 
                            (gpointer)RECTANGLE);
  gtk_button_set_focus_on_click   (GTK_BUTTON(rectangle_button),TRUE);  


  gtk_widget_show(toolbar);


  return toolbar;
}

