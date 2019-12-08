// some code taken from Multi Theft Auto, licensed under the GPLv3.

#include "stdafx.h"

#if GTA_SA
#include "LegacyCrap.h"

#define FUNC_PlaceMarker		0x725120

#pragma unmanaged
#pragma warning(disable: 4409)

#define FUNC_CVisiblityPlugins_SetClumpAlpha 0x732B00

void SetClumpAlpha ( RpClump * pClump, int iAlpha )
{
    DWORD dwFunc = FUNC_CVisiblityPlugins_SetClumpAlpha;
    _asm
    {
        push    iAlpha
        push    pClump
        call    dwFunc
        add     esp, 0x8
    }
};

#define FUNC_CMatrix__ConvertFromEulerAngles 0x59AA40

void ConvertFromEulerAngles(CMatrix_Padded* mat, float fX, float fY, float fZ) {
	DWORD dwFunc = FUNC_CMatrix__ConvertFromEulerAngles;
	int iUnknown = 21;
	_asm
	{
		push    iUnknown
		push    fZ
		push    fY
		push    fX
		mov     ecx, mat
		call    dwFunc
	}
};

#define FUNC_Add											0x563220 // ##SA##
#define FUNC_Remove											0x563280 // ##SA##

void WorldAdd ( GTA::CEntitySAInterface * entityInterface )
{
	//DEBUG_TRACE("VOID CWorldSA::Add ( CEntitySAInterface * entityInterface )");
	DWORD dwFunction = FUNC_Add;
	_asm
	{
		push	entityInterface
		call	dwFunction
		add		esp, 4
	}
}

void WorldRemove ( GTA::CEntitySAInterface * entityInterface )
{
	//DEBUG_TRACE("VOID CWorldSA::Remove ( CEntitySAInterface * entityInterface )");
	DWORD dwFunction = FUNC_Remove;
	_asm
	{
		push	entityInterface
		call	dwFunction
		add		esp, 4

	/*	mov		ecx, entityInterface
		mov		esi, [ecx]
		push	1
		call	dword ptr [esi+8]*/				
	}
};

#define FUNC_SetOrientation									0x439A80

void SetObjectOrientation ( GTA::CEntitySAInterface* m_pInterface, float fX, float fY, float fZ )
{
    //DEBUG_TRACE("VOID CEntitySA::SetOrientation ( float fX, float fY, float fZ )");
	WorldRemove ( m_pInterface );
	DWORD dwThis = (DWORD) m_pInterface;
	DWORD dwFunc = FUNC_SetOrientation;
	_asm
	{
        // ChrML: I've switched the X and Z at this level because that's how the real rotation
        //        is. GTA has kinda swapped them in this function.

		push	fZ
		push	fY
		push	fX
		mov		ecx, dwThis
		call	dwFunc
	}

	dwFunc = 0x446F90;
	_asm
	{
		mov		ecx, dwThis
		call	dwFunc
	}

	dwFunc = 0x532B00;
	_asm
	{
		mov		ecx, dwThis
		call	dwFunc
	}

	WorldAdd ( m_pInterface );
};

DWORD PlaceMarker(bool bZCheck, float fPulseFraction, BYTE r, BYTE g, BYTE b, BYTE a, FLOAT fSize, CVector vecPosition, DWORD dwType, DWORD Identifier) {
	DWORD dwFunc = FUNC_PlaceMarker;
	DWORD dwReturn = 0;
	_asm
	{
		push	bZCheck		// zCheck  ##SA##
		push	0			// normalZ ##SA##
		push	0			// normalY ##SA##
		push	0			// normalX ##SA##
		push	0			// rotate rate
		push	fPulseFraction		// pulse
		push	0		    // period
		push	a			// alpha
		push	b			// blue
		push	g			// green
		push	r			// red
		push	fSize		// size
		push	vecPosition	// position
		push	dwType		// type
		push	Identifier	// identifier
		call	dwFunc
		mov		dwReturn, eax
		add		esp, 0x3C
	}

	return dwReturn;
}

void _nativeOverridePeds(int* peds) {
	DWORD dwFunc = 0x40BDA0;
	DWORD dwPtr = (DWORD)peds;

	__asm {
		push dwPtr
		call dwFunc
		add esp, 4
	}
}

void _playFrontendAudio(int audioID) {
	DWORD dwFunc = 0x506EA0;
	DWORD dwClass = 0xB6BC90;
	float fl1 = 1.0f;
	int zero = 0;

	__asm {
		push fl1
		push zero
		push audioID
		mov ecx, dwClass
		call dwFunc
	}
}

#pragma warning(default: 4409)
#pragma managed

namespace GTA {
	void NativeFunctions::PlayFrontendAudio(int audioID) {
		_playFrontendAudio(audioID);
	}

	void NativeFunctions::OverridePedSpawn(cli::array<int>^ peds) {
		int pedids[8];

		for (int i = 0; i < 8; i++) {
			if (i < peds->Length) {
				pedids[i] = peds[i];
			} else {
				pedids[i] = -1;
			}
		}

		_nativeOverridePeds(&pedids[0]);
	}

	static GTA3DMarkers::GTA3DMarkers() {
		Markers = gcnew array<GTA3DMarker^>(32);

		for(int i = 0;i< 32;i++)
		{
			Markers[i] = gcnew GTA3DMarker((C3DMarkerSAInterface *)(0xC7DD58 + i * sizeof(C3DMarkerSAInterface)));
		}
	}

	void GTA3DMarker::SetZRotation(int degrees) {
			float radians = degrees * (3.1415926535897932384626433832795f / 180.0f);

			CMatrix_Padded mat = internalInterface->m_mat;

			ConvertFromEulerAngles(&mat, 0.0f, 0.0f, radians);

			//mat.vRoll.fZ = z;
			internalInterface->m_mat = mat;
		}

	void GTA3DMarker::SetAlpha(int nA) {
 {
			/*ColorRGBA color;
			memcpy(&color, &internalInterface->rwColour, sizeof(ColorRGBA));
			color.A = A;
			memcpy(&internalInterface->rwColour, &color, sizeof(RGBA));*/

			unsigned char R, G, B, A;
			GetColor ( R, G, B, A );

			A = (unsigned char)nA;

			SetColor (R, G, B, A);

			SetClumpAlpha(internalInterface->m_pRwObject, A);
		}
	}

	array<GTA3DMarker^>^ GTA3DMarkers::GetMarkers() {
		return Markers;
	}

	static GTAPickups::GTAPickups() {
		Pickups = gcnew array<GTAPickup^>(620);

		for(int i = 0;i< 620;i++)
		{
			Pickups[i] = gcnew GTAPickup((CPickupSAInterface *)(0x9788C0 + i * sizeof(CPickupSAInterface)));
		}
	}

	array<GTAPickup^>^ GTAPickups::GetPickups() {
		return Pickups;
	}

	GTA3DMarker^ GTA3DMarkers::GetFreeMarker() {
		for each (GTA3DMarker^ marker in Markers) {
			if (!marker->Exists) {
				return marker;
			}
		}

		return nullptr;
	}

	float NativeFunctions::GetCameraFOV() {
		CCameraSAInterface* cam = (CCameraSAInterface*)0xB6F028;
		return (cam->Cams[0].FOV/* / 0.01745329238f*/);
	}

	void NativeFunctions::SetCameraFOV(float value) {
		CCameraSAInterface* cam = (CCameraSAInterface*)0xB6F028;

		cam->Cams[0].FOV = (value/* * 0.01745329238f*/);
	}

	SVector^ NativeFunctions::GetScreenCoords(SVector^ world) {
		CVector in = CVector(world->pX, world->pY, world->pZ);
		CVector out;
		float x, y;

		WorldCoords2ScreenCoords(&in, &out, &x, &y, 0, 0);

		return gcnew SVector(x, y, 0.0f);
	}
}

#endif
