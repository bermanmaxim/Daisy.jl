// C wrapper for Daisy Descriptor
// Original Daisy author Engin Tola
// See libdaisy/licence.txt for info on Daisy license
//
// Only Daisy "MODE 1" operation wrapped

#ifndef __DAISY_C_H
#define __DAISY_C_H

#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct daisy daisy;

daisy* new_daisy();

void daisy_set_image(daisy* desc, float* im, int h, int w);

void daisy_verbose(daisy* desc, size_t v);

void daisy_set_parameters(daisy* desc, double rad, int radq, int thq, int histq );

void daisy_initialize_single_descriptor_mode(daisy* desc);

void daisy_compute_descriptors(daisy* desc);

void daisy_normalize_descriptors(daisy* desc);

float* daisy_get_descriptor(daisy* desc, int y, int x);

int daisy_descriptor_size(daisy* desc);

void delete_daisy(daisy* desc);

#ifdef __cplusplus
}
#endif
#endif