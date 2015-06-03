
cd(dirname(Base.source_path()))
push!(LOAD_PATH, dirname(Base.source_path()))

# using Images, Color, FixedPointNumbers
# using ImageView
# using TestImages

# img = testimage("mandrill")
# g = convert(Image{Gray}, img)
# A = map(float32, data(g)); typeof(A)

A = [0.2 0.3 0.5 0.2
     0.7 0.2 0.4 0.8]

A = float32(A)

desc = Daisy()

verbose!(desc, 4)
image!(desc, A)
parameters!(desc, 14.)
compute!(desc)
@show desc[2,1]
# Impossible to delete descriptor for now: segmentation faults... The C wrapper yields
# double free or corruption (out): 0x00007fff70b1ba60
#    finalizer(desc, delete_daisy)
#    desc
# delete_daisy!(desc)

#delete_daisy!(desc::Daisy) = ccall( (:delete_daisy, daisyC), Void, (Ptr{Daisy_struct},), desc.ptr)
#free_daisy!(desc::Daisy) = ccall( (:free_daisy, daisyC), Void, (Ptr{Daisy_struct},), desc.ptr)



