
cd(dirname(Base.source_path()))
push!(LOAD_PATH, dirname(Base.source_path()))

workspace()
reload("JuDaisy")
using JuDaisy

A = [0.2 0.3 0.5 0.2
     0.7 0.2 0.4 0.8]

A = float32(A)

desc = Daisy()

image!(desc, A)
parameters!(desc, 14.)
compute!(desc)
desc[2,2]

descriptor_size(desc)
# Impossible to delete descriptor for now: segmentation faults... The C wrapper yields
# double free or corruption (out): 0x00007fff70b1ba60
#    finalizer(desc, delete_daisy)
#    desc
# delete_daisy!(desc)

#delete_daisy!(desc::Daisy) = ccall( (:delete_daisy, daisyC), Void, (Ptr{Daisy_struct},), desc.ptr)
#free_daisy!(desc::Daisy) = ccall( (:free_daisy, daisyC), Void, (Ptr{Daisy_struct},), desc.ptr)



