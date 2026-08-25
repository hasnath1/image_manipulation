#include <stdint.h>

#ifndef MY_CUSTOM_HEADER
#define MY_CUSTOM_HEADER

// GUI Setup Declarations
void setupGui();

// Control/Callback Function Declarations

int open_clb(Ihandle *self);
int ext_clb(Ihandle *self);

// Image struct

typedef struct
{
  int width;
  int height;
  uint8_t *data;
} Image;

// Application State

typedef struct
{
  char *currentImageFile;
  Image *currentImage;
  Image *undoImage;
  Ihandle *imageWidget;
} AppState;

// Globally declare the appstate

extern AppState state;

#endif