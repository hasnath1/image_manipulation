#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iup.h>
#include <iupim.h>
#include <im.h>
#include <im_image.h>

#include "../include/custom.h"

int open_clb(Ihandle *self)
{
  Ihandle *file_dlg = IupFileDlg();
  IupSetAttribute(file_dlg, "DIALOGTYPE", "OPEN");
  IupSetAttribute(file_dlg, "TITLE", "Select a BMP Image");
  IupSetAttribute(file_dlg, "EXTFILTER", "BMP Images (*.bmp)|*.bmp|");

  IupPopup(file_dlg, IUP_CENTER, IUP_CENTER);

  if (IupGetInt(file_dlg, "STATUS") != -1)
  {
    char *fileName = IupGetAttribute(file_dlg, "VALUE");
    size_t s = strlen(fileName);
    state.currentImageFile = (char *)malloc(sizeof(char) * (s + 1));
    strcpy(state.currentImageFile, fileName);

    printf("%s\n", state.currentImageFile);
  }

  IupDestroy(file_dlg);

  return IUP_DEFAULT;
}

int ext_clb(Ihandle *self)
{
  return IUP_CLOSE;
}