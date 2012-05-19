#include "illuminati.h"

void select_rectangular_region( GtkWidget *widget,gdouble x,gdouble y,gint flag)
{
   GdkGCValues values;

   gdk_gc_get_values(fg_gc,&values);
   gdk_gc_set_line_attributes(fg_gc,values.line_width,GDK_LINE_ON_OFF_DASH,
                                      values.cap_style,
                                      values.join_style);


if(!selected)
{
 if(!flag)
 {
  
  sel_rect.width=fabs(x-pre_x);
  sel_rect.height=fabs(y-pre_y);
  if(pre_x < x && pre_y < y) {
     sel_rect.x=pre_x;
     sel_rect.y=pre_y; }
  else if(pre_x < x && pre_y > y )  {
     sel_rect.x=pre_x;
     sel_rect.y=y;}
  else if(pre_x > x && pre_y < y){
     sel_rect.x=x;
     sel_rect.y=pre_y;}
  else{
     sel_rect.x=x;
     sel_rect.y=y;}
  }
  gdk_draw_drawable(widget->window,fg_gc,pixmap,0,0,0,0,
                    widget->allocation.width,widget->allocation.height);
  if(pre_x < x && pre_y < y)
  {
   gdk_draw_rectangle (widget->window,
	              fg_gc,
		      FALSE,
		      pre_x, pre_y,
		      fabs(x-pre_x),
		      fabs(y-pre_y));
  }
  else if(pre_x < x && pre_y > y )
  {

   gdk_draw_rectangle (widget->window,
	              fg_gc,
		      FALSE,
		      pre_x,y,
		      fabs(x-pre_x),
		      fabs(y-pre_y));
 }
  else if(pre_x > x && pre_y < y)
  {
      gdk_draw_rectangle (widget->window,
	              fg_gc,
		      FALSE,
		      x, pre_y,
		      fabs(x-pre_x),
		      fabs(y-pre_y));
 
 }
  else
  {
      gdk_draw_rectangle (widget->window,
	             fg_gc,
		      FALSE,
		      x, y,
		      fabs(x-pre_x),
		      fabs(y-pre_y));
  }
}
else
    gdk_draw_drawable(widget->window,fg_gc,pixmap,0,0,0,0,
                    widget->allocation.width,widget->allocation.height);


gdk_gc_set_line_attributes(fg_gc,values.line_width,values.line_style,
                                      values.cap_style,
                                      values.join_style);
}



void eraser(GtkWidget *widget,gdouble x,gdouble y)
{
   GdkGCValues values;
   gdk_gc_get_values(fg_gc,&values);
   gdk_gc_set_line_attributes(bg_gc,7,values.line_style,
                                      values.cap_style,
                                      values.join_style);

   gdk_draw_line(pixmap,bg_gc,last_x,last_y,x,y);
   gdk_draw_line(widget->window,bg_gc,last_x,last_y,x,y);
   gdk_gc_set_line_attributes(bg_gc,1,values.line_style,
                                      values.cap_style,
                                      values.join_style);

}

void hide_dialog(GtkWidget *w,GtkDialog *dialog)
{
   gtk_widget_hide(GTK_WIDGET(dialog));
}
void draw_text( GtkWidget *w,gdouble  x,gdouble y )
{
  GtkWidget *fontseldlg;
  GtkFontSelection *fontsel;
  GdkFont* font;
  GtkWidget *dialog;
  GtkWidget *label;
  GtkWidget *entry;
  GtkWidget *hbox;
  GtkWidget *button;
  const gchar *text;
  gchar *fontname;
  gint text_len;
  gint response;
  PangoLayout *layout;
  PangoFontDescription *fontdesc;

  
      fontseldlg=gtk_font_selection_dialog_new("Pick the font for text");
      
      fontsel = GTK_FONT_SELECTION (GTK_FONT_SELECTION_DIALOG (fontseldlg)->fontsel);

      response = gtk_dialog_run (GTK_DIALOG (fontseldlg));

      if (response == GTK_RESPONSE_OK)
      {
        font=gtk_font_selection_get_font(GTK_FONT_SELECTION(fontsel));
        fontname=gtk_font_selection_get_font_name(GTK_FONT_SELECTION(fontsel));
        gtk_widget_hide (fontseldlg);
        gdk_gc_set_font(fg_gc,font);
        dialog=gtk_dialog_new();
        gtk_widget_set_name (dialog, "Please enter text here");
        label=gtk_label_new("Please enter the text here\n");    
        entry = gtk_entry_new ();
        gtk_box_pack_start (GTK_BOX (GTK_DIALOG(dialog)->vbox), label, TRUE, TRUE, 0); 
        gtk_widget_show(label) ;

        gtk_box_pack_start (GTK_BOX (GTK_DIALOG(dialog)->vbox), entry, TRUE, TRUE, 0); 
        gtk_widget_show(entry) ;
        
        gtk_dialog_set_has_separator(GTK_DIALOG(dialog),TRUE);

        hbox=gtk_hbox_new(TRUE,4);
        gtk_box_pack_start (GTK_BOX (GTK_DIALOG(dialog)->vbox), hbox, TRUE, TRUE, 0); 

        button=gtk_button_new_from_stock(GTK_STOCK_OK) ;
        gtk_box_pack_start (GTK_BOX (hbox), button, TRUE, TRUE, 0); 
        gtk_widget_show(button) ;

        gtk_widget_show(hbox) ;

        g_signal_connect(G_OBJECT (button), "clicked",
		      G_CALLBACK (hide_dialog),(gpointer)dialog);

        gtk_widget_show(dialog) ;
        gtk_entry_set_max_length (GTK_ENTRY (entry), 50);
        gtk_dialog_run (GTK_DIALOG (dialog));
        g_signal_connect(G_OBJECT (entry), "activate",
		      G_CALLBACK (hide_dialog),(gpointer)dialog);
        text = gtk_entry_get_text (GTK_ENTRY (entry));
        text_len=GTK_ENTRY (entry)->text_length;
        
        layout = gtk_widget_create_pango_layout (w, text);
        fontdesc = pango_font_description_from_string (fontname);
        pango_layout_set_font_description (layout, fontdesc); 
        gdk_draw_layout (w->window,fg_gc,x,y,layout);
        gdk_draw_layout(pixmap,fg_gc,x,y,layout);
        pango_font_description_free (fontdesc);
        g_object_unref (layout);

      }
  

}
void draw_line( GtkWidget *widget,gdouble x,gdouble y,gint flag)
{
 if(!flag)
  gdk_draw_line(pixmap,fg_gc,pre_x,pre_y,x,y);
 gdk_draw_drawable (widget->window,fg_gc,pixmap,0,0,0,0,widget->allocation.width,
                                                       widget->allocation.height);
  gdk_draw_line(widget->window,fg_gc,pre_x,pre_y,x,y);
 
}
void paintbrush( GtkWidget *w,gdouble x,gdouble y )
{
   GdkGCValues values;
   gdk_gc_get_values(fg_gc,&values);
   gdk_gc_set_line_attributes(fg_gc,3,values.line_style,
                                      values.cap_style,
                                      values.join_style);
   gdk_draw_line (pixmap,fg_gc,last_x,last_y,x,y);
   gdk_draw_line (w->window,fg_gc,last_x,last_y,x,y);
   gdk_gc_set_line_attributes(fg_gc,1,values.line_style,
                                      values.cap_style,
                                      values.join_style);
}
void spraycan( GtkWidget *w,gdouble x,gdouble y )
{

   GdkPixmap *xmap;
   GdkBitmap *bitmap;
   const gchar data[16]={1,0,1,0,1,0,1,0,1,0,1,0,1,0,1,0};

   xmap = gdk_pixmap_new( NULL,4,4,24);
   bitmap=gdk_bitmap_create_from_data(xmap,data,4,4);
          
   gdk_gc_set_fill(fg_gc,GDK_STIPPLED);

   gdk_gc_set_stipple(fg_gc,bitmap);
                                    
   gdk_draw_rectangle(pixmap,fg_gc,TRUE,x,y,4,4);
   gdk_draw_rectangle(w->window,fg_gc,TRUE,x,y,4,4);

   gdk_gc_set_fill(fg_gc,GDK_SOLID);

}

void draw_using_pencil(GtkWidget *widget,gdouble x,gdouble y)
{
  gdk_draw_line(pixmap,fg_gc,last_x,last_y,x,y);
  gdk_draw_line(widget->window,fg_gc,last_x,last_y,x,y);
  
}

typedef struct pt
{
    gint x;
    gint y;
    struct pt* next;
}Point;

void insert (int x, int y, Point** last)
{
    Point* p;

    p = (Point *) malloc (sizeof (Point));
    if (p == NULL) {
        fprintf (stderr, "\ninsert: Out of memory.\n");
        exit (2);
    }
    p->x = x;
    p->y = y;
    p->next = NULL;
    (*last)->next = p;
    *last = (*last)->next;
}

void put_pixel (GdkPixbuf *pixbuf, int x, int y,GdkColor color)
{
  int width, height, rowstride, n_channels;
  guchar *pixels, *p;

  n_channels = gdk_pixbuf_get_n_channels (pixbuf);

  g_assert (gdk_pixbuf_get_colorspace (pixbuf) == GDK_COLORSPACE_RGB);
  g_assert (gdk_pixbuf_get_bits_per_sample (pixbuf) == 8);
  g_assert (n_channels == 3);

  width = gdk_pixbuf_get_width (pixbuf);
  height = gdk_pixbuf_get_height (pixbuf);

  g_assert (x >= 0 && x < width);
  g_assert (y >= 0 && y < height);

  rowstride = gdk_pixbuf_get_rowstride (pixbuf);
  pixels = gdk_pixbuf_get_pixels (pixbuf);

  p = pixels + y * rowstride + x * n_channels;
  p[0] = color.red;
  p[1] = color.green;
  p[2] = color.blue;
}
guint32 pixel_from_rgb(GdkColor color)
{
  guchar r,b,g;

  r = color.red;
  g = color.green;
  b = color.blue;

 return ((r >> (16 - visual->red_prec))   << visual->red_shift) |
         ((g >> (16 - visual->green_prec)) << visual->green_shift) |
         ((r >> (16 - visual->blue_prec))  << visual->blue_shift);
}

guint32 get_pixel (GdkPixbuf *pixbuf, int x, int y)
{
  int width, height, rowstride, n_channels;
  guchar r,b,g;
  guchar *pixels, *p;

  n_channels = gdk_pixbuf_get_n_channels (pixbuf);

  g_assert (gdk_pixbuf_get_colorspace (pixbuf) == GDK_COLORSPACE_RGB);
  g_assert (gdk_pixbuf_get_bits_per_sample (pixbuf) == 8);
  g_assert (n_channels == 3);

  width = gdk_pixbuf_get_width (pixbuf);
  height = gdk_pixbuf_get_height (pixbuf);

  g_assert (x >= 0 && x < width);
  g_assert (y >= 0 && y < height);

  rowstride = gdk_pixbuf_get_rowstride (pixbuf);
  pixels = gdk_pixbuf_get_pixels (pixbuf);

  p = pixels + y * rowstride + x * n_channels;
  r = p[0];
  g = p[1];
  b = p[2];
  return ((r >> (16 - visual->red_prec))   << visual->red_shift) |
         ((g >> (16 - visual->green_prec)) << visual->green_shift) |
         ((r >> (16 - visual->blue_prec))  << visual->blue_shift);

}
      
void bucketfill (GtkWidget* widget,gint x, gint y)
{
    Point* first, *last, *tmp;
    GdkGCValues fvalues,bvalues;
    GdkImage *image;
    GdkPixbuf *xbuf;
    GdkPoint points[600+800];
    int i=0;
    int init_x=x,init_y=y;
    visual=gdk_visual_get_best();   

    xbuf=gdk_pixbuf_get_from_drawable(NULL,pixmap,
                               gdk_drawable_get_colormap(pixmap),
                               0,0,
                               0,0,   
                              -1,-1);

  

                                     
    first = (Point *) malloc (sizeof (Point));
    if (first == NULL) {
        fprintf (stderr, "bucketfill: Out of memory.\n");
        exit (2);
    }
  
    first->x = x;
    first->y = y;
    first->next = NULL;
    last = first;

  
    while (first != NULL) {
            x = first->x;
            y = first->y;
  

        
        if(x<600 && y <800) 
        {

           if (get_pixel(xbuf,x,y-1)== pixel_from_rgb(bvalues.foreground) && i%2 ==0 ) 
            insert (x, y-1, &last);     /* Insert at the end. */
           else{ 
             points[i].x=x;
             points[i].y=y-1;
	     i++; }	

           if (get_pixel(xbuf,x,y+1)== pixel_from_rgb(bvalues.foreground) && i%2 ==1)
             insert (x, y+1, &last);
           else{ 
             points[i].x=x;
             points[i].y=y+1;
	     i++; }	


          if (get_pixel(xbuf,x-1,y)== pixel_from_rgb(bvalues.foreground) && i%2 ==0) 
            insert (x-1, y, &last);
           else{ 
             points[i].x=x-1;
             points[i].y=y;
	     i++; }	

          if (get_pixel(xbuf,x+1,y)==pixel_from_rgb(bvalues.foreground) && i%2 ==1) 
            insert (x+1, y, &last);
           else{ 
             points[i].x=x+1;
             points[i].y=y;
	     i++; }	

        }
        else
              break;

        /* This pixel is done. Try the next node in the list. */
        tmp = first;
        first = first->next;
        
        free (tmp);
    }
    
    gdk_draw_polygon(widget->window,fg_gc,TRUE,points,i+1);
   
    gdk_draw_drawable( pixmap,
                      fg_gc,
             	      widget->window,
		      0,0,
		      0,0,
		      widget->allocation.width,widget->allocation.height);
}

void colorpicker( GtkWidget *w,gdouble x,gdouble y)
{

 GdkColor color;
 GdkImage* image;

 image=gdk_image_get(w->window,0,0,w->allocation.width,w->allocation.height);
 color.pixel=gdk_image_get_pixel(image,x,y);

 gdk_gc_set_foreground(fg_gc,&color); 

 gdk_draw_rectangle (fbpixmap,fg_gc,TRUE,5,2,40,40);
 gdk_draw_drawable(fg_bg_area->window,fg_gc,fbpixmap,5,2,5,2,40,40);
 
}

      
void draw_polyline( GtkWidget *widget,gdouble x,gdouble y,gint flag)
{
	
 if(!flag)
   gdk_draw_line(pixmap,fg_gc,pre_x,pre_y,x,y);
 gdk_draw_drawable (widget->window,fg_gc,pixmap,0,0,0,0,widget->allocation.width,
                                                       widget->allocation.height);
 gdk_draw_line(widget->window,fg_gc,pre_x,pre_y,x,y);
 

}

void draw_arc( GtkWidget *widget,gdouble x,gdouble y,gint flag)
{
if(!flag)
{
  if(pre_x < x && pre_y < y) {
   gdk_draw_arc (pixmap,
	              fg_gc,
		      FALSE,
		      pre_x, pre_y,
		      fabs(x-pre_x),
		      fabs(y-pre_y),0,360*64); }
  else if(pre_x < x && pre_y > y )  {
   gdk_draw_arc (pixmap,
	              fg_gc,
		      FALSE,
		      pre_x,y,
		      fabs(x-pre_x),
		      fabs(y-pre_y),0,360*64);}
  else if(pre_x > x && pre_y < y){
      gdk_draw_arc (pixmap,
	              fg_gc,
		      FALSE,
		      x, pre_y,
		      fabs(x-pre_x),
		      fabs(y-pre_y),0,360*64);}
  else{
      gdk_draw_arc (pixmap,
	             fg_gc,
		      FALSE,
		      x, y,
		      fabs(x-pre_x),
		      fabs(y-pre_y),0,360*64);}
}
gdk_draw_drawable(widget->window,fg_gc,pixmap,0,0,0,0,
                    widget->allocation.width,widget->allocation.height);

  if(pre_x < x && pre_y < y)
  {
   gdk_draw_arc (widget->window,
	              fg_gc,
		      FALSE,
		      pre_x, pre_y,
		      fabs(x-pre_x),
		      fabs(y-pre_y),0,360*64);
  }
  else if(pre_x < x && pre_y > y )
  {

   gdk_draw_arc (widget->window,
	              fg_gc,
		      FALSE,
		      pre_x,y,
		      fabs(x-pre_x),
		      fabs(y-pre_y),0,360*64);
 }
  else if(pre_x > x && pre_y < y)
  {
      gdk_draw_arc (widget->window,
	              fg_gc,
		      FALSE,
		      x, pre_y,
		      fabs(x-pre_x),
		      fabs(y-pre_y),0,360*64);
 
 }
  else
  {
      gdk_draw_arc (widget->window,
	             fg_gc,
		      FALSE,
		      x, y,
		      fabs(x-pre_x),
		      fabs(y-pre_y),0,360*64);
  }
  
}

void draw_polygon( GtkWidget *widget,gdouble  x,gdouble y,gint flag )
{

  if(!flag)
  {
   gdk_draw_line(pixmap,fg_gc,pre_x,pre_y,x,y);
   gdk_draw_line(pixmap,fg_gc,last_x,last_y,x,y);

  }
  
if(lineflag != 1)
 gdk_draw_line(pixmap,widget->style->white_gc,pre_x,pre_y,last_x,last_y);
 gdk_draw_drawable (widget->window,fg_gc,pixmap,0,0,0,0,widget->allocation.width,
                                                       widget->allocation.height);
 
 gdk_draw_line(widget->window,fg_gc,pre_x,pre_y,x,y);
 gdk_draw_line(widget->window,fg_gc,last_x,last_y,x,y);


}

void draw_rectangle( GtkWidget *widget,gdouble  x,gdouble y,gint flag )
{
if(!flag)
{
  if(pre_x < x && pre_y < y) {
   gdk_draw_rectangle (pixmap,
	              fg_gc,
		      FALSE,
		      pre_x, pre_y,
		      fabs(x-pre_x),
		      fabs(y-pre_y)); }
  else if(pre_x < x && pre_y > y )  {
   gdk_draw_rectangle (pixmap,
	              fg_gc,
		      FALSE,
		      pre_x,y,
		      fabs(x-pre_x),
		      fabs(y-pre_y));}
  else if(pre_x > x && pre_y < y){
      gdk_draw_rectangle (pixmap,
	              fg_gc,
		      FALSE,
		      x, pre_y,
		      fabs(x-pre_x),
		      fabs(y-pre_y));}
  else{
      gdk_draw_rectangle (pixmap,
	             fg_gc,
		      FALSE,
		      x, y,
		      fabs(x-pre_x),
		      fabs(y-pre_y));}
}
gdk_draw_drawable(widget->window,fg_gc,pixmap,0,0,0,0,
                    widget->allocation.width,widget->allocation.height);
  if(pre_x < x && pre_y < y)
  {
   gdk_draw_rectangle (widget->window,
	              fg_gc,
		      FALSE,
		      pre_x, pre_y,
		      fabs(x-pre_x),
		      fabs(y-pre_y));
  }
  else if(pre_x < x && pre_y > y )
  {

   gdk_draw_rectangle (widget->window,
	              fg_gc,
		      FALSE,
		      pre_x,y,
		      fabs(x-pre_x),
		      fabs(y-pre_y));
 }
  else if(pre_x > x && pre_y < y)
  {
      gdk_draw_rectangle (widget->window,
	              fg_gc,
		      FALSE,
		      x, pre_y,
		      fabs(x-pre_x),
		      fabs(y-pre_y));
 
 }
  else
  {
      gdk_draw_rectangle (widget->window,
	             fg_gc,
		      FALSE,
		      x, y,
		      fabs(x-pre_x),
		      fabs(y-pre_y));
  }


}

void draw_round_rect( GtkWidget *widget,gdouble  x,gdouble y,gint flag )
{

GdkGCValues values;
GdkPoint points[4]={ {pre_x,pre_y},{pre_x,y},{x,y},{x,pre_y}};

gdk_gc_get_values(fg_gc,&values);

gdk_gc_set_line_attributes(fg_gc,1,
                                 values.line_style,values.cap_style,GDK_JOIN_ROUND);


if(!flag)
  gdk_draw_polygon(pixmap,fg_gc,FALSE,points,4);

gdk_draw_drawable(widget->window,fg_gc,pixmap,0,0,0,0,
                    widget->allocation.width,widget->allocation.height);

gdk_draw_polygon(widget->window,fg_gc,FALSE,points,4);

gdk_gc_set_line_attributes(fg_gc,values.line_width,
                          values.line_style,values.cap_style,values.join_style);

}



