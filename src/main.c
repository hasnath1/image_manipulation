
#include <stdio.h>
#include <stdlib.h>

#include <iup.h>

#include "../include/utils.h"

int functionRunWhenClicked(Ihandle *self)
{
    IupMessage("Message", "This message appeared because you clicked the button");
    return 0;
}

int main(int argc, char **argv)
{
    IupOpen(&argc, &argv);
    Ihandle *window, *btn, *label, *vbox;

    label = IupLabel("Hello world!!!\n");
    btn = IupButton("Click me !!!", NULL);

    vbox = IupVbox(label, btn, NULL);

    IupSetCallback(btn, "ACTION", (Icallback)functionRunWhenClicked);

    window = IupDialog(vbox);

    IupSetAttribute(window, "TITLE", "Image Manipulation Software");
    IupSetAttribute(window, "SIZE", "600x400");

    IupShowXY(window, IUP_CENTER, IUP_CENTER);

    IupMainLoop();

    IupClose();
    return EXIT_SUCCESS;
}
