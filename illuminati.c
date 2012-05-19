#include "illuminati.h"

/*------------------------------for freehand drawing ---------------------------------*/

/* Create a new backing pixmap of the appropriate size */
gint configure_event( GtkWidget *widget,GdkEventConfigure *event )
{
  GdkColor color;
  color.pixel=0;
  color.red=65535;
  color.green=65535;
  color.blue=65535;
  gcf_pixmap = gdk_pixmap_new(NULL,640,480,24);
  gcb_pixmap = gdk_pixmap_new(NULL,640,480,24);
  fg_gc=gdk_gc_new(gcf_pixmap);
  bg_gc=gdk_gc_new(gcb_pixmap);
  gdk_gc_set_rgb_fg_color(bg_gc,&color); 
  initialise();

 
  return TRUE; /*To indicate the sucess */
}

/* Redraw the screen from the backing pixmap*/
gint expose_event( GtkWidget      *widget,
                          GdkEventExpose *event )
{


  gdk_draw_drawable (drawing_area->window,
		     fg_gc,
		     pixmap,
		     event->area.x, event->area.y,
		     event->area.x, event->area.y,
		     event->area.width, event->area.height);


  return FALSE;
}



gint button_press_event( GtkWidget      *widget,
                                GdkEventButton *event )
{
  modified=1;
  if (event->button == 1 && pixmap != NULL)
    switch(tool)
    {
    case RECT_SEL: gdk_draw_drawable(undomap,fg_gc,pixmap,0,0,0,0,-1,-1);
                   pre_x=event->x;
                   pre_y=event->y;
                   select_rectangular_region(widget,event->x,event->y,1);
                   last_x=event->x;
                   last_y=event->y; 
                  break;

    case ERASER: gdk_draw_drawable(undomap,fg_gc,pixmap,0,0,0,0,-1,-1);
                 last_x=event->x;
                 last_y=event->y;
                 eraser(widget,event->x,event->y);
                 break;

    case LINE: gdk_draw_drawable(undomap,fg_gc,pixmap,0,0,0,0,-1,-1);
               pre_x=event->x;
               pre_y=event->y;
               draw_line(widget,event->x,event->y,0);
               last_x=event->x;
               last_y=event->y;
               break;

    case TEXT: gdk_draw_drawable(undomap,fg_gc,pixmap,0,0,0,0,-1,-1);
               draw_text(widget,event->x,event->y);
               break;

    case BRUSH:gdk_draw_drawable(undomap,fg_gc,pixmap,0,0,0,0,-1,-1);
               last_x=event->x;
               last_y=event->y;
               paintbrush(widget,event->x,event->y);
               break;

    case SPRAYCAN:gdk_draw_drawable(undomap,fg_gc,pixmap,0,0,0,0,-1,-1);
               last_x=event->x;
               last_y=event->y;
               spraycan(widget,event->x,event->y);
               break;

    case PENCIL:gdk_draw_drawable(undomap,fg_gc,pixmap,0,0,0,0,-1,-1);
                last_x=event->x;
                last_y=event->y;
                draw_using_pencil(widget,event->x,event->y);
                break;

    case BUCKET: bucketfill(widget,event->x,event->y);
                 break;
  
    case COLORPICK: gdk_gc_copy(undo_gc,fg_gc);
                    undoflag=1;	
                    colorpicker(widget,event->x,event->y);
                    break;

    case POLYLINE:if(!poly)
                  {pre_x=event->x;
                   pre_y=event->y;
                   poly++;}
                  draw_polyline(widget,event->x,event->y,1);
                   break;

    case ELLIPSE:gdk_draw_drawable(undomap,fg_gc,pixmap,0,0,0,0,-1,-1);
                  pre_x=event->x;
                  pre_y=event->y; 
                 draw_arc(widget,event->x,event->y,0);
		 last_x=event->x;
                 last_y=event->y;
                 break;
   
    case POLYGON:if(!poly)
                 { 

                   pre_x=event->x;
                   pre_y=event->y;
                   last_x=event->x;
                   last_y=event->y; 
                   poly++;
                 }
                 
                 draw_polygon(widget,event->x,event->y,1);
    		 
                 break;

    case RECTANGLE:gdk_draw_drawable(undomap,fg_gc,pixmap,0,0,0,0,-1,-1);
                   pre_x=event->x;
                   pre_y=event->y;
                   draw_rectangle(widget,event->x,event->y,0);
                   last_x=event->x;
                   last_y=event->y;
                   break;
                      
   
    }
    

  return TRUE;
}

gint motion_notify_event( GtkWidget *widget,
                                 GdkEventMotion *event )
{
  int x, y;
  GdkModifierType state;

  if (event->is_hint)
    gdk_window_get_pointer (event->window, &x, &y, &state);
  else   /*To start drawing when mouse is just clicked without hint*/
    {
      x = event->x;
      y = event->y;
      state = event->state;
    }
    
  if (state & GDK_BUTTON1_MASK && pixmap != NULL)
    switch(tool)
    {
    case RECT_SEL:select_rectangular_region(widget,x,y,1);
                   last_x=x;
                   last_y=y; 
                  break;

    case ERASER: eraser(widget,x,y);
                 last_x=x;
                 last_y=y;
                 break;

    case LINE:draw_line(widget,x,y,1);
              last_x=x;
              last_y=y;
              break;
    case BRUSH:  paintbrush(widget,x,y);
                last_x=x;
                last_y=y;
                 break;

    case SPRAYCAN: spraycan(widget,x,y);
                last_x=x;
                last_y=y;
                break;

    case PENCIL:draw_using_pencil(widget,x,y);
                last_x=x;
                last_y=y;
                break;
    case BUCKET: break;
  


    case POLYLINE:draw_line(widget,x,y,1); 
                  last_x=x;
                  last_y=y;
                  break;


      
    case ELLIPSE:  draw_arc(widget,x,y,1);
                   last_x=event->x;
                   last_y=event->y; 
                   break;
   
    case POLYGON: 
                  
                  draw_polygon(widget,event->x,event->y,1);
    		  
                  break;

                 

    case RECTANGLE:draw_rectangle(widget,x,y,1);
                   last_x=x;
                   last_y=y;
                   break;
                   ;

   
    }
    

  return TRUE;
}


gint button_release_event(GtkWidget *widget,GdkEventButton *event )
{ 
  if (event->state & GDK_BUTTON1_MASK && pixmap != NULL)
    switch(tool)
    {
    case RECT_SEL: select_rectangular_region(widget,event->x,event->y,0);
                   selected++;
                   break;

    case ERASER:  eraser(widget,event->x,event->y);
                  break;

    case LINE:draw_line(widget,event->x,event->y,0);
                break; 


    case BRUSH: paintbrush(widget,event->x,event->y);
                break;

    case SPRAYCAN: spraycan(widget,event->x,event->y);
                break;

    case PENCIL:draw_using_pencil(widget,event->x,event->y);
                break;

    case BUCKET: break;
  


    case POLYLINE: draw_line(widget,event->x,event->y,0);
                   pre_x=last_x=event->x;
                   pre_y=last_y=event->y;
                    break;

    case ELLIPSE: draw_arc(widget,event->x,event->y,0);
                  break;
   
    case POLYGON:
                 draw_polygon(widget,event->x,event->y,0);
                 last_x=event->x;
                 last_y=event->y;
                 lineflag++;  
                 break;

    case RECTANGLE:draw_rectangle(widget,event->x,event->y,0);
                   break;
                   
   
    }
    return TRUE;
}
 





int main( int   argc,char *argv[] )
{
  
  GtkWidget *vbox;
  GtkWidget *hbox;

  
  GtkWidget* menubar;
  GtkWidget* main_toolbar;	
  GtkWidget* tools_toolbar;	
  
  GtkWidget* colortable;	
  GtkWidget* frame;
  
  gtk_init (&argc, &argv);
 
  modified=0;

  window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

  gtk_window_set_title (GTK_WINDOW(window), "Illuminati");
 
  g_signal_connect (G_OBJECT (window), "delete-event",
                    G_CALLBACK (delete_event), NULL);

  g_signal_connect (G_OBJECT (window), "destroy",
                    G_CALLBACK (delete_event), NULL);

  vbox = gtk_vbox_new (FALSE, 0);

  gtk_container_add(GTK_CONTAINER(window), vbox);
  

 
  /*To create the menu bar*/
  menubar = get_menubar_menu (window);

  gtk_box_pack_start (GTK_BOX(vbox),menubar, FALSE, FALSE, 0);
  gtk_widget_show (menubar);


 

  main_toolbar=get_main_toolbar();

 /* to make it nice we'll put the toolbar into the handle box, 
   * so that it can be detached from the main window */
  mainhandlebox = gtk_handle_box_new ();

  gtk_box_pack_start (GTK_BOX (vbox),mainhandlebox, FALSE, FALSE, 5);
  gtk_container_add (GTK_CONTAINER (mainhandlebox), main_toolbar);
  gtk_widget_show (main_toolbar);
  gtk_widget_show (mainhandlebox);

  

  /*hbox for tools_toolbar and drawing area*/
  hbox = gtk_hbox_new (FALSE, 2);

  gtk_box_pack_start (GTK_BOX (vbox),hbox, FALSE, FALSE, 0);

  tools_toolbar=get_tools_toolbar();
  toolhandlebox = gtk_handle_box_new ();

  gtk_box_pack_start (GTK_BOX(hbox),toolhandlebox, FALSE, FALSE, 5);
  gtk_container_add (GTK_CONTAINER (toolhandlebox), tools_toolbar);
  gtk_widget_show (tools_toolbar);
  gtk_widget_show (toolhandlebox);



  
  scrolled_win = gtk_scrolled_window_new (NULL, NULL);

  gtk_widget_set_size_request (GTK_WIDGET (scrolled_win),400,400);
  gtk_container_set_border_width (GTK_CONTAINER (scrolled_win), 1);

  gtk_scrolled_window_set_policy (GTK_SCROLLED_WINDOW (scrolled_win),
                                  GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  

  gtk_box_pack_start (GTK_BOX (hbox), scrolled_win, TRUE, TRUE, 0);



  drawing_area = gtk_drawing_area_new ();
  gtk_widget_set_size_request (GTK_WIDGET (drawing_area),800,600);

  gtk_scrolled_window_add_with_viewport (GTK_SCROLLED_WINDOW (scrolled_win),drawing_area);



  gtk_widget_show (drawing_area);


  gtk_widget_show (scrolled_win);



  gtk_widget_show (hbox);



  /* Signals used to handle backing pixmap */

  g_signal_connect (G_OBJECT (drawing_area), "expose_event",
		    G_CALLBACK (expose_event), NULL);
  g_signal_connect (G_OBJECT (drawing_area),"configure_event",
		    G_CALLBACK (configure_event), NULL);

  /* Event signals */

  g_signal_connect (G_OBJECT (drawing_area), "motion_notify_event",
		    G_CALLBACK (motion_notify_event), NULL);
  g_signal_connect (G_OBJECT (drawing_area), "button_press_event",
		    G_CALLBACK (button_press_event), NULL);
  g_signal_connect (G_OBJECT (drawing_area), "button_release_event",
                    G_CALLBACK(button_release_event),NULL);

  gtk_widget_set_events (drawing_area,GDK_EXPOSURE_MASK
			 | GDK_LEAVE_NOTIFY_MASK
                         | GDK_BUTTON_PRESS_MASK
			 | GDK_POINTER_MOTION_MASK
			 | GDK_POINTER_MOTION_HINT_MASK
                         | GDK_BUTTON_RELEASE_MASK);

   hbox = gtk_hbox_new (FALSE,0);

   gtk_box_pack_start(GTK_BOX (vbox),hbox, FALSE, FALSE, 2);
   

   frame=get_fgbgframe();
   

   gtk_box_pack_start(GTK_BOX (hbox),frame, FALSE, FALSE, 2);

   gtk_widget_show(frame);

   colortable=get_system_color_table();
  
   frame=gtk_frame_new("select color");

   gtk_widget_set_size_request (GTK_WIDGET (frame),400,75);

   gtk_box_pack_start(GTK_BOX (hbox),frame, TRUE, TRUE, 2);
  
   gtk_container_add(GTK_CONTAINER(frame),colortable); 


   gtk_widget_show (colortable); 

   gtk_widget_show(frame);

   gtk_widget_show (hbox);


   gtk_widget_show(vbox);

   gtk_widget_show(window);

  /*Initial tool set to PENCIL */
 
  display=gdk_display_get_default();              
 
  cursor=gdk_cursor_new(GDK_PENCIL);

  gdk_window_set_cursor(drawing_area->window,cursor);

  tool=PENCIL;

  gtk_button_set_relief(GTK_BUTTON(pencil_button),GTK_RELIEF_NORMAL);

  filename=g_strdup("Untitled.jpeg");	

  pixmap = gdk_pixmap_new (drawing_area->window,
			   drawing_area->allocation.width,
			   drawing_area->allocation.height,
			   -1);
  gdk_draw_rectangle (pixmap,
		      drawing_area->style->white_gc,
		      TRUE,
		      0, 0,
		      drawing_area->allocation.width,
		      drawing_area->allocation.height);


  gtk_main ();

  return 0;
}
