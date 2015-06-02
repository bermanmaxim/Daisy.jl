cmake_minimum_required (VERSION 2.6)
project (Daisy_C)

include(ExternalProject)

ExternalProject_Add(project_libdaisy
   DOWNLOAD_COMMAND ""
   UPDATE_COMMAND ""
   SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libdaisy
   BUILD_IN_SOURCE 1
   CONFIGURE_COMMAND ""
   BUILD_COMMAND $(MAKE) library outdir=${CMAKE_BINARY_DIR}/libdaisy/
   INSTALL_COMMAND ""
   )

# INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/libdaisy/include)

# LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/res)

#add_executable(main main.cpp)
# add_subdirectory(${CMAKE_BINARY_DIR}/libdaisy/lib)
#TARGET_LINK_LIBRARIES(main ${CMAKE_BINARY_DIR}/libdaisy/lib/libdaisy.a)


add_library(libdaisy STATIC IMPORTED)
set_property(TARGET libdaisy PROPERTY IMPORTED_LOCATION ${CMAKE_BINARY_DIR}/libdaisy/lib/libdaisy.a)
add_dependencies(libdaisy project_libdaisy)

add_executable(daisy_c main.cpp)

INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/libdaisy/include)
TARGET_LINK_LIBRARIES(daisy_c libdaisy)