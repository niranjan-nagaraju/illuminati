#include "illuminati.h"


GtkWidget *colorframe;



gint colorframe_configure_event( GtkWidget *widget,GdkEventConfigure *event )
{
  
  GdkColor *color;
  GdkGC *old_gc=gdk_gc_new(widget->window);
  GdkGC *fb_gc;
  
  color_palette_pixmap = gdk_pixmap_new (widget->window,
			     widget->allocation.width,
			     widget->allocation.height,
			     -1);
  gdk_draw_rectangle (color_palette_pixmap,
		       widget->style->fg_gc[GTK_WIDGET_STATE (color_palette_area)],
		       TRUE,
		       0, 0,
		       widget->allocation.width,
		       widget->allocation.height);

  color=(GdkColor*)malloc(sizeof(GdkColor));
   
    /*white*/
    color->pixel=0;
    color->red=65535;
    color->green=65535;
    color->blue=65535;
  
    color_palette_area->style->fg[0]=*color;
    gdk_gc_set_rgb_fg_color(color_palette_area->style->fg_gc[0],color);

   
   gdk_draw_rectangle(color_palette_pixmap,
	              color_palette_area->style->fg_gc[GTK_WIDGET_STATE(color_palette_area)],
		      TRUE,
		      0,0,
		      40,
		      40);
   gdk_draw_drawable(color_palette_area->window,
                     color_palette_area->style->fg_gc[GTK_WIDGET_STATE(color_palette_area)],
                                              color_palette_pixmap,0,0,0,0,
                                              40,40);







    color->pixel=0;
    color->red=22;
    color->green=26454;
    color->blue=81;

   color_palette_area->style->fg[0]=*color;
   gdk_gc_set_rgb_fg_color(color_palette_area->style->fg_gc[0],color);
   
   gdk_draw_rectangle (color_palette_pixmap,
	              color_palette_area->style->fg_gc[GTK_WIDGET_STATE(color_palette_area)],
		      TRUE,
		      0,40,
		      40,
		      40);
   gdk_draw_drawable(color_palette_area->window,
                    color_palette_area->style->fg_gc[GTK_WIDGET_STATE(color_palette_area)],
                                              color_palette_pixmap,0,40,0,40,
                                             40,40);
  
    /*red*/
    color->pixel=0;
    color->red=65535;
    color->green=0;
    color->blue=0;
    
    color_palette_area->style->fg[0]=*color;
    gdk_gc_set_rgb_fg_color(color_palette_area->style->fg_gc[0],color);

   
    gdk_draw_rectangle(color_palette_pixmap,
	              color_palette_area->style->fg_gc[GTK_WIDGET_STATE(color_palette_area)],
		      TRUE,
		      40,0,
		      40,
		      40);
   gdk_draw_drawable(color_palette_area->window,
                     color_palette_area->style->fg_gc[GTK_WIDGET_STATE(color_palette_area)],
                                              color_palette_pixmap,40,0,40,0,
                                              40,40);

 /*green*/
    color->pixel=0;
    color->red=0;
    color->green=65535;
    color->blue=0;

    color_palette_area->style->fg[0]=*color;
    gdk_gc_set_rgb_fg_color(color_palette_area->style->fg_gc[0],color);

   
   gdk_draw_rectangle(color_palette_pixmap,
	              color_palette_area->style->fg_gc[GTK_WIDGET_STATE(color_palette_area)],
		      TRUE,
		      40,40,
		      40,
		      40);
   gdk_draw_drawable(color_palette_area->window,
                     color_palette_area->style->fg_gc[GTK_WIDGET_STATE(color_palette_area)],
                                              color_palette_pixmap,40,40,40,40,
                                              40,40);

  /*blue*/
    color->pixel=0;
    color->red=0;
    color->green=0;
    color->blue=65535;

    color_palette_area->style->fg[0]=*color;
    gdk_gc_set_rgb_fg_color(color_palette_area->style->fg_gc[0],color);

   
   gdk_draw_rectangle(color_palette_pixmap,
	              color_palette_area->style->fg_gc[GTK_WIDGET_STATE(color_palette_area)],
		      TRUE,
		      80,0,
		      40,
		      40);
   gdk_draw_drawable(color_palette_area->window,
                     color_palette_area->style->fg_gc[GTK_WIDGET_STATE(color_palette_area)],
                                              color_palette_pixmap,80,0,80,0,
                                              40,40);


    color->pixel=0;
    color->red=4000;
    color->green=60000;
    color->blue=200;

    color_palette_area->style->fg[0]=*color;
    gdk_gc_set_rgb_fg_color(color_palette_area->style->fg_gc[0],color);

   
   gdk_draw_rectangle(color_palette_pixmap,
	              color_palette_area->style->fg_gc[GTK_WIDGET_STATE(color_palette_area)],
		      TRUE,
		      80,40,
		      40,
		      40);
   gdk_draw_drawable(color_palette_area->window,
                     color_palette_area->style->fg_gc[GTK_WIDGET_STATE(color_palette_area)],
                                              color_palette_pixmap,80,40,80,40,
                                              40,40);



    color->pixel=0;
    color->red=40000;
    color->green=20000;
    color->blue=1000;

   color_palette_area->style->fg[0]=*color;
    gdk_gc_set_rgb_fg_color(color_palette_area->style->fg_gc[0],color);

   
   gdk_draw_rectangle(color_palette_pixmap,
	              color_palette_area->style->fg_gc[GTK_WIDGET_STATE(color_palette_area)],
		      TRUE,
		      120,0,
		      40,
		      40);
   gdk_draw_drawable(color_palette_area->window,
                     color_palette_area->style->fg_gc[GTK_WIDGET_STATE(color_palette_area)],
                                              color_palette_pixmap,120,0,120,0,
                                              40,40);


    color->pixel=456;
    color->red=23456;
    color->green=53686;
    color->blue=23;

  color_palette_area->style->fg[0]=*color;
    gdk_gc_set_rgb_fg_color(color_palette_area->style->fg_gc[0],color);

   
   gdk_draw_rectangle(color_palette_pixmap,
	              color_palette_area->style->fg_gc[GTK_WIDGET_STATE(color_palette_area)],
		      TRUE,
		      120,40,
		      40,
		      40);
   gdk_draw_drawable(color_palette_area->window,
                     color_palette_area->style->fg_gc[GTK_WIDGET_STATE(color_palette_area)],
                                              color_palette_pixmap,120,40,120,40,
                                              40,40);


    color->pixel=1056;
    color->red=900;
    color->green=2400;
    color->blue=4567;

    color_palette_area->style->fg[0]=*color;
    gdk_gc_set_rgb_fg_color(color_palette_area->style->fg_gc[0],color);

   
   gdk_draw_rectangle(color_palette_pixmap,
	              color_palette_area->style->fg_gc[GTK_WIDGET_STATE(color_palette_area)],
		      TRUE,
		      160,0,
		      40,
		      40);
   gdk_draw_drawable(color_palette_area->window,
                     color_palette_area->style->fg_gc[GTK_WIDGET_STATE(color_palette_area)],
                                              color_palette_pixmap,160,0,160,0,
                                              40,40);


    color->pixel=1478;
    color->red=19999;
    color->green=2366;
    color->blue=56000;

  color_palette_area->style->fg[0]=*color;
    gdk_gc_set_rgb_fg_color(color_palette_area->style->fg_gc[0],color);

   
   gdk_draw_rectangle(color_palette_pixmap,
	              color_palette_area->style->fg_gc[GTK_WIDGET_STATE(color_palette_area)],
		      TRUE,
		      160,40,
		      40,
		      40);
   gdk_draw_drawable(color_palette_area->window,
                     color_palette_area->style->fg_gc[GTK_WIDGET_STATE(color_palette_area)],
                                              color_palette_pixmap,160,40,160,40,
                                              40,40);


    color->pixel=10078;
    color->red=78;
    color->green=26789;
    color->blue=456;

    color_palette_area->style->fg[0]=*color;
    gdk_gc_set_rgb_fg_color(color_palette_area->style->fg_gc[0],color);

   
   gdk_draw_rectangle(color_palette_pixmap,
	              color_palette_area->style->fg_gc[GTK_WIDGET_STATE(color_palette_area)],
		      TRUE,
		      200,0,
		      40,
		      40);
   gdk_draw_drawable(color_palette_area->window,
                     color_palette_area->style->fg_gc[GTK_WIDGET_STATE(color_palette_area)],
                                              color_palette_pixmap,200,0,200,0,
                                              40,40);


    color->pixel=0;
    color->red=5078;
    color->green=6783;
    color->blue=20090;

  color_palette_area->style->fg[0]=*color;
    gdk_gc_set_rgb_fg_color(color_palette_area->style->fg_gc[0],color);

   
   gdk_draw_rectangle(color_palette_pixmap,
	              color_palette_area->style->fg_gc[GTK_WIDGET_STATE(color_palette_area)],
		      TRUE,
		      200,40,
		      40,
		      40);
   gdk_draw_drawable(color_palette_area->window,
                     color_palette_area->style->fg_gc[GTK_WIDGET_STATE(color_palette_area)],
                                              color_palette_pixmap,200,40,200,40,
                                              40,40);



    color->pixel=34512;
    color->red=30427;
    color->green=48723;
    color->blue=1000;

  color_palette_area->style->fg[0]=*color;
    gdk_gc_set_rgb_fg_color(color_palette_area->style->fg_gc[0],color);

   
   gdk_draw_rectangle(color_palette_pixmap,
	              color_palette_area->style->fg_gc[GTK_WIDGET_STATE(color_palette_area)],
		      TRUE,
		      240,0,
		      40,
		      40);
   gdk_draw_drawable(color_palette_area->window,
                     color_palette_area->style->fg_gc[GTK_WIDGET_STATE(color_palette_area)],
                                              color_palette_pixmap,240,0,240,0,
                                              40,40);


    color->pixel=45211;
    color->red=3455;
    color->green=0;
    color->blue=24312;

   color_palette_area->style->fg[0]=*color;
    gdk_gc_set_rgb_fg_color(color_palette_area->style->fg_gc[0],color);

   
   gdk_draw_rectangle(color_palette_pixmap,
	              color_palette_area->style->fg_gc[GTK_WIDGET_STATE(color_palette_area)],
		      TRUE,
		      240,40,
		      40,
		      40);
   gdk_draw_drawable(color_palette_area->window,
                     color_palette_area->style->fg_gc[GTK_WIDGET_STATE(color_palette_area)],
                                              color_palette_pixmap,240,40,240,40,
                                              40,40);


    color->pixel=4322;
    color->red=36055;
    color->green=560;
    color->blue=1542;

  color_palette_area->style->fg[0]=*color;
    gdk_gc_set_rgb_fg_color(color_palette_area->style->fg_gc[0],color);

   
   gdk_draw_rectangle(color_palette_pixmap,
	              color_palette_area->style->fg_gc[GTK_WIDGET_STATE(color_palette_area)],
		      TRUE,
		      280,0,
		      40,
		      40);
   gdk_draw_drawable(color_palette_area->window,
                     color_palette_area->style->fg_gc[GTK_WIDGET_STATE(color_palette_area)],
                                              color_palette_pixmap,280,0,280,0,
                                              40,40);


    color->pixel=0;
    color->red=0;
    color->green=0;
    color->blue=0;

  color_palette_area->style->fg[0]=*color;
    gdk_gc_set_rgb_fg_color(color_palette_area->style->fg_gc[0],color);

   
   gdk_draw_rectangle(color_palette_pixmap,
	              color_palette_area->style->fg_gc[GTK_WIDGET_STATE(color_palette_area)],
		      TRUE,
		      280,40,
		      40,
		      40);
   gdk_draw_drawable(color_palette_area->window,
                     color_palette_area->style->fg_gc[GTK_WIDGET_STATE(color_palette_area)],
                                              color_palette_pixmap,280,40,280,40,
                                              40,40);



   color_palette_area->style->fg_gc[GTK_WIDGET_STATE(color_palette_area)]=old_gc;
   return TRUE;	/*To indicate the sucess */
}

gint colorframe_expose_event( GtkWidget      *widget,
                          GdkEventExpose *event )
{
  gdk_draw_drawable (widget->window,
		     widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
		     color_palette_pixmap,
		     event->area.x, event->area.y,
		     event->area.x, event->area.y,
		     event->area.width, event->area.height);

  return FALSE;
}





GtkWidget* get_colorframe( )
{
   
   colorframe=gtk_frame_new("");

   gtk_widget_set_size_request (GTK_WIDGET (colorframe),320,100);

   color_palette_area=gtk_drawing_area_new();
   gtk_container_add(GTK_CONTAINER(colorframe),color_palette_area);

     
   gtk_widget_show(color_palette_area);


   gtk_widget_set_events (color_palette_area,GDK_EXPOSURE_MASK
			 | GDK_LEAVE_NOTIFY_MASK
                         | GDK_BUTTON_PRESS_MASK
                         | GDK_BUTTON_RELEASE_MASK);
  
   g_signal_connect (G_OBJECT (color_palette_area), "expose_event",
		    G_CALLBACK (colorframe_expose_event), NULL);
   g_signal_connect (G_OBJECT (color_palette_area),"configure_event",
		    G_CALLBACK (colorframe_configure_event), NULL);

   
   return colorframe;

}

