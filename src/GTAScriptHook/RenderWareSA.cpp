// some code taken from Multi Theft Auto, licensed under the GPLv3.

#include "Stdafx.h"
#include "Log.h"
#include "Pool.h"

#if GTA_SA | GTA_III
#include "RenderWareSA.h"
#include "GameVersion.h"

static RwTexture* AddAllTexturesCB (RwTexture * texture, RwTexDictionary * data ) {
	RwTexDictionaryAddTexture ( data, texture );
	return texture;
}

#pragma unmanaged
BOOL IsModelLoaded ( DWORD m_dwModelID )
{
	//DEBUG_TRACE("BOOL CModelInfoSA::IsLoaded ( )");
	//return (BOOL)*(BYTE *)(ARRAY_ModelLoaded + 20*dwModelID);
	DWORD dwFunc = FUNC_CStreaming__HasModelLoaded;
	DWORD ModelID = m_dwModelID;

	BOOL bReturn = 0;
	_asm
	{
		push	ModelID
		call	dwFunc
		movzx	eax, al
		mov		bReturn, eax
		pop		eax
	}

    //m_pInterface = ppModelInfo [ m_dwModelID ];
	return bReturn;
}

void LoadAllRequestedModels ( )
{
	//DEBUG_TRACE("VOID CModelInfoSA::LoadAllRequestedModels ( )");

	DWORD dwFunction = FUNC_LoadAllRequestedModels;
    DWORD dwSlot = 0;
    //if ( m_dwModelID >= 400 && m_dwModelID < 615 )
        //dwSlot = 1;
	_asm
	{
		push	dwSlot
		call	dwFunction
		add		esp, 4
	}
}

VOID CLoadModel( DWORD m_dwModelID, bool bAndLoad, bool bWaitForLoad )
{
	//DEBUG_TRACE("VOID CModelInfoSA::Request( BOOL bAndLoad, BOOL bWaitForLoad )");
	// don't bother loading it if it already is
    if ( IsModelLoaded (m_dwModelID) )
        return;

    /*if ( m_dwModelID <= 288 && m_dwModelID != 7 && !pGame->GetModelInfo ( 7 )->IsLoaded () )
    {
        // Skin 7 must be loaded in order for other skins to work. No, really. (#4010)
        pGame->GetModelInfo ( 7 )->Request ( bAndLoad, false );
    }*/

	DWORD dwFunction = FUNC_RequestModel;
	DWORD ModelID = m_dwModelID;
	//DWORD dwChannel = ( m_dwModelID < 400 ) ? 0 : 6;
    DWORD dwChannel = 6;
	_asm
	{
		push	dwChannel
		push	ModelID
		call	dwFunction
		add		esp, 8
	}

	int iTimeToWait = 50;

	if(bAndLoad)
	{
		LoadAllRequestedModels();
		
		if(bWaitForLoad)
		{
			while(!IsModelLoaded(m_dwModelID) && iTimeToWait != 0)
			{
				iTimeToWait--;
				Sleep(10);
			}
		}
	}
}

#pragma managed

bool ListContainsNamedTexture ( List<GTA::RwTextureW^>^ list, const char* szTexName )
{
    /*std::list < RwTexture* >::iterator it;
    for ( it = list.begin (); it != list.end (); it++ )
    {*/
	for each (GTA::RwTextureW^ itt in list) {
		RwTexture* it = itt->ptr;

        if ( !_stricmp ( szTexName, (it)->name ) )
            return true;
    }
    return false;
}

void         RwTexDictionaryRemoveTexture( RwTexDictionary* pTXD, RwTexture* pTex ) {
	if ( pTex->txd != pTXD )
        return;

    pTex->TXDList.next->prev = pTex->TXDList.prev;
    pTex->TXDList.prev->next = pTex->TXDList.next;
    pTex->txd = NULL;
}

namespace GTA {
	IntPtr RenderWare::CreateTexture32(int width, int height) {
		RwRaster* raster = RwRasterCreate(width, height, 32, rwRASTERFORMAT8888 | 0x4); // rwRASTERTYPETEXTURE
		RwTexture* texture = RwTextureCreate(raster);

		return IntPtr(texture);
	}

	bool TXD::Import ( unsigned short usModelID )
	{
		// Have we got textures and haven't already imported into this model?
		if ( textures->Count > 0 && !imported->Contains(usModelID) )
		{
			// Grab the lists of replaced and added textures for the model's TXD
			unsigned short usTxdID = 0;

			if (ppModelInfo[usModelID]) {
				usTxdID = ppModelInfo[usModelID]->usTextureDictionary;
			}
			//unsigned short usTxdID = 0;
			/*std::list < RwTexture* >& replacedTextures = NativeTXD::ms_ReplacedTXDTextures.insert (
				make_pair ( usTxdID, std::list < RwTexture* > () )
			).first->second;
			std::list < RwTexture* >& addedTextures = NativeTXD::ms_AddedTXDTextures.insert (
				make_pair ( usTxdID, std::list < RwTexture* > () )
			).first->second;*/

			if (!ms_ReplacedTXDTextures->ContainsKey(usTxdID)) {
				ms_ReplacedTXDTextures->Add(usTxdID, gcnew List<RwTextureW^>);
			}

			if (!ms_AddedTXDTextures->ContainsKey(usTxdID)) {
				ms_AddedTXDTextures->Add(usTxdID, gcnew List<RwTextureW^>);
			}

			// If we already used our main textures in a model, we need to make copies now
			// for this new model.
			bool bMakeCopy = ( m_usMainModel != 0xFFFF );

			// Add the textures.
			RenderWare::ModelInfoTXDAddTextures ( textures, usModelID, bMakeCopy, true );

			// Add the id to the list over which models we've imported ourselves into.
			imported->Add(usModelID);
			if ( m_usMainModel == 0xFFFF )
				m_usMainModel = usModelID;

			return true;
		}

		return false;
	}

	bool TXD::LoadID(IntPtr usTxdId) {
		//SetTextureDict ( usTxdId );

		//RwTexDictionary* pTXD = CTxdStore_GetTxd ( usTxdId );

		RwTexDictionary* pTXD = (RwTexDictionary*)usTxdId.ToPointer();

		loaded = false;

		if (pTXD) {
			RwListEntry* pSentinel = &pTXD->textures.root;
			RwListEntry* pTexLink = pSentinel->next;
			while ( pTexLink != pSentinel )
			{
				RwTexture* pTex = (RwTexture *)( (BYTE *)pTexLink - offsetof(RwTexture, TXDList) );
				//m_Textures.push_back ( pTex );
				textures->Add(gcnew RwTextureW(pTex));
				pTex->txd = NULL;
				pTex->flags = 0x1102;       // Enable filtering (otherwise textures are pixely)

				pTexLink = pTexLink->next;
			}

			// Make the txd forget it has any textures and destroy it
			pTXD->textures.root.next = &pTXD->textures.root;
			pTXD->textures.root.prev = &pTXD->textures.root;
			RenderWare::UnloadTXD ( pTXD );
			pTXD = NULL;

			// We succeeded if we got any textures
			return textures->Count > 0;

			loaded = true;
		}

		return false;
	}

	List<String^>^ TXD::TextureNames() {
		List<String^>^ retval = gcnew List<String^>();

		for each (RwTextureW^ tex in textures) {
			retval->Add(gcnew String(tex->ptr->name));
		}

		return retval;
	}

	bool TXD::Load(String^ filename) {
		if (textures->Count == 0) {
			RwTexDictionary* pTXD = RenderWare::ReadTXD(filename);

			if (pTXD) {
				RwListEntry* pSentinel = &pTXD->textures.root;
				RwListEntry* pTexLink = pSentinel->next;
				while ( pTexLink != pSentinel )
				{
					RwTexture* pTex = (RwTexture *)( (BYTE *)pTexLink - offsetof(RwTexture, TXDList) );
					//m_Textures.push_back ( pTex );
					textures->Add(gcnew RwTextureW(pTex));
					pTex->txd = NULL;
					pTex->flags = 0x1102;       // Enable filtering (otherwise textures are pixely)

					pTexLink = pTexLink->next;
				}

				// Make the txd forget it has any textures and destroy it
				pTXD->textures.root.next = &pTXD->textures.root;
				pTXD->textures.root.prev = &pTXD->textures.root;
				RenderWare::UnloadTXD ( pTXD );
				pTXD = NULL;

				// We succeeded if we got any textures
				return textures->Count > 0;
			}
		}

		return false;
	}

	Drawing::Graphics^ TXD::LockBitmap(IntPtr texPtr) {
		RenderWare::Init();

		return LockBitmap((RwTexture*)texPtr.ToPointer());
	}

	void TXD::UnlockBitmap(IntPtr texPtr) {
		UnlockBitmap((RwTexture*)texPtr.ToPointer());
	}

	Drawing::Graphics^ TXD::LockBitmap(unsigned short model, String^ name) {
		RwTexture* tex = RenderWare::GetTexFromModel(model, name);

		if (tex == NULL) {
			Log::Warn("Texture does not exist?");
			return nullptr;
		}

		return LockBitmap(tex);
	}

	Drawing::Bitmap^ TXD::LockRawBitmap(RwTexture* tex) {
		RwRaster* raster = tex->raster;
		void* buffer = RwRasterLock ( raster, 0, RASTER_LOCK_WRITE );

		IntPtr ptr = IntPtr(buffer);

		RwRasterFormat format = (RwRasterFormat)(RwRasterGetFormat(raster) & 0x0f00); // format
		Drawing::Imaging::PixelFormat fmt = Drawing::Imaging::PixelFormat::Format16bppRgb565;
		
		switch (format) {
			case rwRASTERFORMAT565:
				fmt = Drawing::Imaging::PixelFormat::Format16bppRgb565;
				break;
			case rwRASTERFORMAT1555:
				fmt = Drawing::Imaging::PixelFormat::Format16bppArgb1555;
				break;
			case rwRASTERFORMAT8888:
				fmt = Drawing::Imaging::PixelFormat::Format32bppArgb;
				break;
			case rwRASTERFORMAT888:
				if (raster->depth == 32) {
					fmt = Drawing::Imaging::PixelFormat::Format32bppArgb;
				} else {
					fmt = Drawing::Imaging::PixelFormat::Format24bppRgb;
				}
				break;
			case rwRASTERFORMAT4444:
				return nullptr;
			default:
				Log::Warn("Unknown raster format: " + ((int)format).ToString());
				return nullptr;
		}

		Drawing::Bitmap^ bmp = gcnew Drawing::Bitmap(raster->width, raster->height, raster->stride, fmt, ptr);

		return bmp;
	}

	Drawing::Bitmap^ TXD::LockRawBitmap(IntPtr tex) {
		RenderWare::Init();

		return LockRawBitmap((RwTexture*)tex.ToPointer());
	}

	Drawing::Graphics^ TXD::LockBitmap(RwTexture* tex) {
		return Drawing::Graphics::FromImage(LockRawBitmap(tex));
	}

	void TXD::UnlockBitmap(unsigned short model, String^ name) {
		/*for each (RwTextureW^ tex in textures) {
			if (gcnew String(tex->ptr->name) == name) {*/

		RwTexture* tex = RenderWare::GetTexFromModel(model, name);

		UnlockBitmap(tex);
	}

	void TXD::UnlockBitmap(RwTexture* tex) {
		RwRaster* raster = tex->raster;
		RwRasterUnlock ( raster );
	}

	RwTexture * RenderWare::GetTexFromModel(unsigned short usModelID, String^ name) {
		// Get the CModelInfo's TXD ID
		unsigned short usTxdId = ((CBaseModelInfoSAInterface**)ARRAY_ModelInfo)[usModelID]->usTextureDictionary;

		// Get the TXD corresponding to this ID
		SetTextureDict ( usTxdId );

		RwTexDictionary* pTXD = CTxdStore_GetTxd ( usTxdId );
		if ( true )
		{
			if ( !pTXD )
			{
				//pGame->GetModelInfo ( usModelID )->Request ( true, true );
				CLoadModel(usModelID, true, true);
				CTxdStore_AddRef ( usTxdId );
				( (void (__cdecl *)(unsigned short))FUNC_RemoveModel )( usModelID );
				pTXD = CTxdStore_GetTxd ( usTxdId );
			}
			else
			{
				CTxdStore_AddRef ( usTxdId );
			}
		}

		if (pTXD) {
			return RwTexDictionaryFindNamedTexture ( pTXD, (char*)Runtime::InteropServices::Marshal::StringToHGlobalAnsi(name).ToPointer() );
		}

		return NULL;
	}

	// Adds texture into the TXD of a model, eventually making a copy of each texture first 
	void RenderWare::ModelInfoTXDAddTextures ( List<RwTextureW^>^ textures, unsigned short usModelID, bool bMakeCopy, bool bAddRef )
	{
		// Get the CModelInfo's TXD ID
		unsigned short usTxdId = ((CBaseModelInfoSAInterface**)ARRAY_ModelInfo)[usModelID]->usTextureDictionary;

		// Get the TXD corresponding to this ID
		SetTextureDict ( usTxdId );

		RwTexDictionary* pTXD = CTxdStore_GetTxd ( usTxdId );
		if ( bAddRef )
		{
			if ( !pTXD )
			{
				//pGame->GetModelInfo ( usModelID )->Request ( true, true );
				CLoadModel(usModelID, true, true);
				CTxdStore_AddRef ( usTxdId );
				( (void (__cdecl *)(unsigned short))FUNC_RemoveModel )( usModelID );
				pTXD = CTxdStore_GetTxd ( usTxdId );
			}
			else
			{
				CTxdStore_AddRef ( usTxdId );
			}
		}

		if ( pTXD )
		{
			for each (RwTextureW^ itt in textures)
			{
				RwTexture* it = itt->ptr;

				// Does a texture by this name already exist?
				RwTexture* pExistingTexture = RwTexDictionaryFindNamedTexture ( pTXD, (it)->name );
				if ( pExistingTexture )
				{
					// Is it a custom texture?
					if ( ( ListContainsNamedTexture ( TXD::ms_AddedTXDTextures[usTxdId], (it)->name ) ) ||
						 ( ListContainsNamedTexture ( TXD::ms_ReplacedTXDTextures[usTxdId], (it)->name ) ) )
					{
						continue;
					}

					// If not, we can replace it
					RwTexDictionaryRemoveTexture ( pTXD, pExistingTexture );
					/*if ( pReplacedTextures )
						pReplacedTextures->push_back ( pExistingTexture );*/

					TXD::ms_ReplacedTXDTextures[usTxdId]->Add(gcnew RwTextureW(pExistingTexture));
				}
				else
				{
					/*if ( pAddedTextures )
						pAddedTextures->push_back ( it );*/

					TXD::ms_AddedTXDTextures[usTxdId]->Add(itt);
				}

				RwTexture* pTex = it;

				if ( bMakeCopy )
				{
					// Reuse the given texture's raster
					RwTexture* pNewTex = RwTextureCreate ( pTex->raster );

					// Copy over additional properties
					memcpy ( &pNewTex->name, &pTex->name, RW_TEXTURE_NAME_LENGTH );
					memcpy ( &pNewTex->mask, &pTex->mask, RW_TEXTURE_NAME_LENGTH );
					pNewTex->flags = pTex->flags;
	                
					pTex = pNewTex;
				}

				// Add the texture
				RwTexDictionaryAddTexture ( pTXD, pTex );
			}
		}
	}

	void RenderWare::UnloadTXD ( RwTexDictionary * pTXD )
	{
		if ( pTXD )
			RwTexDictionaryDestroy ( pTXD );
	}

	RwTexDictionary* RenderWare::ReadTXD ( String^ txdFile ) {
//	g_pCore->GetConsole ()->Printf ( "Reading TXD file %s", szTXD );
		const char* szTXD = (const char*) Runtime::InteropServices::Marshal::StringToHGlobalAnsi(txdFile).ToPointer();

		// open the stream
		RwStream * streamTexture = RwStreamOpen ( STREAM_TYPE_FILENAME, STREAM_MODE_READ, szTXD );

		// check for errors
		if ( streamTexture == NULL )
			return NULL;

		// TXD header id: 0x16
		// find our txd chunk (dff loads textures, so correct loading order is: txd, dff)
		if ( RwStreamFindChunk ( streamTexture, 0x16, NULL, NULL ) == false )
			return NULL;

		// read the texture dictionary from our model (txd)
		RwTexDictionary *pTex = RwTexDictionaryStreamRead ( streamTexture );

		// close the stream
		RwStreamClose ( streamTexture, NULL );

		//return pTex;
		//RWTextureDictionary^ tex = gcnew RWTextureDictionary(pTex);

		return pTex;
	}

/*	void RenderWare::ImportTXD ( RWTextureDictionary^ source, unsigned short usModelID ) {
		RwTexDictionary * pSource = source->txd;

		// CModelInfo stores some kind of TXD id at +Ah
		DWORD *pPool = ( DWORD* ) ARRAY_ModelInfo;
		unsigned short usTXDId = *( ( unsigned short * ) ( pPool[usModelID] + 0xA ) );

		// Preload the model, just to be sure that all the textures are present
		//pGame->GetModelInfo ( usModelID )->Request ( TRUE, TRUE );

		SetTextureDict ( usTXDId );

		// Get the Txd associated with the CTXDStore
		RwTexDictionary * pTXD = CTxdStore_GetTxd ( usTXDId );
		//assert ( pTXD != NULL );

	//	RwTexDictionarySetCurrent ( pTxd );
		if ( pTXD ) {
			//RwTexDictionaryForAllTextures ( pTXD, ( void* ) DebugCB, NULL );
			//RwTexDictionaryForAllTextures ( pSource, ( void* ) DebugCB, NULL );
			RwTexDictionaryForAllTextures ( pSource, ( void* ) AddAllTexturesCB, pTXD );
		}

		// Add a reference to the TXD to make sure it doesn't get destroyed
		CTxdStore_AddRef ( usTXDId );
	}*/

#if GTA_III
	RwTexDictionary* __cdecl GetTxd (unsigned int id) {
		return (RwTexDictionary*)Pool::TXD->GetAtIndex(id).ToPointer();
	}
#endif

	static RenderWare::RenderWare() {
		switch ( GameVersion::Region )
		{
        // VERSION 1.0 EU ADDRESSES
#if GTA_III
		default:
			// 1.0
			RwStreamFindChunk					= (RwStreamFindChunk_t)						0x005AA540;
			RwStreamOpen						= (RwStreamOpen_t)							0x0053AFE0;
			RwStreamClose						= (RwStreamClose_t)							0x0053AF10;
			RwTexDictionaryStreamRead		    = (RwTexDictionaryStreamRead_t)				0x005924A0; 
			RwTexDictionaryAddTexture		    = (RwTexDictionaryAddTexture_t)				0x005A7490;
			RwTexDictionaryFindNamedTexture		= (RwTexDictionaryFindNamedTexture_t)		0x005A74D0;
            RwTextureDestroy					= (RwTextureDestroy_t)						0x005A7330;
            RwRasterUnlock						= (RwRasterUnlock_t)						0x005AD6F0;
            RwRasterLock						= (RwRasterLock_t)							0x005AD9D0; 
            RwRasterCreate						= (RwRasterCreate_t)						0x005AD930;
            RwTextureCreate						= (RwTextureCreate_t)						0x005A72D0;

			SetTextureDict					    = (SetTextureDict_t)				        0x005278C0;
            CTxdStore_LoadTxd				    = (CTxdStore_LoadTxd_t)				        0x00527700;
            CTxdStore_GetTxd				    = (CTxdStore_GetTxd_t)				        &GetTxd;
            CTxdStore_RemoveTxd				    = (CTxdStore_RemoveTxd_t)			        0x00527870;
            CTxdStore_RemoveRef				    = (CTxdStore_RemoveRef_t)			        0x00527970;
            CTxdStore_AddRef				    = (CTxdStore_AddRef_t)				        0x00527930; 
			break;
#endif
#if GTA_SA
        case 'E':
        {
            RwStreamFindChunk					= (RwStreamFindChunk_t)						0x007ED310;
            RpClumpStreamRead					= (RpClumpStreamRead_t)						0x0074B470;
            RwErrorGet							= (RwErrorGet_t)							0x008088C0;
            RwStreamOpen						= (RwStreamOpen_t)							0x007ECF30;
            RwStreamClose						= (RwStreamClose_t)							0x007ECE60;
            RpClumpDestroy						= (RpClumpDestroy_t)						0x0074A360;
            RpClumpGetNumAtomics				= (RpClumpGetNumAtomics_t)					0x00749930;
            RwFrameTranslate					= (RwFrameTranslate_t)						0x007F0E70;
            RpClumpForAllAtomics				= (RpClumpForAllAtomics_t)					0x00749BC0;
            RwFrameAddChild						= (RwFrameAddChild_t)						0x007F0B40;
            RpClumpAddAtomic					= (RpClumpAddAtomic_t)						0x0074A4E0;
            RpAtomicSetFrame					= (RpAtomicSetFrame_t)						0x0074BF70;
            RwTexDictionaryStreamRead		    = (RwTexDictionaryStreamRead_t)				0x00804C70; 
            RwTexDictionaryGetCurrent			= (RwTexDictionaryGetCurrent_t)				0x007F3AD0;
            RwTexDictionarySetCurrent		    = (RwTexDictionarySetCurrent_t)				0x007F3AB0;
            RwTexDictionaryForAllTextures	    = (RwTexDictionaryForAllTextures_t)			0x007F3770;
            RwTexDictionaryAddTexture		    = (RwTexDictionaryAddTexture_t)				0x007F39C0;
            RpPrtStdGlobalDataSetStreamEmbedded = (RpPrtStdGlobalDataSetStreamEmbedded_t)	0x0041B350;
            RpClumpRemoveAtomic					= (RpClumpRemoveAtomic_t)					0x0074A510;
            RpAtomicClone						= (RpAtomicClone_t)							0x00749EB0; 
            RwTexDictionaryFindNamedTexture		= (RwTexDictionaryFindNamedTexture_t)		0x007F3A30;
            RwFrameRemoveChild					= (RwFrameRemoveChild_t)					0x007F0D10; 
            RwFrameForAllObjects				= (RwFrameForAllObjects_t)					0x007F1240; 
            RpAtomicDestroy						= (RpAtomicDestroy_t)						0x00749E10; 
            RpAtomicSetGeometry					= (RpAtomicSetGeometry_t)					0x00749D90;
            RpWorldAddAtomic					= (RpWorldAddAtomic_t)						0x00750FE0;
            RpGeometryCreate					= (RpGeometryCreate_t)						0x0074CAE0;
            RpGeometryTriangleSetVertexIndices	= (RpGeometryTriangleSetVertexIndices_t)	0x0074C6E0;
            RpGeometryUnlock					= (RpGeometryUnlock_t)						0x0074C850;
            RpGeometryLock						= (RpGeometryLock_t)						0x0074C820;
            RpAtomicCreate						= (RpAtomicCreate_t)						0x00749CA0;
            RwFrameCreate						= (RwFrameCreate_t)							0x007F0450;
            RpGeometryTransform					= (RpGeometryTransform_t)					0x0074C030;
            RwFrameSetIdentity					= (RwFrameSetIdentity_t)					0x007F10F0;
            RwMatrixCreate						= (RwMatrixCreate_t)						0x007F2A90; 
            RwMatrixTranslate					= (RwMatrixTranslate_t)						0x007F2490;
            RwMatrixScale						= (RwMatrixScale_t)							0x007F2300;
            RpGeometryTriangleSetMaterial		= (RpGeometryTriangleSetMaterial_t)			0x0074C710;
            RpMaterialCreate					= (RpMaterialCreate_t)						0x0074D9E0;
            RpGeometryDestroy					= (RpGeometryDestroy_t)						0x0074CD10;
            RpMaterialDestroy					= (RpMaterialDestroy_t)						0x0074DA70;
            RwV3dNormalize						= (RwV3dNormalize_t)						0x007ED9F0;
            RwIm3DTransform						= (RwIm3DTransform_t)						0x007EF490; 
            RwIm3DRenderIndexedPrimitive		= (RwIm3DRenderIndexedPrimitive_t)			0x007EF590;
            RwIm3DEnd							= (RwIm3DEnd_t)								0x007EF560;
            RwMatrixInvert						= (RwMatrixInvert_t)						0x007F20B0;
            RpWorldAddClump						= (RpWorldAddClump_t)						0x00751350;
            RwFrameScale						= (RwFrameScale_t)							0x007F0F10;
            RwV3dTransformVector				= (RwV3dTransformVector_t)					0x007EDE00;
            RpLightCreate						= (RpLightCreate_t)							0x00752160;
            RpClumpAddLight						= (RpClumpAddLight_t)						0x0074A540;
            _rwObjectHasFrameSetFrame			= (_rwObjectHasFrameSetFrame_t)				0x00804F30;
            RpLightSetRadius					= (RpLightSetRadius_t)						0x00751AC0;
            RpWorldAddLight						= (RpWorldAddLight_t)						0x00751960;
            RpLightSetColor						= (RpLightSetColor_t)						0x00751AE0;
            RwCameraClone						= (RwCameraClone_t)							0x007EF3F0;
            RpClumpClone						= (RpClumpClone_t)							0x00749FC0;
            RwTexDictionaryDestroy				= (RwTexDictionaryDestroy_t)				0x007F36E0;
            RwTextureDestroy					= (RwTextureDestroy_t)						0x007F3860;
            RwRasterUnlock						= (RwRasterUnlock_t)						0x007FAF00;
            RwRasterLock						= (RwRasterLock_t)							0x007FB310; 
            RwRasterCreate						= (RwRasterCreate_t)						0x007FB270;
            RwTextureCreate						= (RwTextureCreate_t)						0x007F3800;

            SetTextureDict					    = (SetTextureDict_t)				        0x007319C0;
            LoadClumpFile					    = (LoadClumpFile_t)					        0x005371F0;
            LoadModel						    = (LoadModel_t)						        0x0040C6B0;
            LoadCollisionModelVer3			    = (LoadCollisionModelVer3_t)		        0x00537CE0;
            CTxdStore_LoadTxd				    = (CTxdStore_LoadTxd_t)				        0x00731DD0;
            CTxdStore_GetTxd				    = (CTxdStore_GetTxd_t)				        0x00408340;
            CTxdStore_RemoveTxd				    = (CTxdStore_RemoveTxd_t)			        0x00731E90;
            CTxdStore_RemoveRef				    = (CTxdStore_RemoveRef_t)			        0x00731A30;
            CTxdStore_AddRef				    = (CTxdStore_AddRef_t)				        0x00731A00; 
            CClothesBuilder_CopyTexture		    = (CClothesBuilder_CopyTexture_t)	        0x005A5730;

            break;
        }    

        // VERSION 1.0 US ADDRESSES
        case 'U':
        {
            RwStreamFindChunk					= (RwStreamFindChunk_t)						0x007ED2D0;
            RpClumpStreamRead					= (RpClumpStreamRead_t)						0x0074B420;
            RwErrorGet							= (RwErrorGet_t)							0x00808880;
            RwStreamOpen						= (RwStreamOpen_t)							0x007ECEF0;
            RwStreamClose						= (RwStreamClose_t)							0x007ECE20;
            RpClumpDestroy						= (RpClumpDestroy_t)						0x0074A310;
            RpClumpGetNumAtomics				= (RpClumpGetNumAtomics_t)					0x007498E0;
            RwFrameTranslate					= (RwFrameTranslate_t)						0x007F0E30;
            RpClumpForAllAtomics				= (RpClumpForAllAtomics_t)					0x00749B70;
            RwFrameAddChild						= (RwFrameAddChild_t)						0x007F0B00;
            RpClumpAddAtomic					= (RpClumpAddAtomic_t)						0x0074A490;
            RpAtomicSetFrame					= (RpAtomicSetFrame_t)						0x0074BF20;
            RwTexDictionaryStreamRead		    = (RwTexDictionaryStreamRead_t)				0x00804C30;
            RwTexDictionaryGetCurrent			= (RwTexDictionaryGetCurrent_t)				0x007F3A90;
            RwTexDictionarySetCurrent		    = (RwTexDictionarySetCurrent_t)				0x007F3A70;
            RwTexDictionaryForAllTextures	    = (RwTexDictionaryForAllTextures_t)			0x007F3730;
            RwTexDictionaryAddTexture		    = (RwTexDictionaryAddTexture_t)				0x007F3980;
            RpPrtStdGlobalDataSetStreamEmbedded = (RpPrtStdGlobalDataSetStreamEmbedded_t)	0x0041B350;
            RpClumpRemoveAtomic					= (RpClumpRemoveAtomic_t)					0x0074A4C0;
            RpAtomicClone						= (RpAtomicClone_t)							0x00749E60;
            RwTexDictionaryFindNamedTexture		= (RwTexDictionaryFindNamedTexture_t)		0x007F39F0;
            RwFrameRemoveChild					= (RwFrameRemoveChild_t)					0x007F0CD0;
            RwFrameForAllObjects				= (RwFrameForAllObjects_t)					0x007F1200;
            RpAtomicDestroy						= (RpAtomicDestroy_t)						0x00749DC0;
            RpAtomicSetGeometry					= (RpAtomicSetGeometry_t)					0x00749D40;
            RpWorldAddAtomic					= (RpWorldAddAtomic_t)						0x00750F90;
            RpGeometryCreate					= (RpGeometryCreate_t)						0x0074CA90;
            RpGeometryTriangleSetVertexIndices	= (RpGeometryTriangleSetVertexIndices_t)	0x0074C690;
            RpGeometryUnlock					= (RpGeometryUnlock_t)						0x0074C800;
            RpGeometryLock						= (RpGeometryLock_t)						0x0074C7D0;
            RpAtomicCreate						= (RpAtomicCreate_t)						0x00749C50;
            RwFrameCreate						= (RwFrameCreate_t)							0x007F0410;
            RpGeometryTransform					= (RpGeometryTransform_t)					0x0074BFE0;
            RwFrameSetIdentity					= (RwFrameSetIdentity_t)					0x007F10B0;
            RwMatrixCreate						= (RwMatrixCreate_t)						0x007F2A50;
            RwMatrixTranslate					= (RwMatrixTranslate_t)						0x007F2450;
            RwMatrixScale						= (RwMatrixScale_t)							0x007F22C0;
            RpGeometryTriangleSetMaterial		= (RpGeometryTriangleSetMaterial_t)			0x0074C6C0;
            RpMaterialCreate					= (RpMaterialCreate_t)						0x0074D990;
            RpGeometryDestroy					= (RpGeometryDestroy_t)						0x0074CCC0;
            RpMaterialDestroy					= (RpMaterialDestroy_t)						0x0074DA20;
            RwV3dNormalize						= (RwV3dNormalize_t)						0x007ED9B0;
            RwIm3DTransform						= (RwIm3DTransform_t)						0x007EF450;
            RwIm3DRenderIndexedPrimitive		= (RwIm3DRenderIndexedPrimitive_t)			0x007EF550;
            RwIm3DEnd							= (RwIm3DEnd_t)								0x007EF520;
            RwMatrixInvert						= (RwMatrixInvert_t)						0x007F2070;
            RpWorldAddClump						= (RpWorldAddClump_t)						0x00751300;
            RwFrameScale						= (RwFrameScale_t)							0x007F0ED0;
            RwV3dTransformVector				= (RwV3dTransformVector_t)					0x007EDDC0;
            RpLightCreate						= (RpLightCreate_t)							0x00752110;
            RpClumpAddLight						= (RpClumpAddLight_t)						0x0074A4F0;
            _rwObjectHasFrameSetFrame			= (_rwObjectHasFrameSetFrame_t)				0x00804EF0;
            RpLightSetRadius					= (RpLightSetRadius_t)						0x00751A70;
            RpWorldAddLight						= (RpWorldAddLight_t)						0x00751910;
            RpLightSetColor						= (RpLightSetColor_t)						0x00751A90;
            RwCameraClone						= (RwCameraClone_t)							0x007EF3B0;
            RpClumpClone						= (RpClumpClone_t)							0x00749F70;
            RwTexDictionaryDestroy				= (RwTexDictionaryDestroy_t)				0x007F36A0;
            RwTextureDestroy					= (RwTextureDestroy_t)						0x007F3820;
            RwRasterUnlock						= (RwRasterUnlock_t)						0x007FAEC0;
            RwRasterLock						= (RwRasterLock_t)							0x007FB2D0;
            RwRasterCreate						= (RwRasterCreate_t)						0x007FB230;
            RwTextureCreate						= (RwTextureCreate_t)						0x007F37C0;

            SetTextureDict					    = (SetTextureDict_t)				        0x007319C0;
            LoadClumpFile					    = (LoadClumpFile_t)					        0x005371F0;
            LoadModel						    = (LoadModel_t)						        0x0040C6B0;
            LoadCollisionModelVer3			    = (LoadCollisionModelVer3_t)		        0x00537CE0;
            CTxdStore_LoadTxd				    = (CTxdStore_LoadTxd_t)				        0x00731DD0;
            CTxdStore_GetTxd				    = (CTxdStore_GetTxd_t)				        0x00408340;
            CTxdStore_RemoveTxd				    = (CTxdStore_RemoveTxd_t)			        0x00731E90;
            CTxdStore_RemoveRef				    = (CTxdStore_RemoveRef_t)			        0x00731A30;
            CTxdStore_AddRef				    = (CTxdStore_AddRef_t)				        0x00731A00;
            CClothesBuilder_CopyTexture		    = (CClothesBuilder_CopyTexture_t)	        0x005A5730;

            break;
        }
#endif
		}
	}
}
#endif