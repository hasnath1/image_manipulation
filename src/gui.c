#include <stdio.h>
#include <stdlib.h>

#include <iup.h>

#include <im.h>
#include <im_image.h>
#include <iupim.h>

#include "../include/custom.h"

void setupGui()
{
  Ihandle *window, *vbox;
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

  // TO DO :
  /*
    1.Implement "Brightness Adjustment" feature
    2."Crop" feature
  */

  // Ihandle *hbox = IupHbox();

  Ihandle *label = IupLabel("Image : ");
  int err;

  imImage *img = imFileImageLoadBitmap("./images/color.bmp", 0, &err);
  imImage *copy = imImageDuplicate(img);

  printf("%d\n", err);

  if (img->color_space == IM_RGB && img->data_type == IM_BYTE)
  {
    unsigned char *r = (unsigned char *)img->data[0];
    unsigned char *g = (unsigned char *)img->data[1];
    unsigned char *b = (unsigned char *)img->data[2];

    int total_pixels = img->width * img->height;

    for (int i = 0; i < total_pixels; i++)
    {
      unsigned char gray = (unsigned char)(0.299 * r[i] + 0.587 * g[i] + 0.114 * b[i]);

      r[i] = gray;
      g[i] = gray;
      b[i] = gray;
    }
  }

  printf("DONE\n");

  Ihandle *image = IupImageFromImImage(copy);
  Ihandle *image_label = IupLabel(NULL);
  IupSetAttributeHandle(image_label, "IMAGE", image);

  if (!img)
  {
    printf("Error : Couldn't load image data\n");
    return;
  }

  // image_label = IupLabel(NULL);
  // IupSetAttributeHandle(image_label, "IMAGE", img_data);

  // state.imageWidget = image_label;

  /*testing*/
  // Ihandle *t = IupGetAttributeHandle(state.imageWidget, "IMAGE");

  /*testing*/
  // defining the menu items
  item_open = IupItem("Open", NULL);
  IupSetCallback(item_open, "ACTION", (Icallback)open_clb);

  item_save_as = IupItem("Save as", NULL);

  item_exit = IupItem("Exit", NULL);
  IupSetCallback(item_exit, "ACTION", (Icallback)ext_clb);
  file_menu = IupMenu(item_open, item_save_as, IupSeparator(), item_exit, NULL);
  sub1_menu = IupSubmenu("File", file_menu);
  menu = IupMenu(sub1_menu, NULL);

  // defining

  vbox = IupVbox(hbox, label, image_label, NULL);

  // window initialization code
  window = IupDialog(vbox);
  IupSetAttributeHandle(window, "MENU", menu);
  IupSetAttribute(window, "TITLE", "Simple Notepad");
  IupSetAttribute(window, "SIZE", "400x200");

  IupShowXY(window, IUP_CENTER, IUP_CENTER);

  IupMainLoop();
}