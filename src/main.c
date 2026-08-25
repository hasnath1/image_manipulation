#include <stdio.h>
#include <stdlib.h>

#include <iup.h>
#include <iupim.h>
#include <im.h>
#include <im_image.h>

#include "../include/custom.h"

int main(int argc, char **argv)
{
    IupOpen(&argc, &argv);
    setupGui();
    IupClose();
    return EXIT_SUCCESS;
}
