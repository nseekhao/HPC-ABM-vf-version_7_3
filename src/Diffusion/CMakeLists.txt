
set(DIFFUSION_SRC "Diffuser.cpp")
file(GLOB DIFFUSION_HELPER1_SRC "Diffusion.cu")
file(GLOB DIFFUSION_HELPER2_SRC "convolutionFFT.cu")
file(GLOB DIFFUSION_HELPER3_SRC "DiffusionHelper.cpp")

set(lib_type SHARED)

set(CUDA_SAMPLES_INC "/usr/local/cuda/cuda-7.0/samples/common/inc")
cuda_include_directories(${CUDA_SAMPLES_INC})

set(LIB_NAME "Diffusion")

cuda_add_library(${LIB_NAME}
  ${lib_type}
  ${DIFFUSION_SRC}
  ${DIFFUSION_HELPER1_SRC}
  ${DIFFUSION_HELPER2_SRC}
  ${DIFFUSION_HELPER3_SRC}
  #${USR_DIFFUSION_SRC}
  #OPTIONS -DSTUFF="blah blah"
  #RELEASE -DNDEBUG
  #DEBUG -g -DDEBUG
)

# Added by Nuttiiya
find_package(OpenMP)
if (OPENMP_FOUND)
  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  add_definitions(-D_OMP)
endif()

target_link_libraries(${LIB_NAME} World)



