#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <iup.h>
#include <iupim.h>
#include <im.h>
#include <im_image.h>

#include "../include/custom.h"

int grayScale_clb(Ihandle *self)
{
  // printState();

  if (!isAppStateValid())
    return IUP_CLOSE;

  if (state.undoImage)
    imImageDestroy(state.undoImage);
  state.undoImage = imImageDuplicate(state.currentImage);

  int w = state.currentImage->width;
  int h = state.currentImage->height;

  unsigned char *r = state.currentImage->data[0];
  unsigned char *g = state.currentImage->data[1];
  unsigned char *b = state.currentImage->data[2];

  for (int i = 0; i < w * h; i++)
  {
    unsigned char gray = 0.299 * r[i] + 0.587 * g[i] + 0.114 * b[i];
    r[i] = gray;
    g[i] = gray;
    b[i] = gray;
  }

  updateUIImage(self);

  // Ihandle *old_img = (Ihandle *)IupGetAttributeHandle(state.imageWidget, "IMAGE");
  // Ihandle *new_img = IupImageFromImImage(state.currentImage);

  return IUP_DEFAULT;
};

int Inversion_clb(Ihandle *self)
{
  if (!isAppStateValid())
    return IUP_CLOSE;

  if (state.undoImage)
    imImageDestroy(state.undoImage);
  state.undoImage = imImageDuplicate(state.currentImage);

  int w = state.currentImage->width;
  int h = state.currentImage->height;

  unsigned char *r = state.currentImage->data[0];
  unsigned char *g = state.currentImage->data[1];
  unsigned char *b = state.currentImage->data[2];

  for (int i = 0; i < w * h; i++)
  {
    // unsigned char gray = 0.299 * r[i] + 0.587 * g[i] + 0.114 * b[i];
    r[i] = 255 - r[i];
    g[i] = 255 - g[i];
    b[i] = 255 - b[i];
  }

  updateUIImage(self);

  return IUP_DEFAULT;
};

int horizontalFlip_clb(Ihandle *self)
{
  if (!isAppStateValid())
    return IUP_CLOSE;

  if (state.undoImage)
    imImageDestroy(state.undoImage);
  state.undoImage = imImageDuplicate(state.currentImage);

  int w = state.currentImage->width;
  int h = state.currentImage->height;

  unsigned char *r = state.currentImage->data[0];
  unsigned char *g = state.currentImage->data[1];
  unsigned char *b = state.currentImage->data[2];

  // for each row
  for (int i = 0; i < h; i++)
  {

    // for every element on that row upto middle point
    for (int j = 0; j < w / 2; j++)
    {

      // (i*w) ==> means i-th row || j ==> means j-th column
      int idx1 = i * w + j;
      // (w-1-j)==> means (w-j)-th column // we are trying to get rows from the end;
      int idx2 = i * w + (w - 1 - j);

      unsigned char temp = r[idx1];
      r[idx1] = r[idx2];
      r[idx2] = temp;

      temp = g[idx1];
      g[idx1] = g[idx2];
      g[idx2] = temp;

      temp = b[idx1];
      b[idx1] = b[idx2];
      b[idx2] = temp;
    }
  }

  updateUIImage(self);

  return IUP_DEFAULT;
};

int verticalFlip_clb(Ihandle *self)
{
  if (!isAppStateValid())
    return IUP_CLOSE;

  if (state.undoImage)
    imImageDestroy(state.undoImage);
  state.undoImage = imImageDuplicate(state.currentImage);

  int w = state.currentImage->width;  // number of columns
  int h = state.currentImage->height; // number of rows

  unsigned char *r = state.currentImage->data[0];
  unsigned char *g = state.currentImage->data[1];
  unsigned char *b = state.currentImage->data[2];

  for (int i = 0; i < h / 2; i++)
  {
    for (int j = 0; j < w; j++)
    {

      // (i*w) ==> means i-th row || j ==> means j-th column
      int idx1 = i * w + j;
      // (h-1-i) ==> means (h-i)-th row // we are trying to get the rows from the end;
      int idx2 = (h - 1 - i) * w + j;

      unsigned char temp = r[idx1];
      r[idx1] = r[idx2];
      r[idx2] = temp;

      temp = g[idx1];
      g[idx1] = g[idx2];
      g[idx2] = temp;

      temp = b[idx1];
      b[idx1] = b[idx2];
      b[idx2] = temp;
    }
  }

  updateUIImage(self);

  return IUP_DEFAULT;
};

int rotate90_clb(Ihandle *self)
{
  if (!isAppStateValid())
    return IUP_CLOSE;

  if (state.undoImage)
    imImageDestroy(state.undoImage);
  state.undoImage = imImageDuplicate(state.currentImage);

  int w = state.currentImage->width;  // number of columns
  int h = state.currentImage->height; // number of rows

  unsigned char *r = state.currentImage->data[0];
  unsigned char *g = state.currentImage->data[1];
  unsigned char *b = state.currentImage->data[2];

  // we have to create a new image because the dimensions has changed.
  // so we need to allocate new memory for it.

  imImage *newImage = imImageCreate(h, w, state.currentImage->color_space, state.currentImage->data_type);
  unsigned char *n_r = newImage->data[0];
  unsigned char *n_g = newImage->data[1];
  unsigned char *n_b = newImage->data[2];

  // for each row
  for (int i = 0; i < h; i++)
  {
    // for each element of that row
    for (int j = 0; j < w; j++)
    {
      int src_index = i * w + j;

      // I took help of gemini to come up with this part.
      // formula to rotate 90def clockwise .
      // new row is (w - 1 - y), new column is x
      // Note : imImage stores the image data bottom up thats why we used this formula.
      int dst_index = (w - 1 - j) * h + i;
      ;

      n_r[dst_index] = r[src_index];
      n_g[dst_index] = g[src_index];
      n_b[dst_index] = b[src_index];
    }
  }

  // free up the old image
  imImageDestroy(state.currentImage);
  state.currentImage = newImage;
  updateUIImage(self);

  return IUP_DEFAULT;
};

int blur_clb(Ihandle *self)
{
  if (!isAppStateValid())
    return IUP_CLOSE;
  if (state.undoImage)
    imImageDestroy(state.undoImage);
  state.undoImage = imImageDuplicate(state.currentImage);

  int w = state.currentImage->width;  // number of columns
  int h = state.currentImage->height; // number of rows

  unsigned char *r = state.currentImage->data[0];
  unsigned char *g = state.currentImage->data[1];
  unsigned char *b = state.currentImage->data[2];

  imImage *newImage = imImageCreate(w, h, state.currentImage->color_space, state.currentImage->data_type);
  unsigned char *n_r = newImage->data[0];
  unsigned char *n_g = newImage->data[1];
  unsigned char *n_b = newImage->data[2];

  // to parse all the surrounding pixels and including the center one
  int dx[] = {-1, -1, -1, 0, 0, 0, 1, 1, 1};
  int dy[] = {-1, 0, 1, -1, 0, 1, -1, 0, 1};

  // i = row j = column
  for (int i = 0; i < h; i++)
  {
    for (int j = 0; j < w; j++)
    {
      unsigned int sum_r = 0;
      unsigned int sum_g = 0;
      unsigned int sum_b = 0;
      unsigned int divider = 0;

      for (int k = 0; k < 9; k++)
      {
        // i = current row | j = current col
        int neighbor_row = i + dx[k];
        int neighbor_col = j + dy[k];

        if (neighbor_row >= 0 && neighbor_row < w && neighbor_col >= 0 && neighbor_col < h)
        {
          int src = neighbor_row * w + neighbor_col;
          sum_r += r[src];
          sum_g += g[src];
          sum_b += b[src];
          divider++;
        }
      }

      sum_r /= divider;
      sum_g /= divider;
      sum_b /= divider;

      int dst = i * w + j;

      n_r[dst] = (unsigned char)sum_r;
      n_g[dst] = (unsigned char)sum_g;
      n_b[dst] = (unsigned char)sum_b;
    }
  }

  // free up the old image
  imImageDestroy(state.currentImage);
  state.currentImage = newImage;
  updateUIImage(self);

  return IUP_DEFAULT;
};

int undo_clb(Ihandle *self)
{
  if (!isAppStateValid())
    return IUP_CLOSE;

  if (state.undoImage == NULL)
    return IUP_DEFAULT;

  imImage *temp = imImageDuplicate(state.undoImage);

  imImageDestroy(state.currentImage);
  imImageDestroy(state.undoImage);
  state.undoImage = NULL;

  state.currentImage = temp;

  updateUIImage(self);

  return IUP_DEFAULT;
};
