
#include "illuminati.h"


void color_changed_cb(GtkColorSelection *colorsel,GtkColorButton *button)
{
  GdkColor color;
  gtk_color_selection_get_current_color (colorsel, &color);
  gtk_color_button_set_color(GTK_COLOR_BUTTON(button),&color);
}
void on_color_button_press(GtkWidget *widget,GdkEventButton *event)
{

  gint response;
  GtkColorSelection *colorsel;
  GdkColor color;

    if (event->type == GDK_2BUTTON_PRESS)
    {
      if (colorseldlg == NULL)
        colorseldlg = gtk_color_selection_dialog_new ("Select background color");
      
      colorsel = GTK_COLOR_SELECTION (GTK_COLOR_SELECTION_DIALOG (colorseldlg)->colorsel);

      gtk_color_selection_set_has_palette (colorsel, TRUE);

      g_signal_connect (G_OBJECT (colorsel), "color_changed",
                        G_CALLBACK (color_changed_cb), (gpointer)widget);


      response = gtk_dialog_run (GTK_DIALOG (colorseldlg));

      if (response == GTK_RESPONSE_OK)
        gtk_color_selection_get_current_color (colorsel, &color);
      else 
         gtk_color_button_set_color(GTK_COLOR_BUTTON(widget),&color);

      gtk_widget_hide (colorseldlg);
    }
    else
    {
	gtk_color_button_get_color(GTK_COLOR_BUTTON(widget),&color);
        gdk_gc_set_rgb_fg_color(fg_gc,&color); 
        gdk_draw_rectangle (fbpixmap,fg_gc,TRUE,5,2,40,40);
        gdk_draw_drawable(fg_bg_area->window,fg_gc,fbpixmap,5,2,5,2,40,40);
     }
}
GtkWidget* get_system_color_table()
{

    
    GtkWidget *table;

    GtkWidget* color_button;

    GdkColor* color;
    
    int i,j;

    int red=0,green=0,blue=0;


    table = gtk_table_new (2, 8, TRUE);

    gtk_table_set_row_spacings( GTK_TABLE(table),1);

    gtk_table_set_col_spacings( GTK_TABLE(table),1);
  
    color=(GdkColor*)malloc(sizeof(GdkColor));

    for(i=0;i<2;i++)
     for(j=0;j<8;j++)
    {
     color->pixel=0;
     color->red=rand();
     color->green=rand();
     color->blue=rand();
     color_button=gtk_color_button_new_with_color(color);
     gtk_table_attach(GTK_TABLE (table), color_button,
                      j,j+1,i,i+1,GTK_EXPAND|GTK_FILL,GTK_EXPAND|GTK_FILL,0,0);
     gtk_widget_show(color_button);
     gtk_widget_set_events (color_button,GDK_BUTTON_PRESS_MASK);
     g_signal_connect (G_OBJECT (color_button), "button_press_event",
		      G_CALLBACK (on_color_button_press), NULL);
   }

   return table;  
  
}
