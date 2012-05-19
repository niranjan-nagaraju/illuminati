#include "illuminati.h"

struct colorbuttontype 
{
  char filename[35];
  char tiptext[25];
  int red;
  int green;
  int blue;
};

struct colorbuttontype  array[2][10]={
{
	{ "images/gray.png","Gray",35433,32552,29733 },
	{ "images/lightgray.png","Lightgray",49894,47372,44904 },
	{ "images/red.png","Red",65535,0,0 },
	{ "images/brown.png","Brown",31776,5154,3048 },
	{ "images/orange.png","Orange",64733,38034,8312 },
	{ "images/lightbrown.png","Lightbrown",32464,20480,7138 },
	{ "images/yellow.png","Yellow",60920,64149,2411 },
	{ "images/olivegreen.png","Olivegreen",32372,32890,9842 },
	{ "images/parrotgreen.png","Parrotgreen",4832,65535,18076 },
	{ "images/darkgreen.png","Darkgreen",7398,29102,12134 }
},{
	{ "images/lightblue.png","Lightblue",2026,58292,65535 },
	{ "images/turquoise.png","Turquoise",0,25948,28765 },
	{ "images/blue.png","Blue",1173,0,65535 },
	{ "images/navyblue.png","Navyblue",2450,0,35559 },
	{ "images/pink.png","Pink",65535,28652,62081 },
	{ "images/purple.png","Purple",28871,0,26168 },
	{ "images/bisket.png","Biscuit",65535,43250,38658 },
	{ "images/skyblue.png","Skyblue",20437,37064,63569 },
	{ "images/lightgreen.png","Lightgreen",34847,65535,35392 },
	{ "images/lightyellow.png","Lightyellow",61907,65467,33256 }
}
};




void setfgcolor(GtkWidget *widget,GdkColor* color)
{

   gdk_gc_set_rgb_fg_color(fg_gc,color); 
  // fg_bg_area->style->fg[0]= *color;
//   gdk_gc_set_rgb_fg_color(fg_bg_area->style->fg_gc[0],color);

   gdk_draw_rectangle (fbpixmap,
	              fg_gc,//fg_bg_area->style->fg_gc[GTK_WIDGET_STATE (widget)],
		      TRUE,
		      5,2,
		      40,
		      40);
   gdk_draw_drawable(fg_bg_area->window,fg_gc,//fg_bg_area->style->fg_gc[GTK_WIDGET_STATE (widget)],
                                              fbpixmap,5,2,5,2,
                                              40,40);
   
  // drawing_area->style->fg[0]=*color;
   //gdk_gc_set_rgb_fg_color(drawing_area->style->fg_gc[0],color);

}

GtkWidget* create_color_button(char img_filename[],char tooltiptext[])
{

    GtkWidget *button;
    GtkWidget *box;
    GtkWidget *img;  
    GtkTooltips *tip;



    box = gtk_hbox_new (FALSE, 0);
    gtk_container_set_border_width (GTK_CONTAINER (box), 1);
    img = gtk_image_new_from_file (img_filename);
    gtk_box_pack_start (GTK_BOX (box), img, FALSE, FALSE, 1);
    gtk_widget_show (img);
    gtk_widget_show (box);
    button = gtk_button_new ();
    gtk_container_add (GTK_CONTAINER (button), box);
    tip = gtk_tooltips_new ();

    gtk_tooltips_set_tip (tip, button,tooltiptext,NULL);

    gtk_widget_show (button);

    return button;
}
GtkWidget* get_system_color_table( )
{

  GtkWidget *table;
  GdkColor* color;
  int i,j;

    table = gtk_table_new (2, 11, TRUE);

    gtk_table_set_row_spacings( GTK_TABLE(table),1);

    gtk_table_set_col_spacings( GTK_TABLE(table),1);

   

  for(i=0;i<2;i++)
    for(j=0;j<10;j++)
   {
    color=(GdkColor*)malloc(sizeof(GdkColor));
    colorpalette[i][j].color=color;
    colorpalette[i][j].color->pixel=0;
    colorpalette[i][j].color->red=array[i][j].red;
    colorpalette[i][j].color->green=array[i][j].green;
    colorpalette[i][j].color->blue=array[i][j].blue;
    colorpalette[i][j].button=create_color_button(array[i][j].filename,array[i][j].tiptext);
    gtk_table_attach(GTK_TABLE (table), colorpalette[i][j].button,
                      j,j+1,i,i+1,GTK_EXPAND|GTK_FILL,GTK_EXPAND|GTK_FILL,0,0);
    gtk_widget_show(colorpalette[i][j].button);

    g_signal_connect (G_OBJECT (colorpalette[i][j].button), "clicked",
		      G_CALLBACK (setfgcolor), (gpointer)colorpalette[i][j].color);
   }


   return table;

}   
