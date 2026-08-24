
#include <stdio.h>
#include <stdlib.h>
#include <iup.h>
#include <im.h>
#include <iupim.h>

int main(int argc, char **argv)
{
    IupOpen(&argc, &argv);

    Ihandle *vbox;
    Ihandle *image = IupLoadImage("./images/sample_640×426.bmp");

    vbox = IupVbox(image, NULL);
    Ihandle *window = IupDialog(vbox);

    IupSetAttribute(window, "TITLE", "IMAGE MANIPULATION SOFTWARE");
    IupSetAttribute(window, "SIZE", "600x400");

    IupShowXY(window, IUP_CENTER, IUP_CENTER);

    IupMainLoop();

    IupClose();
    return 0;
}
