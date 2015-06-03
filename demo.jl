
cd(dirname(Base.source_path()))
push!(LOAD_PATH, dirname(Base.source_path()))

# using Images, Color, FixedPointNumbers
# using ImageView
# using TestImages

const daisyC = "build/libdaisyC.so"

# img = testimage("mandrill")
# g = convert(Image{Gray}, img)
# A = map(float32, data(g)); typeof(A)

"""This maps the dummy C daisy struct"""
immutable Daisy_struct
end

"""This is an interface type to the descriptor"""
type Daisy
  ptr::Ptr{Daisy_struct}

  function Daisy()
    ptr = ccall( (:new_daisy, daisyC), Ptr{Daisy_struct}, () )
    desc = new(ptr)
    delete_daisy(desc::Daisy) = ccall( (:delete_daisy, daisyC), Void, (Ptr{Daisy_struct},), desc.ptr)
    finalizer(desc, delete_daisy)
    desc
  end
end

function verbose!(desc::Daisy, v)
  ccall( (:daisy_verbose, daisyC), Void, (Ptr{Daisy_struct}, Csize_t), desc.ptr, v)
end

function image!(desc::Daisy, im::Array{Float32, 2})
  ccall( (:daisy_set_image, daisyC), Void, (Ptr{Daisy_struct}, Ptr{Float32}, Cint, Cint), desc.ptr, im, size(im, 1), size(im, 2))
end

A = [1.2 3.3 1.5 2.2
     7.7 2.2 4.4 7.8]

A = float32(A)

desc = Daisy()

verbose!(desc, 4)
image!(desc, A)

