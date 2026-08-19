
#include <stdio.h>
#include <iup.h>

int main(int argc, char **argv) {
    IupOpen(&argc, &argv);

    Ihandle *label = IupLabel("IUP Setup Successful on Linux!");
    Ihandle *dlg = IupDialog(IupVbox(label, NULL));
    
    IupSetAttribute(dlg, "TITLE", "IUP Test");
    IupSetAttribute(dlg, "SIZE", "200x100");

    IupShowXY(dlg, IUP_CENTER, IUP_CENTER);
    IupMainLoop();

    IupClose();
    return 0;
}
