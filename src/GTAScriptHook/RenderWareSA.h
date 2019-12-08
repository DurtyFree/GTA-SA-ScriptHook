// some code taken from Multi Theft Auto, licensed under the GPLv3.

#pragma once

#ifndef RENDERWARE_H
#define RENDERWARE_H
using namespace System;

#include "RenderWare.h"

#include <iostream>
#include <map>
#include <list>
#include <utility> // make_pair

#ifndef __CGAMESA_COLMODELSA
	typedef void CColModelSAInterface;
#endif

/*****************************************************************************/
/** Renderware functions                                                    **/
/*****************************************************************************/

/* RenderWare macros */
#define RpGetFrame(__c)            ((RwFrame*)(((RwObject *)(__c))->parent))
#define RpSetFrame(__c,__f)        ((((RwObject *)(__c))->parent) = (void *)(__f))

/* RenderWare function defines */
typedef RpAtomic *				(__cdecl *RpAtomicCreate_t)						(void);
typedef RpAtomic *				(__cdecl *RpAtomicClone_t)						(RpAtomic * atomic);
typedef int					(__cdecl *RpAtomicDestroy_t)					(RpAtomic * atomic);
typedef RpAtomic *				(__cdecl *RpAtomicSetGeometry_t)				(RpAtomic * atomic, RpGeometry * geometry, unsigned int flags);
typedef RpAtomic *				(__cdecl *RpAtomicSetFrame_t)					(RpAtomic * atomic, RwFrame * frame);
typedef RpClump *				(__cdecl *RpClumpAddAtomic_t)					(RpClump * clump, RpAtomic * atomic);
typedef RpClump *				(__cdecl *RpClumpAddLight_t)					(RpClump * clump, RpLight * light);
typedef int					(__cdecl *RpClumpGetNumAtomics_t)				(RpClump * clump);
typedef RpClump *				(__cdecl *RpClumpRemoveAtomic_t)				(RpClump * clump, RpAtomic * atomic);
typedef RwFrame *				(__cdecl *RwFrameAddChild_t)					(RwFrame * parent, RwFrame * child);
typedef RwFrame *				(__cdecl *RwFrameRemoveChild_t)					(RwFrame * child);
typedef RwFrame *				(__cdecl *RwFrameForAllObjects_t)				(RwFrame * frame, void * callback, void * data);
typedef RwFrame *				(__cdecl *RwFrameTranslate_t)					(RwFrame * frame, const RwV3d * v, RwTransformOrder order);
typedef RwFrame *				(__cdecl *RwFrameScale_t)						(RwFrame * frame, const RwV3d * v, RwTransformOrder order);
typedef RwFrame *				(__cdecl *RwFrameCreate_t)						(void);
typedef	RwFrame *				(__cdecl *RwFrameSetIdentity_t)					(RwFrame * frame);
typedef RpGeometry *			(__cdecl *RpGeometryCreate_t)					(int numverts, int numtriangles, unsigned int format);
typedef const RpGeometry *		(__cdecl *RpGeometryTriangleSetVertexIndices_t)	(const RpGeometry * geo, RpTriangle * tri, unsigned short v1, unsigned short v2, unsigned short v3);
typedef RpGeometry *			(__cdecl *RpGeometryUnlock_t)					(RpGeometry * geo);
typedef RpGeometry *			(__cdecl *RpGeometryLock_t)						(RpGeometry * geo, int lockmode);
typedef RpGeometry *			(__cdecl *RpGeometryTransform_t)				(RpGeometry * geo, const RwMatrix * matrix);
typedef RpGeometry *			(__cdecl *RpGeometryTriangleSetMaterial_t)		(RpGeometry * geo, RpTriangle * tri, RpMaterial * mat);
typedef int					(__cdecl *RpGeometryDestroy_t)					(RpGeometry * geo);
typedef void *					(__cdecl *RwIm3DTransform_t)					(RwVertex *pVerts, unsigned int numVerts, RwMatrix *ltm, unsigned int flags);
typedef int					(__cdecl *RwIm3DRenderIndexedPrimitive_t)		(RwPrimitiveType primType, unsigned short *indices, int numIndices);
typedef int					(__cdecl *RwIm3DEnd_t)							(void);
typedef RpLight *				(__cdecl *RpLightCreate_t)						(int type);
typedef RpLight *				(__cdecl *RpLightSetRadius_t)					(RpLight * light, float radius);
typedef RpLight *				(__cdecl *RpLightSetColor_t)					(RpLight * light, const RwColorFloat * color);
typedef RwMatrix *				(__cdecl *RwMatrixCreate_t)						(void);
typedef RwMatrix *				(__cdecl *RwMatrixInvert_t)						(RwMatrix *dst, const RwMatrix *src);
typedef RwMatrix *				(__cdecl *RwMatrixTranslate_t)					(RwMatrix * matrix, const RwV3d * translation, RwTransformOrder order);
typedef RwMatrix *				(__cdecl *RwMatrixScale_t)						(RwMatrix * matrix, const RwV3d * translation, RwTransformOrder order);
typedef RpMaterial *			(__cdecl *RpMaterialCreate_t)					(void);
typedef int					(__cdecl *RpMaterialDestroy_t)					(RpMaterial * mat);
typedef RwTexDictionary *		(__cdecl *RwTexDictionarySetCurrent_t)			(RwTexDictionary * dict);
typedef const RwTexDictionary * (__cdecl *RwTexDictionaryForAllTextures_t)		(const RwTexDictionary * dict, void * callback, void * data);
typedef RwTexture *				(__cdecl *RwTexDictionaryAddTexture_t)			(RwTexDictionary * dict, RwTexture * texture);
typedef RwTexDictionary *		(__cdecl *RwTexDictionaryGetCurrent_t)			(void);
typedef RwTexture *				(__cdecl *RwTexDictionaryFindNamedTexture_t)	(RwTexDictionary * dict, const char* name);
typedef void					(__cdecl *RpPrtStdGlobalDataSetStreamEmbedded_t)(void * value);
typedef RpWorld *				(__cdecl *RpWorldAddAtomic_t)					(RpWorld * world, RpAtomic * atomic);
typedef RpWorld *				(__cdecl *RpWorldAddClump_t)					(RpWorld * world, RpClump * clump);
typedef RpWorld *				(__cdecl *RpWorldAddLight_t)					(RpWorld * world, RpLight * light);
typedef float					(__cdecl *RwV3dNormalize_t)						(RwV3d * out, const RwV3d * in);
typedef RwV3d *					(__cdecl *RwV3dTransformVector_t)				(RwV3d * out, const RwV3d * in, const RwMatrix * matrix);
typedef void					(__cdecl *_rwObjectHasFrameSetFrame_t)			(void *object, RwFrame *frame);
typedef RwCamera *				(__cdecl *RwCameraClone_t)						(RwCamera *camera);
typedef RpClump *				(__cdecl *RpClumpClone_t)						(RpClump *clone);
typedef int					(__cdecl *RwTexDictionaryDestroy_t)				(RwTexDictionary *txd);
typedef int					(__cdecl *RwTextureDestroy_t)					(RwTexture *texture);
typedef int					(__cdecl *RwStreamFindChunk_t)					(RwStream *stream, unsigned int type, unsigned int *lengthOut, unsigned int *versionOut);
typedef RpClump*				(__cdecl *RpClumpStreamRead_t)					(RwStream *stream);
typedef RwError*				(__cdecl *RwErrorGet_t)							(RwError *code);
typedef RwStream*				(__cdecl *RwStreamOpen_t)						(RwStreamType type, RwStreamMode mode, const void *pData);
typedef int					(__cdecl *RwStreamClose_t)						(RwStream *stream, void *pData);
typedef int					(__cdecl *RpClumpDestroy_t)						(RpClump *clump);
typedef RpClump*				(__cdecl *RpClumpForAllAtomics_t)				(RpClump *clump, void* callback, void* pData);
typedef RwTexDictionary*		(__cdecl *RwTexDictionaryStreamRead_t)			(RwStream *stream);
typedef RwRaster*				(__cdecl *RwRasterUnlock_t)						(RwRaster *raster);
typedef RwRaster*				(__cdecl *RwRasterLock_t)						(RwRaster *raster, unsigned char level, int lockmode);
typedef RwRaster*				(__cdecl *RwRasterCreate_t)						(int width, int height, int depth, int flags);
typedef RwTexture*				(__cdecl *RwTextureCreate_t)					(RwRaster *raster);

/*****************************************************************************/
/** Renderware function mappings                                            **/
/*****************************************************************************/

// US Versions
RwStreamFindChunk_t						RwStreamFindChunk						= (RwStreamFindChunk_t)						0xDEAD;
RpClumpStreamRead_t						RpClumpStreamRead						= (RpClumpStreamRead_t)						0xDEAD;
RwErrorGet_t							RwErrorGet								= (RwErrorGet_t)							0xDEAD;
RwStreamOpen_t							RwStreamOpen							= (RwStreamOpen_t)							0xDEAD;
RwStreamClose_t							RwStreamClose							= (RwStreamClose_t)							0xDEAD;
RpClumpDestroy_t						RpClumpDestroy							= (RpClumpDestroy_t)						0xDEAD;
RpClumpGetNumAtomics_t					RpClumpGetNumAtomics					= (RpClumpGetNumAtomics_t)					0xDEAD;
RwFrameTranslate_t						RwFrameTranslate						= (RwFrameTranslate_t)						0xDEAD;
RpClumpForAllAtomics_t					RpClumpForAllAtomics					= (RpClumpForAllAtomics_t)					0xDEAD;
RwFrameAddChild_t						RwFrameAddChild							= (RwFrameAddChild_t)						0xDEAD;
RpClumpAddAtomic_t						RpClumpAddAtomic						= (RpClumpAddAtomic_t)						0xDEAD;
RpAtomicSetFrame_t						RpAtomicSetFrame						= (RpAtomicSetFrame_t)						0xDEAD;
RwTexDictionaryStreamRead_t				RwTexDictionaryStreamRead				= (RwTexDictionaryStreamRead_t)				0xDEAD;
RwTexDictionaryGetCurrent_t				RwTexDictionaryGetCurrent				= (RwTexDictionaryGetCurrent_t)				0xDEAD;
RwTexDictionarySetCurrent_t				RwTexDictionarySetCurrent				= (RwTexDictionarySetCurrent_t)				0xDEAD;
RwTexDictionaryForAllTextures_t			RwTexDictionaryForAllTextures			= (RwTexDictionaryForAllTextures_t)			0xDEAD;
RwTexDictionaryAddTexture_t				RwTexDictionaryAddTexture				= (RwTexDictionaryAddTexture_t)				0xDEAD;
RpPrtStdGlobalDataSetStreamEmbedded_t	RpPrtStdGlobalDataSetStreamEmbedded		= (RpPrtStdGlobalDataSetStreamEmbedded_t)	0xDEAD;
RpClumpRemoveAtomic_t					RpClumpRemoveAtomic						= (RpClumpRemoveAtomic_t)					0xDEAD;
RpAtomicClone_t							RpAtomicClone							= (RpAtomicClone_t)							0xDEAD;
RwTexDictionaryFindNamedTexture_t		RwTexDictionaryFindNamedTexture			= (RwTexDictionaryFindNamedTexture_t)		0xDEAD;
RwFrameRemoveChild_t					RwFrameRemoveChild						= (RwFrameRemoveChild_t)					0xDEAD;
RwFrameForAllObjects_t					RwFrameForAllObjects					= (RwFrameForAllObjects_t)					0xDEAD;
RpAtomicDestroy_t						RpAtomicDestroy							= (RpAtomicDestroy_t)						0xDEAD;
RpAtomicSetGeometry_t					RpAtomicSetGeometry						= (RpAtomicSetGeometry_t)					0xDEAD;
RpWorldAddAtomic_t						RpWorldAddAtomic						= (RpWorldAddAtomic_t)						0xDEAD;
RpGeometryCreate_t						RpGeometryCreate						= (RpGeometryCreate_t)						0xDEAD;
RpGeometryTriangleSetVertexIndices_t	RpGeometryTriangleSetVertexIndices		= (RpGeometryTriangleSetVertexIndices_t)	0xDEAD;
RpGeometryUnlock_t						RpGeometryUnlock						= (RpGeometryUnlock_t)						0xDEAD;
RpGeometryLock_t						RpGeometryLock							= (RpGeometryLock_t)						0xDEAD;
RpAtomicCreate_t						RpAtomicCreate							= (RpAtomicCreate_t)						0xDEAD;
RwFrameCreate_t							RwFrameCreate							= (RwFrameCreate_t)							0xDEAD;
RpGeometryTransform_t					RpGeometryTransform						= (RpGeometryTransform_t)					0xDEAD;
RwFrameSetIdentity_t					RwFrameSetIdentity						= (RwFrameSetIdentity_t)					0xDEAD;
RwMatrixCreate_t						RwMatrixCreate							= (RwMatrixCreate_t)						0xDEAD;
RwMatrixTranslate_t						RwMatrixTranslate						= (RwMatrixTranslate_t)						0xDEAD;
RwMatrixScale_t							RwMatrixScale							= (RwMatrixScale_t)							0xDEAD;
RpGeometryTriangleSetMaterial_t			RpGeometryTriangleSetMaterial			= (RpGeometryTriangleSetMaterial_t)			0xDEAD;
RpMaterialCreate_t						RpMaterialCreate						= (RpMaterialCreate_t)						0xDEAD;
RpGeometryDestroy_t						RpGeometryDestroy						= (RpGeometryDestroy_t)						0xDEAD;
RpMaterialDestroy_t						RpMaterialDestroy						= (RpMaterialDestroy_t)						0xDEAD;
RwV3dNormalize_t						RwV3dNormalize							= (RwV3dNormalize_t)						0xDEAD;
RwIm3DTransform_t						RwIm3DTransform							= (RwIm3DTransform_t)						0xDEAD;
RwIm3DRenderIndexedPrimitive_t			RwIm3DRenderIndexedPrimitive			= (RwIm3DRenderIndexedPrimitive_t)			0xDEAD;
RwIm3DEnd_t								RwIm3DEnd								= (RwIm3DEnd_t)								0xDEAD;
RwMatrixInvert_t						RwMatrixInvert							= (RwMatrixInvert_t)						0xDEAD;
RpWorldAddClump_t						RpWorldAddClump							= (RpWorldAddClump_t)						0xDEAD;
RwFrameScale_t							RwFrameScale							= (RwFrameScale_t)							0xDEAD;
RwV3dTransformVector_t					RwV3dTransformVector					= (RwV3dTransformVector_t)					0xDEAD;
RpLightCreate_t							RpLightCreate							= (RpLightCreate_t)							0xDEAD;
RpClumpAddLight_t						RpClumpAddLight							= (RpClumpAddLight_t)						0xDEAD;
_rwObjectHasFrameSetFrame_t				_rwObjectHasFrameSetFrame				= (_rwObjectHasFrameSetFrame_t)				0xDEAD;
RpLightSetRadius_t						RpLightSetRadius						= (RpLightSetRadius_t)						0xDEAD;
RpWorldAddLight_t						RpWorldAddLight							= (RpWorldAddLight_t)						0xDEAD;
RpLightSetColor_t						RpLightSetColor							= (RpLightSetColor_t)						0xDEAD;
RwCameraClone_t							RwCameraClone							= (RwCameraClone_t)							0xDEAD;
RpClumpClone_t							RpClumpClone							= (RpClumpClone_t)							0xDEAD;
RwTexDictionaryDestroy_t				RwTexDictionaryDestroy					= (RwTexDictionaryDestroy_t)				0xDEAD;
RwTextureDestroy_t						RwTextureDestroy						= (RwTextureDestroy_t)						0xDEAD;
RwRasterUnlock_t						RwRasterUnlock							= (RwRasterUnlock_t)						0xDEAD;
RwRasterLock_t							RwRasterLock							= (RwRasterLock_t)							0xDEAD;
RwRasterCreate_t						RwRasterCreate							= (RwRasterCreate_t)						0xDEAD;
RwTextureCreate_t						RwTextureCreate							= (RwTextureCreate_t)						0xDEAD;

/*****************************************************************************/
/** GTA function definitions and mappings                                   **/
/*****************************************************************************/

typedef bool				(__cdecl *SetTextureDict_t)					(unsigned short id);
typedef bool				(__cdecl *LoadClumpFile_t)					(RwStream *stream, unsigned int id);		// (stream, model id)
typedef bool				(__cdecl *LoadModel_t)						(RwBuffer *filename, unsigned int id);		// (memory chunk, model id)
typedef void				(__cdecl *LoadCollisionModelVer3_t)			(unsigned char*, unsigned int, CColModelSAInterface*, const char*);	// buf, bufsize, ccolmodel&, keyname
typedef bool				(__cdecl *CTxdStore_LoadTxd_t)				(unsigned int id, RwStream *filename);
typedef void				(__cdecl *CTxdStore_RemoveTxd_t)			(unsigned int id);
typedef void				(__cdecl *CTxdStore_RemoveRef_t)			(unsigned int id);
typedef void				(__cdecl *CTxdStore_AddRef_t)				(unsigned int id);
typedef RwTexDictionary*	(__cdecl *CTxdStore_GetTxd_t)				(unsigned int id);
typedef RwTexture*			(__cdecl *CClothesBuilder_CopyTexture_t)	(RwTexture *texture);

SetTextureDict_t				SetTextureDict					= (SetTextureDict_t)				0xDEAD;
LoadClumpFile_t					LoadClumpFile					= (LoadClumpFile_t)					0xDEAD;
LoadModel_t						LoadModel						= (LoadModel_t)						0xDEAD;
LoadCollisionModelVer3_t		LoadCollisionModelVer3			= (LoadCollisionModelVer3_t)		0xDEAD;
CTxdStore_LoadTxd_t				CTxdStore_LoadTxd				= (CTxdStore_LoadTxd_t)				0xDEAD;
CTxdStore_GetTxd_t				CTxdStore_GetTxd				= (CTxdStore_GetTxd_t)				0xDEAD;
CTxdStore_RemoveTxd_t			CTxdStore_RemoveTxd				= (CTxdStore_RemoveTxd_t)			0xDEAD;
CTxdStore_RemoveRef_t			CTxdStore_RemoveRef				= (CTxdStore_RemoveRef_t)			0xDEAD;
CTxdStore_AddRef_t				CTxdStore_AddRef				= (CTxdStore_AddRef_t)				0xDEAD;
CClothesBuilder_CopyTexture_t	CClothesBuilder_CopyTexture		= (CClothesBuilder_CopyTexture_t)	0xDEAD;

#define			COL3_HEADER_SIZE	32

/*****************************************************************************/
/** Function inlines                                                        **/
/*****************************************************************************/

// Matrix copying
/*void RwFrameCopyMatrix ( RwFrame * dst, RwFrame * src ) {
	if ( dst == NULL || src == NULL ) return;
	memcpy(&dst->modelling,&src->modelling,sizeof(RwMatrix));
	memcpy(&dst->ltm,&src->ltm,sizeof(RwMatrix));
}

// Recursive RwFrame children searching function
RwFrame * RwFrameFindFrame ( RwFrame * parent, const char * name ) {
	RwFrame * ret = parent->child, * buf;
	while ( ret != NULL ) {
		// recurse into the child
		if ( ret->child != NULL ) {			
			buf = RwFrameFindFrame ( ret, name );
			if ( buf != NULL ) return buf;
		}

		// search through the children frames
		if ( strncmp ( &ret->szName[0], name, 16 ) == 0 ) {
			// found it
			return ret;
		}
		ret = ret->next;
	}
	return NULL;
}*/

#define		ARRAY_ModelLoaded				0x8E4CD0 // ##SA##

#define		FUNC_CStreaming__HasModelLoaded	0x4044C0

// CModelInfo/ARRAY_ModelInfo __thiscall to load/replace vehicle models
#define		FUNC_LoadVehicleModel			0x4C95C0

#define		DWORD_AtomicsReplacerModelID	0xB71840
#define		FUNC_AtomicsReplacer			0x537150

#define		ARRAY_ModelInfo					0xA9B0C8
#define		CLASS_CText						0xC1B340
#define		FUNC_CText_Get					0x6A0050
#define		FUNC_GetModelFlags				0x4044E0
#define		FUNC_GetBoundingBox				0x4082F0

#define		FUNC_IsBoatModel				0x4c5a70
#define		FUNC_IsCarModel					0x4c5aa0
#define		FUNC_IsTrainModel				0x4c5ad0
#define		FUNC_IsHeliModel				0x4c5b00
#define		FUNC_IsPlaneModel				0x4c5b30
#define		FUNC_IsBikeModel				0x4c5b60
#define		FUNC_IsFakePlaneModel			0x4c5b90	
#define		FUNC_IsMonsterTruckModel		0x4c5bc0		
#define		FUNC_IsQuadBikeModel			0x4c5bf0
#define		FUNC_IsBmxModel					0x4c5c20
#define		FUNC_IsTrailerModel				0x4c5c50
#define		FUNC_IsVehicleModelType			0x4c5c80

#define		FUNC_RequestModel				0x4087e0
#define		FUNC_RemoveModel				0x4089a0
#define		FUNC_LoadAllRequestedModels		0x40ea10

#define     FUNC_HasVehicleUpgradeLoaded    0x407820
#define     FUNC_RequestVehicleUpgrade      0x408C70

#define     FUNC_CVehicleModelInfo__GetNumRemaps        0x4C86B0

#define		FUNC_SetColModel				0x4C4BC0

	
class NativeTXD {
public:
	// Any SA textures that were replaced by custom ones (txd => texture list)
	static std::map < unsigned short, std::list < RwTexture* > > ms_ReplacedTXDTextures;
	// Any custom textures that were added (txd => texture list)
	static std::map < unsigned short, std::list < RwTexture* > > ms_AddedTXDTextures;
};

namespace GTA {
	class CBaseModelInfo_SA_VTBL
	{
		DWORD           Destructor;
		DWORD           AsAtomicModelInfoPtr;           // (void)
		DWORD           AsDamageAtomicModelInfoPtr;     // (void)
		DWORD           AsLodAtomicModelInfoPtr;        // (void)
		DWORD           GetModelType;                   // (void)           - Not defined in the base
		DWORD           GetTimeInfo;                    // (void)
		DWORD           Init;                           // (void)
		DWORD           Shutdown;                       // (void)
		DWORD           DeleteRwObject;                 // (void)           - Not defined in the base
		DWORD           GetRwModelType;                 // (void)           - Not defined in the base
		DWORD           CreateInstance_;                // (RwMatrixTag*)   - Not defined in the base
		DWORD           CreateInstance;                 // (void)           - Not defined in the base
		DWORD           SetAnimFile;                    // (char const*)
		DWORD           ConvertAnimFileIndex;           // (void)
		DWORD           GetAnimFileIndex;               // (void)
	};

	class CAtomicModelInfo_SA_VTBL: public CBaseModelInfo_SA_VTBL
	{
		DWORD           SetAtomic;                      // (RpAtomic*)
	};

	class CDamageAtomicModelInfo_SA_VTBL: public CAtomicModelInfo_SA_VTBL
	{
	};

	class CLodAtomicModelInfo_SA_VTBL: public CAtomicModelInfo_SA_VTBL
	{
	};

	class CTimeModelInfo_SA_VTBL: public CAtomicModelInfo_SA_VTBL
	{
	};

	class CLodTimeModelInfo_SA_VTBL: public CLodAtomicModelInfo_SA_VTBL
	{
	};

	class CClumpModelInfo_SA_VTBL: public CBaseModelInfo_SA_VTBL
	{
		DWORD           SetClump;                       // (RpClump*)
	};

	class CWeaponModelInfo_SA_VTBL: public CClumpModelInfo_SA_VTBL
	{
	};

	class CPedModelInfo_SA_VTBL: public CClumpModelInfo_SA_VTBL
	{
	};

	class CVehicleModelInfo_SA_VTBL: public CClumpModelInfo_SA_VTBL
	{
	};


	class CBaseModelInfoSAInterface
	{
	public:
		CBaseModelInfo_SA_VTBL* VFTBL;                      // +0

		unsigned long           ulHashKey;                  // +4   Generated by CKeyGen::GetUppercaseKey(char const *) called by CBaseModelInfo::SetModelName(char const *)
		unsigned short          usNumberOfRefs: 16;         // +8
		unsigned short          usTextureDictionary: 16;    // +10
		unsigned char           ucAlpha: 8;                 // +12

		unsigned char           ucNumOf2DEffects: 8;        // +13
		unsigned short          usUnknown: 16;              // +14     Something with 2d effects

		unsigned char           ucDynamicIndex: 8;          // +16

		unsigned char           dwUnknownFlag9: 1;          // +17
		unsigned char           dwUnknownFlag10: 1;
		unsigned char           dwUnknownFlag11: 1;
		unsigned char           dwUnknownFlag12: 1;
		unsigned char           dwUnknownFlag13: 1;
		unsigned char           dwUnknownFlag14: 1;
		unsigned char           dwUnknownFlag15: 1;
		unsigned char           dwUnknownFlag16: 1;

		// Flags used by CBaseModelInfo
		unsigned char           bDoWeOwnTheColModel: 1;     // +18
		unsigned char           bIsBackfaceCulled: 1;
		unsigned char           bIsLod: 1;
		unsigned char           bDontCastShadowsOn: 1;
		unsigned char           bDontWriteZBuffer: 1;
		unsigned char           bDrawAdditive: 1;
		unsigned char           bDrawLast: 1;
		unsigned char           bHasBeenPreRendered: 1;

		unsigned char           dwUnknownFlag25: 1;         // +19
		unsigned char           dwUnknownFlag26: 1;
		unsigned char           dwUnknownFlag27: 1;
		unsigned char           bSwaysInWind: 1;
		unsigned char           bCollisionWasStreamedWithModel: 1;  // CClumpModelInfo::SetCollisionWasStreamedWithModel(unsigned int)
		unsigned char           bDontCollideWithFlyer: 1;           // CAtomicModelInfo::SetDontCollideWithFlyer(unsigned int)
		unsigned char           bHasComplexHierarchy: 1;            // CClumpModelInfo::SetHasComplexHierarchy(unsigned int)
		unsigned char           bWetRoadReflection: 1;              // CAtomicModelInfo::SetWetRoadReflection(unsigned int)

		//CColModelSAInterface*   pColModel;                  // +20      CColModel: public CBoundingBox
		DWORD pColModel;

		float                   fLodDistanceUnscaled;       // +24      Scaled is this value multiplied with flt_B6F118
		RwObject*               pRwObject;                  // +28

		// CWeaponModelInfo:
		// +36 = Weapon info as int

		// CPedModelInfo:
		// +36 = Motion anim group (AssocGroupID, long)
		// +40 = Default ped type (long)
		// +44 = Default ped stats (ePedStats)
		// +48 = Can drive cars (byte)
		// +50 = Ped flags (short)
		// +52 = Hit col model (CColModel*)
		// +56 = First radio station
		// +57 = Second radio station
		// +58 = Race (byte)
		// +60 = Audio ped type (short)
		// +62 = First voice
		// +64 = Last voice
		// +66 = Next voice (short)

		// CVehicleModelInfo:
		// +36 = Custom plate material (RpMaterial*)
		// +49 = Custom plate design (byte)
		// +50 = Pointer to game name (const char*)
		// +60 = Vehicle type (enum, int)
		// +64 = Wheel scale (float). Front/rear?
		// +68 = Wheel scale (float). Front/rear?
		// +72 = Wheel model id
		// +74 = Vehicle handling ID (word)
		// +76 = Number of doors (byte)
		// +77 = Vehicle list (byte)
		// +78 = Vehicle flags (byte)
		// +79 = Wheel upgrade class (byte)
		// +80 = Number of times used (byte)
		// +82 = Vehicle freq (short)
		// +84 = Component rules mask (long)
		// +88 = Steer angle
		// +92 = Pointer to some class containing back seat position @ +60
		// +180 = Vehicle upgrade position descriptors array (32 bytes each)
		// +720 = Number of possible colors
		// +726 = Word array as referenced in CVehicleModelInfo::GetVehicleUpgrade(int)
		// +762 = Array of WORD containing something relative to paintjobs
		// +772 = Anim file index
	};

	CBaseModelInfoSAInterface** ppModelInfo = (CBaseModelInfoSAInterface**) ARRAY_ModelInfo;

	ref class RwTextureW {
	public:
		RwTexture* ptr;

		RwTextureW(RwTexture* base) { ptr = base; }
	};

	public ref class TXD {
	private:
		// This model contains our primary textures rather than copies
		unsigned short                  m_usMainModel;

		List<RwTextureW^>^ textures;
		List<unsigned short>^ imported;
	internal:

		static Dictionary<unsigned short, List<RwTextureW^>^>^ ms_AddedTXDTextures;
		static Dictionary<unsigned short, List<RwTextureW^>^>^ ms_ReplacedTXDTextures;

		static System::Drawing::Graphics^ LockBitmap(RwTexture* model);
		static System::Drawing::Bitmap^ LockRawBitmap(RwTexture* model);
		static void UnlockBitmap(RwTexture* model);
	public:
		bool							loaded;


		bool Load(String^ filename);
		bool LoadID(IntPtr pointer);
		bool Import(unsigned short modelID);

		List<String^>^ TextureNames();

		static TXD() {
			ms_AddedTXDTextures = gcnew Dictionary<unsigned short, List<RwTextureW^>^>();
			ms_ReplacedTXDTextures = gcnew Dictionary<unsigned short, List<RwTextureW^>^>();
		}

		static System::Drawing::Graphics^ LockBitmap(IntPtr texPtr);
		static void UnlockBitmap(IntPtr texPtr);

		static System::Drawing::Bitmap^ LockRawBitmap(IntPtr texPtr);
		//static void UnlockBitmap(IntPtr texPtr, String^ name);

		static System::Drawing::Graphics^ LockBitmap(unsigned short model, String^ name);
		static void UnlockBitmap(unsigned short model, String^ name);

		TXD(String^ filename) { textures = gcnew List<RwTextureW^>(); imported = gcnew List<unsigned short>(); Load(filename); }
		TXD(IntPtr rwTexDictionary) { LoadID(rwTexDictionary); }
	};

	public ref class RenderWare {
	public:
		static RenderWare();

		static void Init() { }

		static IntPtr CreateTexture32(int width, int height);

		//static void ImportTXD ( RWTextureDictionary^ source, unsigned short usModelID );
	internal:
		static RwTexture * GetTexFromModel ( unsigned short model, String^ name );

		static RwTexDictionary * ReadTXD ( String^ txdFile );

		static void ModelInfoTXDAddTextures ( List<RwTextureW^>^ textures, unsigned short usModelID, bool bMakeCopy, bool bAddRef );

		static void UnloadTXD( RwTexDictionary* txd );
	};
}
#endif