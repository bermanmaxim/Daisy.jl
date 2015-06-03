#include "daisy_C.h"
#include <stdio.h>

int main(int argc, char* argv[]) {
        struct daisy* desc = new_daisy();
        float im[] = {1., 3., 5., 2., 7., 2.};
        daisy_verbose(desc, 4);
        daisy_set_image(desc, im, 2, 3);
//        delete_daisy(desc);
        free_daisy(desc);
}