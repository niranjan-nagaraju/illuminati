#include "illuminati.h"

	

/* Obligatory basic callbacks */


void delete_event(GtkWidget *widget,gpointer data )
{
    GtkWidget* dialog;
    GtkWidget* label;
    GtkWidget* hbox;
    GtkWidget* box;
    GtkWidget* button;
    GtkWidget* hseperator;
    GtkWidget* iconw;
    if(!modified) 
      gtk_main_quit();

    
    dialog=gtk_dialog_new();
 

    g_signal_connect_swapped (G_OBJECT (dialog), "delete-event",
                    G_CALLBACK (gtk_widget_destroy), G_OBJECT(dialog));
  

    label=gtk_label_new("The current document has been modified\n\tDo you want to save it ?\n");
    iconw = gtk_image_new_from_stock (GTK_STOCK_DIALOG_WARNING,3); /*<new> icon widget */

    

    hbox=gtk_hbox_new(FALSE,5) ;
    gtk_box_pack_start (GTK_BOX(GTK_DIALOG(dialog)->vbox),hbox, FALSE, FALSE, 0);
    
    gtk_box_pack_start (GTK_BOX(hbox),iconw, FALSE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX(hbox),label, FALSE, FALSE, 0);
    gtk_widget_show(iconw) ;
    gtk_widget_show(label) ;
    gtk_widget_show(hbox) ;
    
   /* hseperator=gtk_hseparator_new(); 
    gtk_box_pack_start (GTK_BOX(GTK_DIALOG(dialog)->vbox),hseperator, FALSE, FALSE, 0);
    gtk_widget_show(hseperator) ;*/
     
    hbox=gtk_hbox_new(TRUE,4) ;
    gtk_box_pack_start (GTK_BOX(GTK_DIALOG(dialog)->vbox),hbox, FALSE, FALSE, 0);

    button=gtk_button_new();
    box=gtk_hbox_new(FALSE,2) ;
    label=gtk_label_new(" Save  ");
    iconw = gtk_image_new_from_stock (GTK_STOCK_SAVE,2); /*<new> icon widget */
    gtk_box_pack_start (GTK_BOX(box),iconw, FALSE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX(box),label, FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(button), box);
    gtk_widget_show(iconw) ;
    gtk_widget_show(label) ;
    gtk_widget_show(box) ;
    gtk_box_pack_start (GTK_BOX(hbox),button, FALSE, FALSE, 0);
    gtk_widget_show(button) ;
    g_signal_connect (G_OBJECT (button), "clicked",
                    G_CALLBACK (save_as_file), (gpointer)1);
    g_signal_connect_swapped (G_OBJECT (button), "clicked",
                    G_CALLBACK (gtk_widget_destroy), G_OBJECT(dialog));
  
    button=gtk_button_new_with_label(" Discard ");
    gtk_box_pack_start (GTK_BOX(hbox),button, FALSE, FALSE, 0);
    gtk_widget_show(button) ;


                     
    g_signal_connect(G_OBJECT (button), "clicked",
                    G_CALLBACK (gtk_main_quit), NULL);


    button=gtk_button_new();
    box=gtk_hbox_new(FALSE,2) ;
    label=gtk_label_new(" Cancel");
    iconw = gtk_image_new_from_stock (GTK_STOCK_CLOSE,3); /*<new> icon widget */
    gtk_box_pack_start (GTK_BOX(box),iconw, FALSE, FALSE, 0);
    gtk_box_pack_start (GTK_BOX(box),label, FALSE, FALSE, 0);
    gtk_container_add(GTK_CONTAINER(button), box);
    gtk_widget_show(iconw) ;
    gtk_widget_show(label) ;
    gtk_widget_show(box) ;
    gtk_box_pack_start(GTK_BOX(hbox),button, FALSE, FALSE, 0);
    gtk_widget_show(button) ;
    g_signal_connect_swapped (G_OBJECT (button), "clicked",
                    G_CALLBACK (gtk_widget_destroy), G_OBJECT(dialog));

    gtk_widget_show(hbox) ;

    gtk_widget_show(dialog) ;

}
    
void initialise()
{
	modified=0;


        undomap = gdk_pixmap_new(drawing_area->window,
			   drawing_area->allocation.width,
			   drawing_area->allocation.height,
			   -1);
        gdk_draw_rectangle (undomap,
		      drawing_area->style->white_gc,
		      TRUE,
		      0, 0,
		      drawing_area->allocation.width,
		      drawing_area->allocation.height);
        undo_gc=gdk_gc_new(undomap);
        undoflag=0;

        redomap = gdk_pixmap_new(drawing_area->window,
			   drawing_area->allocation.width,
			   drawing_area->allocation.height,
			   -1);
        gdk_draw_rectangle (redomap,
		      drawing_area->style->white_gc,
		      TRUE,
		      0, 0,
		      drawing_area->allocation.width,
		      drawing_area->allocation.height);
        redo_gc=gdk_gc_new(redomap);
        redoflag=0;


	zin_fact=.125;
	zout_fact=.125;
	z_size=1;

	poly=0;

	lineflag=0;

       /*coordinates of previous button clicked pos*/
        pre_x=0;
        pre_y=0;

      /*coordinates of last event position*/
        last_x=0;
        last_y=0;

    scalemap = gdk_pixmap_new(drawing_area->window,
			   drawing_area->allocation.width,
			   drawing_area->allocation.height,
			   -1);
}


/*---------------------------------To open a new file--------------------------*/

void new_file( GtkWidget *w,gpointer   data )
{
   
   filename=g_strdup("Untitled.jpeg");	

   pixmap = gdk_pixmap_new(drawing_area->window,
			   drawing_area->allocation.width,
			   drawing_area->allocation.height,
			   -1);

   gdk_draw_rectangle (pixmap,
		      drawing_area->style->white_gc,
		      TRUE,
		      0, 0,
		      drawing_area->allocation.width,
		      drawing_area->allocation.height);

   gdk_draw_drawable( drawing_area->window,
                      drawing_area->style->fg_gc[GTK_WIDGET_STATE (drawing_area)],
             	      pixmap,
		      0,0,
		      0,0,
		      -1,-1);

   pixbuf=gdk_pixbuf_get_from_drawable(NULL,pixmap,
                                       gdk_drawable_get_colormap(pixmap),
                                       0,0,
                                       0,0,   
                                       -1,-1);
   initialise(); 


}

/*---------------End of newfile section -----------*/


/*-------------To open a existing file-------------*/

/* The file selection widget and the string to store the chosen filename */
void loadfile (GtkWidget *widget, gpointer user_data) 
{
   
   
   GtkWidget *file_selector = GTK_WIDGET (user_data);
   GError *error= NULL;
   GdkColor* color=(GdkColor*)malloc(sizeof(GdkColor));

   filename = gtk_file_selection_get_filename (GTK_FILE_SELECTION (file_selector));
   pixbuf=gdk_pixbuf_new_from_file(filename,&error); 
   pixmap = gdk_pixmap_new(drawing_area->window,
			   gdk_pixbuf_get_width(pixbuf),
                           gdk_pixbuf_get_height(pixbuf),
			   -1);
   gdk_pixbuf_render_pixmap_and_mask(pixbuf,&pixmap,&mask_return,0);
   gdk_draw_drawable( drawing_area->window,
                      fg_gc,
             	      pixmap,
		      0,0,
		      0,0,
		      drawing_area->allocation.width,drawing_area->allocation.height);

}

void create_file_selection () {

   GtkWidget *file_selector;

   /* Create the selector */
   
   file_selector = gtk_file_selection_new ("Open File");
   
   g_signal_connect (GTK_FILE_SELECTION (file_selector)->ok_button,
                     "clicked",
                     G_CALLBACK (loadfile),
                     file_selector);
   			   
   /* Ensure that the dialog box is destroyed when the user clicks a button. */
   
   g_signal_connect_swapped (GTK_FILE_SELECTION (file_selector)->ok_button,
                             "clicked",
                             G_CALLBACK (gtk_widget_destroy), 
                             file_selector);

   g_signal_connect_swapped (GTK_FILE_SELECTION (file_selector)->cancel_button,
                             "clicked",
                             G_CALLBACK (gtk_widget_destroy),
                             file_selector); 
   
   /* Display that dialog */
   
   gtk_widget_show (file_selector);
}
void open_file( GtkWidget *w, gpointer   data )
{
  create_file_selection();
  initialise();
}

/*------------------------------End of open file section------------------------------*/


/*--------------------To save the buffer to file-------------------------*/
void save_file( GtkWidget *w, gpointer   data )
{
  char *type,*revtype,*i,*j;
  char *option_keys=NULL;
  char *option_values=NULL;
  GError *error=NULL;
  int len=0;
  	
  g_assert(filename != NULL);

  pixbuf=gdk_pixbuf_get_from_drawable(pixbuf,pixmap,
                               gdk_drawable_get_colormap(pixmap),
                               0,0,
                               0,0,   
                               -1,-1);
 g_assert(pixbuf != NULL);

 type=(char *)malloc(sizeof(char *));
 revtype=(char *)malloc(sizeof(char *));
 j=revtype;
 len=strlen(filename);
 i= (char *)(filename + len - 1);
 while( *i != '.')
    *j++=*i--;
*j='\0';


 j=type;
 len=strlen(revtype);
 i=revtype + len - 1;
 while(len--)
  *j++=*i--;
 *j='\0'  ;

 gdk_pixbuf_savev(pixbuf,filename,type,&option_keys,&option_values,&error);

}

/*----------------------End of save section-------------*/

/*------------------------------Save as Section-------------*/
void save_as_file( GtkWidget *w, gpointer   data )
{
   GtkWidget *file_selector;

   modified=0;
   if((gint)data==1)
    if(strcmp(filename,"Untitled.jpeg"))
     save_file(NULL,NULL);
   

   /* Create the selector */
   
   file_selector = gtk_file_selection_new ("Save as file");
   
   g_signal_connect (GTK_FILE_SELECTION (file_selector)->ok_button,
                     "clicked",
                     G_CALLBACK (get_savefilename),
                     file_selector);
   			   
   /* Ensure that the dialog box is destroyed when the user clicks a button. */
   
   g_signal_connect_swapped (GTK_FILE_SELECTION (file_selector)->ok_button,
                             "clicked",
                             G_CALLBACK (gtk_widget_destroy), 
                             file_selector);

   g_signal_connect_swapped (GTK_FILE_SELECTION (file_selector)->cancel_button,
                             "clicked",
                             G_CALLBACK (gtk_widget_destroy),
                             file_selector); 
   
   /* Display that dialog */
   
   gtk_widget_show (file_selector);

}
void get_savefilename(GtkWidget *widget, gpointer user_data) 
{
   GtkWidget *file_selector = GTK_WIDGET (user_data);
   filename = gtk_file_selection_get_filename (GTK_FILE_SELECTION (file_selector));
   save_file(NULL,NULL) ;
}


/*---------------End of Save as Section----------------------*/
void undo( GtkWidget *w, gpointer   data )
{
  if(undoflag)
  {    
       
     if(tool == COLORPICK )
     {
        gdk_gc_copy(redo_gc,fg_gc);
                    redoflag=1;
        gdk_gc_copy(fg_gc,undo_gc);
                    undoflag=0;
        gdk_draw_rectangle (fbpixmap,fg_gc,TRUE,5,2,40,40);
        gdk_draw_drawable(fg_bg_area->window,fg_gc,fbpixmap,5,2,5,2,40,40);

     }
    else
    {
      gdk_draw_drawable(redomap,fg_gc,pixmap,0,0,0,0,-1,-1);
      redoflag=1;                                      

      gdk_draw_drawable(pixmap,fg_gc,undomap,0,0,0,0,-1,-1);
      gdk_draw_drawable(drawing_area->window,fg_gc,pixmap,0,0,0,0,-1,-1);
      undoflag=0;

   }
 }
}
void redo( GtkWidget *w, gpointer   data )
{
  if(redoflag)
  {
       if(tool == COLORPICK )
       {
           gdk_gc_copy(undo_gc,fg_gc);
                    undoflag=1;
           gdk_gc_copy(fg_gc,redo_gc);
                    redoflag=0;
        gdk_draw_rectangle (fbpixmap,fg_gc,TRUE,5,2,40,40);
        gdk_draw_drawable(fg_bg_area->window,fg_gc,fbpixmap,5,2,5,2,40,40);
       }
       else
       {
          gdk_draw_drawable(undomap,fg_gc,pixmap,0,0,0,0,-1,-1);
                      undoflag=1;

          gdk_draw_drawable(pixmap,fg_gc,redomap,0,0,0,0,-1,-1);
          gdk_draw_drawable(drawing_area->window,fg_gc,redomap,0,0,0,0,-1,-1);
                      redoflag=0;

       }

  }
}
void cut( GtkWidget *w,gpointer   data )
{
       if(selected)
       {
        gdk_draw_drawable(undomap,fg_gc,pixmap,0,0,0,0,-1,-1);
                 undoflag=1;
        gdk_draw_drawable (sel_pixmap,
	              fg_gc,
		      pixmap,
		      sel_rect.x, sel_rect.y,0,0,
		      sel_rect.width,
		      sel_rect.height);
	gdk_draw_rectangle (pixmap,
	             bg_gc,
		     TRUE ,
		     sel_rect.x,sel_rect.y,
		     sel_rect.width,
		     sel_rect.height);
        gdk_draw_drawable(drawing_area->window,fg_gc,pixmap,0,0,0,0,
                    drawing_area->allocation.width,
                    drawing_area->allocation.height);
        }
          

}

void copy( GtkWidget *w, gpointer   data )
{
if(sel_pixmap != NULL )
   gdk_draw_drawable (sel_pixmap,
	              fg_gc,
		      pixmap,
		      sel_rect.x, sel_rect.y,0,0,
		      sel_rect.width,
		      sel_rect.height);
}
void paste( GtkWidget *w, gpointer   data )
{
if(sel_pixmap != NULL )
{
        gdk_draw_drawable(undomap,fg_gc,pixmap,0,0,0,0,-1,-1);
                 undoflag=1;
        gdk_draw_drawable(pixmap,
	             fg_gc,
		     sel_pixmap,0,0,
		     pre_x,pre_y,
		     sel_rect.width,
		     sel_rect.height);
        gdk_draw_drawable(drawing_area->window,fg_gc,pixmap,0,0,0,0,
                    drawing_area->allocation.width,
                    drawing_area->allocation.height);
}
          
}
void clear( GtkWidget *w, gpointer   data )
{
  gdk_draw_drawable(undomap,fg_gc,pixmap,0,0,0,0,-1,-1);
                 undoflag=1;

  gdk_draw_rectangle (pixmap,bg_gc,TRUE,0,0,
                      drawing_area->allocation.width,drawing_area->allocation.height);
 
  gdk_draw_rectangle (drawing_area->window,bg_gc,TRUE,0,0,
                      drawing_area->allocation.width,drawing_area->allocation.height);
}
void select_all( GtkWidget *w, gpointer   data )
{
   GdkGCValues values;

   gdk_gc_get_values(fg_gc,&values);
   
   gdk_gc_set_line_attributes(fg_gc,values.line_width,GDK_LINE_ON_OFF_DASH,
                                      GDK_CAP_BUTT,
                                      GDK_JOIN_MITER);
     sel_rect.x=0;
     sel_rect.y=0;
     sel_rect.width=drawing_area->allocation.width;
     sel_rect.height=drawing_area->allocation.height;

   gdk_draw_rectangle (drawing_area->window,fg_gc,FALSE,3,3,sel_rect.width-4	,sel_rect.height-4);

   gdk_gc_set_line_attributes(fg_gc,values.line_width,values.line_style,
                                      values.cap_style,
                                      values.join_style);
}
void zoom(GtkWidget *w, gpointer data)
{
         double scale_x;
         double scale_y;
         GdkPixbuf *src; 
         GdkPixbuf *dest;
         static double zifact=0,zofact=0; 
      
         gdk_draw_drawable(scalemap,fg_gc,pixmap,0,0,0,0,
                    drawing_area->allocation.width,
                    drawing_area->allocation.height);
         src=gdk_pixbuf_copy(pixbuf);
         src=gdk_pixbuf_get_from_drawable(src,pixmap,
                gdk_drawable_get_colormap(pixmap),0,0,0,0,-1,-1);
         
         dest=gdk_pixbuf_new(GDK_COLORSPACE_RGB,FALSE,8,
                                  2*gdk_pixbuf_get_width(src),
                                  2*gdk_pixbuf_get_height(src));


    switch((gint)data)
    {
       case 1:zifact=zifact+zin_fact;
              scale_x=z_size-zin_fact;
              scale_y=z_size-zin_fact;
	      dest=gdk_pixbuf_scale_simple(src,
                               scale_x*gdk_pixbuf_get_width(src),
                               scale_y*gdk_pixbuf_get_height(src),
                               GDK_INTERP_BILINEAR);
              break;
              
       case 2:zofact=zofact+zout_fact;
              scale_x=z_size+zout_fact;
              scale_y=z_size+zout_fact;
	      dest=gdk_pixbuf_scale_simple(src,
                               scale_x*gdk_pixbuf_get_width(src),
                               scale_y*gdk_pixbuf_get_height(src),
                               GDK_INTERP_BILINEAR);
              break;

       case 100:scale_x=z_size;
                scale_y=z_size;
	      dest=gdk_pixbuf_scale_simple(src,
                               scale_x*gdk_pixbuf_get_width(src),
                               scale_y*gdk_pixbuf_get_height(src),
                               GDK_INTERP_BILINEAR);
              break;
       case 200:scale_x=z_size+.33;
                scale_y=z_size+.33;
	      dest=gdk_pixbuf_scale_simple(src,
                               scale_x*gdk_pixbuf_get_width(src),
                               scale_y*gdk_pixbuf_get_height(src),
                               GDK_INTERP_BILINEAR);
              break;
       case 500:scale_x=z_size+.66;
                scale_y=z_size+.66;
	      dest=gdk_pixbuf_scale_simple(src,
                               scale_x*gdk_pixbuf_get_width(src),
                               scale_y*gdk_pixbuf_get_height(src),
                               GDK_INTERP_BILINEAR);
              break;
      case 1000:scale_x=z_size+.99;
                scale_y=z_size+.99;
	      dest=gdk_pixbuf_scale_simple(src,
                               scale_x*gdk_pixbuf_get_width(src),
                               scale_y*gdk_pixbuf_get_height(src),
                               GDK_INTERP_BILINEAR);
              break;	
   }

   scalemap = gdk_pixmap_new(drawing_area->window,
			   gdk_pixbuf_get_width(dest),
                           gdk_pixbuf_get_height(dest),
			   -1);
   gdk_pixbuf_render_pixmap_and_mask(dest,&scalemap, &mask_return,0);
   
   gtk_widget_set_size_request (GTK_WIDGET(drawing_area),			               
                                           gdk_pixbuf_get_width(dest),
                                           gdk_pixbuf_get_height(dest));

   gdk_draw_rectangle (pixmap,drawing_area->style->bg_gc[0],TRUE,0, 0,-1,-1);
   gdk_draw_drawable (pixmap,fg_gc,scalemap,0,0,0,0,
                                           gdk_pixbuf_get_width(dest),
                                           gdk_pixbuf_get_height(dest));


   gdk_draw_drawable (drawing_area->window,fg_gc,pixmap,0,0,0,0,
                                           gdk_pixbuf_get_width(dest),
                                           gdk_pixbuf_get_height(dest));

}
void scaling( GtkWidget *w, gpointer   data )
{
  g_message ("Hello, World!\n");
}
void flip( GtkWidget *w, gpointer   data )
{
  g_message ("Hello, World!\n");
}
void rotate( GtkWidget *w, gpointer   data )
{
  g_message ("Hello, World!\n");
}
void skew( GtkWidget *w, gpointer   data )
{
  g_message ("Hello, World!\n");
}


void maintoolbar_toggle(gpointer data,guint action,GtkWidget *menuitem)
{
    if (GTK_CHECK_MENU_ITEM (menuitem)->active) 
    {
      gtk_widget_hide(mainhandlebox);
      gtk_widget_set_size_request (GTK_WIDGET (scrolled_win),400,450);
    }
    else 
    {
          gtk_widget_show(mainhandlebox);
          gtk_widget_set_size_request (GTK_WIDGET (scrolled_win),400,400);
     }
}

void toolstoolbar_toggle(gpointer data,guint action,GtkWidget *menuitem )
{
    if (GTK_CHECK_MENU_ITEM (menuitem)->active) 
    {
          gtk_widget_hide(toolhandlebox);
          gtk_widget_set_size_request (GTK_WIDGET (scrolled_win),450,400);
    }
    else 
    {
          gtk_widget_show(toolhandlebox);
          gtk_widget_set_size_request (GTK_WIDGET (scrolled_win),400,400);
    }
}

void statusbar_toggle( gpointer   callback_data,GtkWidget *menu_item )
{

}
void help_topics( GtkWidget *menu_item, gpointer data )
{
    system("firefox /home/manju/illuminati/manual.htm");
}
void what_is_this( gpointer   callback_data , GtkWidget *menu_item )
{
}
void about_illuminatti( GtkWidget *menuitem, gpointer data)
{
    GtkWidget *win;
    GtkWidget *button;
    GtkWidget *table;
    GtkWidget *notebook;
    GtkWidget *frame;
    GtkWidget *label;
    GtkWidget *hbox;
    GtkWidget *iconw;

    win = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    
    g_signal_connect_swapped(G_OBJECT (win), "delete_event",
	              G_CALLBACK (gtk_widget_destroy), G_OBJECT(win));
    
    gtk_container_set_border_width (GTK_CONTAINER (win), 10);

    gtk_widget_set_size_request (GTK_WIDGET (win),400,300);

    table = gtk_table_new (5, 6, FALSE);
    gtk_container_add (GTK_CONTAINER (win), table);

    iconw = gtk_image_new_from_file ("icons/apple-red.png");
    label = gtk_label_new("Illuminati (Using Gnome 2.4)");
    hbox= gtk_hbox_new(FALSE,3) ;

    gtk_box_pack_start (GTK_BOX (hbox),iconw, FALSE, FALSE, 5);
    gtk_box_pack_start (GTK_BOX (hbox),label, FALSE, FALSE, 5);
    gtk_widget_show (iconw);
    gtk_widget_show (label);
    gtk_table_attach_defaults (GTK_TABLE (table), hbox, 0, 6, 0, 1);
    gtk_widget_show (hbox);

    /* Create a new notebook, place the position of the tabs */
    notebook = gtk_notebook_new ();
    gtk_notebook_set_tab_pos (GTK_NOTEBOOK (notebook), GTK_POS_TOP);
    gtk_table_attach_defaults (GTK_TABLE (table), notebook, 0, 6, 1, 2);
    gtk_widget_show (notebook);
    

	frame = gtk_frame_new (NULL);
	gtk_container_set_border_width (GTK_CONTAINER (frame), 10);
	gtk_widget_set_size_request (frame, 100, 75);
	gtk_widget_show (frame);
	
	label = gtk_label_new ("\nGraphics Editor for gnome\nCopyright (c) 2005-2006 Pesit");
	gtk_container_add (GTK_CONTAINER (frame), label);
	gtk_widget_show (label);
	
	label = gtk_label_new ("About");
	gtk_notebook_append_page (GTK_NOTEBOOK (notebook), frame, label);

        frame = gtk_frame_new (NULL);
	gtk_container_set_border_width (GTK_CONTAINER (frame), 10);
	gtk_widget_set_size_request (frame, 100, 75);
	gtk_widget_show (frame);
	
	label = gtk_label_new ("Manjunath T\n\tmanjubailpar079@gmail.com\n\nN.Niranjan\n\tviniThePooh@gmail.com");
	gtk_container_add (GTK_CONTAINER (frame), label);
	gtk_widget_show (label);
	
	label = gtk_label_new ("Authors");
	gtk_notebook_append_page (GTK_NOTEBOOK (notebook), frame, label);

        frame = gtk_frame_new (NULL);
	gtk_container_set_border_width (GTK_CONTAINER (frame), 10);
	gtk_widget_set_size_request (frame, 100, 75);
	gtk_widget_show (frame);
	
	label = gtk_label_new ("Mr V.R.BadriPrasad\n\nMr Praveen\n\nMr Nitin.V.Pujari\n");
	gtk_container_add (GTK_CONTAINER (frame), label);
	gtk_widget_show (label);
	
	label = gtk_label_new ("Thanks To");
	gtk_notebook_append_page (GTK_NOTEBOOK (notebook), frame, label);
    
        gtk_notebook_set_current_page (GTK_NOTEBOOK (notebook), 1);

        /* Create a bunch of buttons */
        button = gtk_button_new_with_label ("close");
        
        g_signal_connect_swapped (G_OBJECT (button), "clicked",
			      G_CALLBACK (gtk_widget_destroy), G_OBJECT(win));
        gtk_table_attach_defaults (GTK_TABLE (table), button, 5,6,4,5);
	gtk_widget_show (button);
    
        gtk_widget_show (table);
        gtk_widget_show (win);

}







