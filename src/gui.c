#include <stdio.h>
#include <stdlib.h>

#include <iup.h>

#include <im.h>
#include <im_image.h>
#include <iupim.h>

#include "../include/custom.h"

void setupGui()
{
  // main window and Vertical box to organize elements top to bottom
  Ihandle *window, *vbox;

  // all menu items
  Ihandle *file_menu, *item_open, *item_exit, *item_save_as;
  Ihandle *menu, *sub1_menu;

  // Feature buttons
  Ihandle *btn_grayScale = IupButton("Grayscale", NULL);
  Ihandle *btn_Inversion = IupButton("Inversion", NULL);
  Ihandle *btn_horizontalFlip = IupButton("Horizontal Flip", NULL);
  Ihandle *btn_verticalFlip = IupButton("Vertical Flip", NULL);
  Ihandle *btn_rotate90 = IupButton("Rotate 90deg", NULL);
  Ihandle *btn_blur = IupButton("Blur", NULL);
  Ihandle *btn_undo = IupButton("Undo", NULL);

  // Added all the call back functions to buttons
  IupSetCallback(btn_grayScale, "ACTION", (Icallback)grayScale_clb);
  IupSetCallback(btn_Inversion, "ACTION", (Icallback)Inversion_clb);
  IupSetCallback(btn_horizontalFlip, "ACTION", (Icallback)horizontalFlip_clb);
  IupSetCallback(btn_verticalFlip, "ACTION", (Icallback)verticalFlip_clb);
  IupSetCallback(btn_rotate90, "ACTION", (Icallback)rotate90_clb);
  IupSetCallback(btn_blur, "ACTION", (Icallback)blur_clb);
  IupSetCallback(btn_undo, "ACTION", (Icallback)undo_clb);

  Ihandle *hbox = IupHbox(
      btn_grayScale,
      btn_Inversion,
      btn_horizontalFlip,
      btn_verticalFlip,
      btn_rotate90,
      btn_blur,
      btn_undo,
      NULL);

  IupSetAttribute(hbox, "GAP", "4");

  // Setting up general btn callbacks

  // TO DO :
  /*
    1.Implement "Brightness Adjustment" feature
    2."Crop" feature
  */

  Ihandle *label = IupLabel("Image : ");

  // Image Label
  state.imageWidget = IupLabel(NULL);

  // this is to force GTK-3 to treat the widget as a image widget
  IupSetAttribute(state.imageWidget, "IMAGE", "DUMMY_INIT_NAME");
  IupSetAttribute(state.imageWidget, "TITLE", NULL);

  IupSetAttribute(state.imageWidget, "EXPAND", "YES");
  IupSetAttribute(state.imageWidget, "ALIGNMENT", "ACENTER:ACENTER");

  // open
  item_open = IupItem("Open", NULL);
  IupSetCallback(item_open, "ACTION", (Icallback)open_clb);

  // save as
  item_save_as = IupItem("Save as", NULL);

  // exit
  item_exit = IupItem("Exit", NULL);
  IupSetCallback(item_exit, "ACTION", (Icallback)ext_clb);

  // organizing menu items
  file_menu = IupMenu(item_open, item_save_as, IupSeparator(), item_exit, NULL);
  sub1_menu = IupSubmenu("File", file_menu);
  menu = IupMenu(sub1_menu, NULL);

  vbox = IupVbox(hbox, label, state.imageWidget, NULL);
  IupSetAttribute(vbox, "ALIGNMENT", "ACENTER");

  // window initialization code
  window = IupDialog(vbox);

  // setting the menu to window
  IupSetAttributeHandle(window, "MENU", menu);
  IupSetAttribute(window, "TITLE", "Image Manipulation Software");
  IupSetAttribute(window, "EXPAND", "YES");
  IupSetAttribute(window, "SIZE", "500x300");
  // I wanted to add these but it is blocked to the os level on my debian gtk environment
  // I don't want to waste my time with this garbage.
  // IupSetAttribute(window, "RESIZE", "YES");
  // IupSetAttribute(window, "MAXBOX", "YES");
  // IupSetAttribute(window, "MINBOX", "YES");

  IupShowXY(window, IUP_CENTER, IUP_CENTER);

  IupMainLoop();
}