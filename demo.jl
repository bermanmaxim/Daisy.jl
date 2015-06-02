using Images, Color, FixedPointNumbers
using ImageView
using TestImages

img = testimage("mandrill")
convert(Image{Gray}, img)

