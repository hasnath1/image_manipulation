#include <stdio.h>
#include <stdlib.h>

#include <iup.h>
#include <iupim.h>
#include <im.h>
#include <im_image.h>

#include "../include/custom.h"

void setupGui()
{
  Ihandle *window, *label, *vbox;
  Ihandle *file_menu, *item_open, *item_exit, *item_save_as;
  Ihandle *menu, *sub1_menu;
  Ihandle *image_label;

  label = IupLabel("Here is your Image : ");
  Ihandle *img_data = IupLoadImage("./images/sample.bmp");

  if (!img_data)
  {
    printf("Error : Couldn't load image data\n");
    return;
  }

  image_label = IupLabel(NULL);
  IupSetAttributeHandle(image_label, "IMAGE", img_data);

  // defining the menu items
  item_open = IupItem("Open", NULL);
  item_save_as = IupItem("Save as", NULL);
  item_exit = IupItem("Exit", NULL);
  IupSetCallback(item_exit, "ACTION", (Icallback)ext_clb);

  file_menu = IupMenu(item_open, item_save_as, IupSeparator(), item_exit, NULL);
  sub1_menu = IupSubmenu("File", file_menu);
  menu = IupMenu(sub1_menu, NULL);

  // defining

  vbox = IupVbox(label, image_label, NULL);

  // window initialization code
  window = IupDialog(vbox);
  IupSetAttributeHandle(window, "MENU", menu);
  IupSetAttribute(window, "TITLE", "Simple Notepad");
  IupSetAttribute(window, "SIZE", "400x200");

  IupShowXY(window, IUP_CENTER, IUP_CENTER);

  IupMainLoop();
}