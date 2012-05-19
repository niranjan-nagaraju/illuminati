#include "illuminati.h"

gint fbconfigure_event( GtkWidget *widget,GdkEventConfigure *event )
{

   fbpixmap = gdk_pixmap_new (widget->window,
			     widget->allocation.width,
			     widget->allocation.height,
			     -1);
   gdk_draw_rectangle (fbpixmap,
		       widget->style->bg_gc[GTK_WIDGET_STATE (fg_bg_area)],
		       TRUE,
		       0, 0,
		       widget->allocation.width,
		       widget->allocation.height);
   
   gdk_draw_rectangle (fbpixmap,
	              widget->style->white_gc,
		      TRUE,
		      20,12,
		      40,
		      40);
   gdk_draw_drawable(widget->window,widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
                                              fbpixmap,20,12,20,12,
                                              40,40);

   gdk_draw_rectangle (fbpixmap,
	              widget->style->black_gc,
		      TRUE,
		      5,2,
		      40,
		      40);
   gdk_draw_drawable(widget->window,widget->style->fg_gc[GTK_WIDGET_STATE (widget)],
                                              fbpixmap,5,2,5,2,
                                              40,40);


  return TRUE; /*To indicate the sucess */
}


gint fbexpose_event( GtkWidget      *widget,
                          GdkEventExpose *event )
{
  gdk_draw_drawable (fg_bg_area->window,
		     fg_gc,
		     fbpixmap,
		     event->area.x, event->area.y,
		     event->area.x, event->area.y,
		     event->area.width, event->area.height);

  return FALSE;
}

void set_bg_color( GtkWidget  *widget,GdkEventButton *event )
{
  gint response;
  GtkColorSelection *colorsel;
  GdkColor color;
  GtkWidget *bgcolorseldlg=NULL;
    if (event->type == GDK_BUTTON_PRESS)
      if(event->x >45 && event->y > 42 && event->x <=60 && event->y <=52 )
      {
      if (bgcolorseldlg == NULL)
        bgcolorseldlg = gtk_color_selection_dialog_new ("Select background color");
      
      colorsel = GTK_COLOR_SELECTION (GTK_COLOR_SELECTION_DIALOG (bgcolorseldlg)->colorsel);

      gtk_color_selection_set_has_palette (colorsel, TRUE);

      response = gtk_dialog_run (GTK_DIALOG (bgcolorseldlg));

      if (response == GTK_RESPONSE_OK)
      {
        gtk_color_selection_get_current_color (colorsel, &color);
        gtk_widget_hide (bgcolorseldlg);
        gdk_gc_set_rgb_fg_color(bg_gc,&color); 
        gdk_draw_rectangle (fbpixmap,bg_gc,TRUE,20,12,40,40);
        gdk_draw_drawable(widget->window,bg_gc,fbpixmap,20,12,20,12,40,40);
        gdk_draw_rectangle (fbpixmap,fg_gc,TRUE,5,2,40,40);
        gdk_draw_drawable(widget->window,fg_gc,fbpixmap,5,2,5,2,40,40);
      }
      else if(response == GTK_RESPONSE_CANCEL)
         gtk_widget_hide (bgcolorseldlg);
    }
}

GtkWidget* get_fgbgframe( )
{
   GtkWidget *frame;

   frame=gtk_frame_new("");

   gtk_widget_set_size_request (GTK_WIDGET (frame),70,40);

   fg_bg_area=gtk_drawing_area_new();
   
   gtk_container_add(GTK_CONTAINER(frame),fg_bg_area);


  
   gtk_widget_show(fg_bg_area);


   gtk_widget_set_events (fg_bg_area,GDK_EXPOSURE_MASK|GDK_BUTTON_PRESS_MASK);
  
   g_signal_connect (G_OBJECT (fg_bg_area), "expose_event",
		    G_CALLBACK (fbexpose_event), NULL);
   g_signal_connect (G_OBJECT (fg_bg_area),"configure_event",
		    G_CALLBACK (fbconfigure_event), NULL);
   g_signal_connect (G_OBJECT (fg_bg_area), "button_press_event",
		    G_CALLBACK (set_bg_color), NULL);

    return frame;

}
