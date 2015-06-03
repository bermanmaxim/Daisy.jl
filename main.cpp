#include <iostream>
#include "daisy/daisy.h"

using namespace std;

int main(int argc, char* argv[]) {
        daisy* desc = new daisy();
        float im[] = {1., 3., 5., 2., 7., 2.};
        desc->verbose(4);
        desc->set_image(im, 2, 3);
        delete desc;
}


