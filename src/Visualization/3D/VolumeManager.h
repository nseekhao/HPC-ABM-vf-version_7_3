//
//  VolumeManager.h
//
//  Created by Nuttiiya Seekhao on 9/07/17.
//  Copyright (c) 2017 Nuttiiya Seekhao. All rights reserved.
//

#ifndef Volume_Manager_h
#define Volume_Manager_h

//#include "common_vis.h"
//#include "draw_util.h"
#include "../../common.h"
#include "../../enums.h"

// CUDA Runtime, Interop, and includes
#include <cuda_runtime.h>
#include <cuda_gl_interop.h>
#include <vector_types.h>
#include <vector_functions.h>
#include <driver_functions.h>

// CUDA utilities
#include <helper_cuda.h>
#include <helper_cuda_gl.h>

// Helper functions
#include <helper_cuda.h>
#include <helper_functions.h>
#include <helper_timer.h>

typedef unsigned int uint;
typedef unsigned char uchar;

#define MAX_EPSILON_ERROR 5.00f
#define THRESHOLD         0.30f

//typedef unsigned char VolumeType;
typedef float VolumeType;

#ifndef MAX
#define MAX(a,b) ((a > b) ? a : b)
#endif

extern "C" void setTextureFilterMode(bool bLinearFilter);
extern "C" void bufferECMmap(cudaMemcpy3DParms copyParams);
extern "C" void initCuda(void *h_volume, cudaExtent volumeSize, cudaMemcpy3DParms &copyParams, ecm_i ecmType);

extern "C" void printCpyParams(cudaMemcpy3DParms cp);

#ifdef AVEP

extern "C" void initCudaAVEP(
		void *h_volume,
		cudaExtent volumeSize,
		cudaMemcpy3DParms &copyParams,
		cudaMemcpy3DParms &svCopyParams,
		ecm_i ecmType);

#ifdef AVEP_INC
extern "C"
void bufferECMmapAVEP(
		cudaMemcpy3DParms copyParams,
		cudaMemcpy3DParms svCopyParams,
		ecm_i ecmType,
		int incRound,
		float incFactor);
#else
extern "C"
void bufferECMmapAVEP(
		cudaMemcpy3DParms copyParams,
		cudaMemcpy3DParms svCopyParams,
		ecm_i ecmType);
#endif	// AVEP_INC
#endif	// AVEP



extern "C" void freeCudaBuffers();
extern "C" void render_kernel(dim3 gridSize, dim3 blockSize, uint *d_output, uint imageW, uint imageH,
                              float density, float brightness, float transferOffset, float transferScale);
extern "C" void render_kernel_dim(dim3 gridSize, dim3 blockSize, uint *d_output, uint nx, uint ny, uint nz,
															    uint imageW, uint imageH,
                                  float density, float brightness, float transferOffset, float transferScale,
                                  int ecmChemType,
                                  bool isChem);
extern "C" void render_sp_kernel_dim(dim3 gridSize, dim3 blockSize, uint *d_output, uint nx, uint ny, uint nz,
																	uint imageW, uint imageH,
																	float density, float brightness, float transferOffset, float transferScale,
																	int gpu_id);
#ifdef ECV_SAMPLE_CHEM_TEST
extern "C"
void render_test_kernel_dim(dim3 gridSize, dim3 blockSize, uint *d_output, uint nx, uint ny, uint nz,
																	uint imageW, uint imageH,
																	float density, float brightness, float transferOffset, float transferScale,
																	int chemType, bool isHigh);
#endif	// ECV_SAMPLE_CHEM_TEST


extern "C" void copyInvViewMatrix(float *invViewMatrix, size_t sizeofMatrix);


class VolumeManager
{
public:


    /*
     * Description: VolumeManager constructor.
     *
     * Return: void
     *
     * Parameters: width    -- Width  (x dimension) of the volume (world) in patches
     *             height   -- Height (y dimension) of the volume (world) in patches
     *             depth    -- Depth  (z dimension) of the volume (world) in patches
     */
    template<typename T>
	VolumeManager(
	        const int width,
	        const int height,
	        const int depth,
	        T* volumeDataPtr);

    /*
     * Description: VolumeManager destructor.
     *
     * Return: void
     *
     * Parameters: void
     */
	~VolumeManager();

    /*
     * Description: Read content change, amplify and superimpose on scaled initial value
     *              and write to volume buffer
     *
     * Return: void
     *
     * Parameters: ecm          -- Pointer to normalized ECM  map of size vol.x*vol.y*vol.z floats
     *             dEcm         -- Pointer to normalized dECM map of size vol.x*vol.y*vol.z floats
     */
	void preprocessECMdata(const float *ecm, const float *dEcm);

private:
	// Volume dimension width. height and depth
	int x;
	int y;
	int z;

	float *volumeBuffer;

};


#endif
