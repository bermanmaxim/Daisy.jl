#include "daisy/daisy.h"
#include "daisy_C.h"

extern "C" {

        daisy* new_daisy() {
                return new daisy();
        }

        void daisy_set_image(daisy* desc, float* im, int h, int w) {
                desc->set_image(im, h, w);
        }

        void daisy_verbose(daisy* desc, size_t v){
                desc->verbose(v);
        }

        void daisy_set_parameters(daisy* desc, double rad, int radq, int thq, int histq) {
                desc->set_parameters(rad, radq, thq, histq);
        }

        void daisy_initialize_single_descriptor_mode(daisy* desc){
                desc->initialize_single_descriptor_mode();
        }

        void daisy_compute_descriptors(daisy* desc){
                desc->compute_descriptors();
        }

        void daisy_normalize_descriptors(daisy* desc){
                desc->normalize_descriptors();
        }

        void daisy_get_descriptor(daisy* desc, int y, int x, float* thor){
                desc->get_descriptor(y, x, thor);
        }

        void delete_daisy(daisy* desc) {
                delete desc;
        }
}