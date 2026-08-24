
#include <stdio.h>
#include <stdlib.h>
#include <iup.h>
#include <im.h>
#include <iupim.h>

#include "../include/utils.h"

int main(int argc, char **argv)
{
    IupOpen(&argc, &argv);
    //    IupMainLoop();

    printf("%d\n", add(20, 40));

    IupClose();
    return 0;
}
