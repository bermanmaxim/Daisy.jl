using Docile
module JuDaisy

  export Daisy, verbose!, image!, parameters!, compute!, normalize!, getindex, descriptor_size

  push!(LOAD_PATH, dirname(Base.source_path()))
  const daisyC = "build/libdaisyC.so"

  """Maps the dummy C daisy struct"""
  immutable Daisy_struct
  end

  """Interface type to the descriptor"""
  type Daisy
    ptr::Ptr{Daisy_struct}
    descriptor_size::Cint
    function Daisy()
      ptr = ccall( (:new_daisy, daisyC), Ptr{Daisy_struct}, () )
      desc = new(ptr)
      delete_daisy!(desc::Daisy) = ccall( (:delete_daisy, daisyC), Void, (Ptr{Daisy_struct},), desc.ptr)
      finalizer(desc, delete_daisy!)
      desc
    end
  end

  """Set verbose level v=1,2,3,4"""
  function verbose!(desc::Daisy, v)
    ccall( (:daisy_verbose, daisyC), Void, (Ptr{Daisy_struct}, Csize_t), desc.ptr, v)
  end

  """Set image. im can be of types that can be casted to float.
  Expects values between 0. and 1."""
  function image!(desc::Daisy, im::Array{Float32, 2})
    ccall( (:daisy_set_float_image, daisyC), Void, (Ptr{Daisy_struct}, Ptr{Float32}, Cint, Cint), desc.ptr, im, size(im, 2), size(im, 1))
  end

  """Set parameters and initialize for Mode 1"""
  function parameters!(desc::Daisy, rad::Float64 = 15., radq::Int = 3, thq::Int = 8, histq::Int = 8)
    ccall( (:daisy_set_parameters, daisyC), Void, (Ptr{Daisy_struct}, Cdouble, Cint, Cint, Cint), desc.ptr, rad, radq, thq, histq)
    desc.descriptor_size = descriptor_size(desc)
    ccall( (:daisy_initialize_single_descriptor_mode, daisyC), Void, (Ptr{Daisy_struct},), desc.ptr)
  end

  """Compute all descriptors"""
  function compute!(desc::Daisy)
    ccall( (:daisy_compute_descriptors, daisyC), Void, (Ptr{Daisy_struct},), desc.ptr)
  end

  function normalize!(desc::Daisy)
    ccall( (:daisy_normalize_descriptors, daisyC), Void, (Ptr{Daisy_struct},), desc.ptr)
  end

  function descriptor_size(desc::Daisy)
    ccall( (:daisy_descriptor_size, daisyC), Cint, (Ptr{Daisy_struct},), desc.ptr)
  end


  import Base.getindex
  """To meet Julia convention x and y start at 1
  no bounds checking !"""
  function getindex(desc::Daisy, y::Int, x::Int)
    thor::Ptr{Cfloat} = ccall( (:daisy_get_descriptor, daisyC), Ptr{Cfloat}, (Ptr{Daisy_struct}, Cint, Cint), desc.ptr, y-1, x-1)
    pointer_to_array(thor, (desc.descriptor_size,), false)
  end



end

