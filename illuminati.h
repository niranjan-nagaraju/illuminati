
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <gdk/gdk.h>
#include <glib.h>
#include <glib/gprintf.h>
#include <string.h>
#include <math.h>

const gchar *filename;

gint modified;

GdkDisplay *display;

GdkVisual *visual;

GdkPixbuf *pixbuf; 

GdkPixmap *pixmap; /* Backing pixmap for drawing area */

GdkPixmap *scalemap; /* Backing pixmap for drawing area during scaling*/

GdkPixmap *undomap;
gint undoflag;
GdkGC *undo_gc;

GdkPixmap *redomap;
gint redoflag;
GdkGC *redo_gc;

GdkPixmap *sel_pixmap;

GdkRectangle sel_rect;

gint selected;



GdkBitmap *mask_return;

GtkWidget *window ; /*X Window to hold the application*/
  
GtkWidget *drawing_area ; /*Drawing area to draw*/

GtkWidget *colorseldlg;

GdkCursor *cursor;

GdkPixbuf *cursorbuf; 

GtkWidget *fg_bg_area;

GdkPixmap *fbpixmap;

GdkPixmap *gcf_pixmap;

GdkPixmap *gcb_pixmap;

GdkGC *fg_gc;

GdkGC *bg_gc;

gdouble zin_fact,zout_fact,z_size;

GtkWidget* mainhandlebox;
GtkWidget* toolhandlebox;
GtkWidget *scrolled_win;



gint lineflag;

GtkWidget*   pencil_button;

gint poly;



enum 
{ RECT_SEL,ERASER,LINE,TEXT,BRUSH,SPRAYCAN,PENCIL,BUCKET,
  COLORPICK,POLYLINE,ELLIPSE,POLYGON,RECTANGLE }tool;



/*coordinates of previous button clicked pos*/
gdouble pre_x;
gdouble pre_y;

/*coordinates of last event position*/
gdouble last_x;
gdouble last_y;




GtkWidget* get_fgbgframe( );

GtkWidget *get_menubar_menu( GtkWidget  *win );

GtkWidget *get_main_toolbar();

GtkWidget *get_tools_toolbar();

GtkWidget* get_system_color_table();

void delete_event(GtkWidget *widget,gpointer data );

void new_file( GtkWidget *w,gpointer   data );

void save_file( GtkWidget *w,gpointer   data );

void save_as_file( GtkWidget *w, gpointer   data );

void undo( GtkWidget *w,gpointer   data );

void redo( GtkWidget *w,gpointer   data );

void cut( GtkWidget *w,gpointer data);

void copy( GtkWidget *w,gpointer   data );

void paste( GtkWidget *w,gpointer   data );

void clear( GtkWidget *w, gpointer   data );

void select_all( GtkWidget *w, gpointer   data );

void scaling( GtkWidget *w, gpointer   data );

void flip( GtkWidget *w, gpointer   data );

void rotate( GtkWidget *w, gpointer   data );

void skew( GtkWidget *w, gpointer   data );

void zoom(GtkWidget *w ,gpointer  data);

void what_is_this( gpointer   callback_data , GtkWidget *menu_item );

void help_topics( GtkWidget *menu_item, gpointer data );

void select_rectangular_region( GtkWidget *w,gdouble  x,gdouble y,gint flag);

void eraser( GtkWidget *w,gdouble x,gdouble y);

void draw_line( GtkWidget *widget,gdouble x,gdouble y,gint flag);

void draw_text( GtkWidget *w,gdouble  x,gdouble y );

void paintbrush( GtkWidget *w,gdouble x,gdouble y );

void spraycan( GtkWidget *w,gdouble x,gdouble y );

void draw_using_pencil(GtkWidget *widget,gdouble x,gdouble y);

void bucketfill( GtkWidget *w,gint  x,gint y);

void colorpicker( GtkWidget *w,gdouble x,gdouble y);

void draw_polyline( GtkWidget *w,gdouble x,gdouble y,gint flag);

void draw_arc( GtkWidget *widget,gdouble x,gdouble y,gint flag);

void draw_polygon( GtkWidget *w,gdouble x,gdouble y,gint flag);

void draw_rectangle( GtkWidget *widget,gdouble  x,gdouble y,gint flag );

void draw_round_rect( GtkWidget *widget,gdouble  x,gdouble y,gint flag );



/*functions used for opening the file*/

void open_file( GtkWidget *w,gpointer   data );

void loadfile (GtkWidget *widget, gpointer user_data) ;

void create_file_selection ();

void get_savefilename(GtkWidget *widget, gpointer user_data) ;

void maintoolbar_toggle(gpointer data,guint action,GtkWidget *menuitem);

void toolstoolbar_toggle(gpointer data,guint action,GtkWidget *menuitem);

void statusbar_toggle( gpointer   callback_data,GtkWidget *menu_item );

void about_illuminatti( GtkWidget *menuitem,gpointer data);


