#include "illuminati.h"


/* Our menu, an array of GtkItemFactoryEntry structures that defines each menu item */
GtkItemFactoryEntry menu_items[] = {
  { "/_File",         NULL,         NULL,         0, "<Branch>" },
  { "/File/_New",     "<control>N", new_file,     0, "<StockItem>", GTK_STOCK_NEW },
  { "/File/_Open",    "<control>O", open_file,    0, "<StockItem>", GTK_STOCK_OPEN },
  { "/File/sep1",     NULL,         NULL,         0, "<Separator>" },
  { "/File/_Save",    "<control>S", save_file,    0, "<StockItem>", GTK_STOCK_SAVE },
  { "/File/Save _As", NULL,         save_as_file, 0, "<StockItem>", GTK_STOCK_SAVE_AS},
  { "/File/sep2",     NULL,         NULL,         0, "<Separator>" },
  { "/File/_Print",   "<CTRL>P",    NULL,         0, "<StockItem>", GTK_STOCK_PRINT },
  { "/File/_Quit",    "<CTRL>Q",    delete_event, 0, "<StockItem>", GTK_STOCK_QUIT },
  { "/_Edit",         NULL,         NULL,         0, "<Branch>" },
  { "/Edit/_Undo",    "<CTRL>Z",    undo     ,    0, "<StockItem>", GTK_STOCK_UNDO },
  { "/Edit/_Redo",    "<CTRL><SHFT>Z", redo     , 0, "<StockItem>", GTK_STOCK_REDO },
  { "/Edit/sep1",     NULL,         NULL,         0, "<Separator>" },
  { "/Edit/_Cut",    "<CTRL>X",     cut     ,      0, "<StockItem>", GTK_STOCK_CUT },
  { "/Edit/_Copy",    "<CTRL>C",    copy     ,     0, "<StockItem>", GTK_STOCK_COPY },
  { "/Edit/_Paste",    "<CTRL>V",   paste     ,   0, "<StockItem>", GTK_STOCK_PASTE },
  { "/Edit/_Clear",    NULL,        clear     ,   0, "<StockItem>", GTK_STOCK_CLEAR },
  { "/Edit/sep2",     NULL,         NULL,         0, "<Separator>" },
  { "/Edit/Select _All", NULL,      select_all,   0, "<Item>" },
  { "/_View",         NULL,         NULL,         0, "<Branch>" },
  { "/View/Zoom _In",    "<CTRL>+", zoom         ,2, "<StockItem>", GTK_STOCK_ZOOM_IN },
  { "/View/Zoom _Out",    "<CTRL>-",zoom         ,1, "<StockItem>", GTK_STOCK_ZOOM_OUT },
  { "/View/Zoom",    NULL,          NULL         ,0, "<Branch>"},
  { "/View/Zoom/100%",    NULL,     zoom         ,100,"<Item>"},
  { "/View/Zoom/200%",    NULL,     zoom         ,200,"<Item>"},
  { "/View/Zoom/500%",    NULL,     zoom         ,500,"<Item>"},
  { "/View/Zoom/1000%",    NULL,    zoom         ,1000,"<Item>"},
  
  { "/_Settings",    NULL,           NULL         ,0, "<Branch>"},
  { "/Settings/Toolbars",    NULL,  NULL         ,0,"<Branch>"},
  { "/Settings/Toolbars/Main Toolbar(Illuminati)",NULL, maintoolbar_toggle,0,"<CheckItem>"},   
  { "/Settings/Toolbars/Tools Toolbar(Illuminati)",NULL,toolstoolbar_toggle,0,"<CheckItem>"},   

  { "/_Help",        NULL,         NULL,         0, "<Branch>" },
  { "/Help/Topics","MOD1",         help_topics,0,   "<Item>" },
  { "/Help/About Illuminatti", NULL,about_illuminatti,0, "<Item>" }
};

/*
{ "/_Image",        NULL,         NULL,         0, "<Branch>" },
  { "/Image/R_esize",    "<CTRL>E", scaling      ,0, "<Item>" },
  { "/Image/_Flip",    "<CTRL>F",   flip        , 0, "<Item>" },
  { "/Image/_Rotate",    "<CTRL>R", rotate       ,0, "<Item>"},
  { "/Image/S_kew",    "<CTRL>K",   skew         ,0, "<Item>"},
  { "/Settings/Hide Statusbar",    NULL,statusbar_toggle ,0,"<CheckItem>"},*/


static gint nmenu_items = sizeof (menu_items) / sizeof (menu_items[0]);

/* Returns a menubar widget made from the above menu */
GtkWidget* get_menubar_menu(GtkWidget* win)
{
  GtkItemFactory *item_factory;
  GtkAccelGroup *accel_group;

  /* Make an accelerator group (shortcut keys) */
  accel_group = gtk_accel_group_new ();

  /* Make an ItemFactory (that makes a menubar) */
  item_factory = gtk_item_factory_new (GTK_TYPE_MENU_BAR, "<main>",
                                       accel_group);

  /* This function generates the menu items. Pass the item factory,
     the number of items in the array, the array itself, and any
     callback data for the the menu items. */
  gtk_item_factory_create_items (item_factory, nmenu_items, menu_items, NULL);

  /* Attach the new accelerator group to the window. */
  gtk_window_add_accel_group (GTK_WINDOW (win), accel_group);

  /* Finally, return the actual menu bar created by the item factory. */
  return gtk_item_factory_get_widget (item_factory, "<main>");
}

