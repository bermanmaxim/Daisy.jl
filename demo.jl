cd(dirname(Base.source_path()))
push!(LOAD_PATH, dirname(Base.source_path()))

using Images, Color, FixedPointNumbers
using ImageView
using TestImages

const daisyC = "build/libdaisyC.so"

img = testimage("mandrill")
g = convert(Image{Gray}, img)
A = map(float32, data(g)); typeof(A)

"""This maps the dummy C daisy struct"""
type Daisy_struct
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

function set_image!(desc::Daisy, Array{Float32, 2})

end
