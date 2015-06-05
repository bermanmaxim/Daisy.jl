# Daisy.jl
Julia/C wrapper for Daisy descriptor

Original Daisy author Engin Tola on [libdaisy](https://github.com/etola/libdaisy)

See libdaisy/licence.txt for info on Daisy license

Only Daisy "MODE 1" operation wrapped. Limited number of wrapped functions but the code is quite easy to extend.

The shared library is using my forked [libdaisy](libdaisy). The only difference of that fork is the definition of `desc->set_float_image(float* im, int h, int w)` that allows to set a floating point image directly without dividing by `255.` Modifying the wrapper to wrap around the builtin `desc->set_image` takes little effort.

## Build steps
```Shell
cd build
cmake ../
make
```
