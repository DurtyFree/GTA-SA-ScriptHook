/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto v1.0
*               (Shared logic for modifications)
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        mods/shared_logic/CClientRadarArea.cpp
*  PURPOSE:     Radar area entity class
*  DEVELOPERS:  Christian Myhre Lundheim <>
*               Oliver Brown <>
*               Ed Lyons <eai@opencoding.net>
*               Jax <>
*               Chris McArthur <>
*               Stanislav Bobrov <lil_toady@hotmail.com>
*               Alberto Alonso <rydencillo@gmail.com>
*
*****************************************************************************/

#include "stdafx.h"
#ifdef GTA_SA
#include "CClientRadarAreas.h"
#include "Hooking.h"
#include "ScriptDomain.h"

bool installed = false;

namespace GTA {

StompHook radarAreaHook;

ref class PulseRadarWorker {
internal:
	static void PulseRadars() {
		if (GTA::CClientRadarArea::m_pRadarAreaManager == nullptr) {
			GTA::CClientRadarArea::m_pRadarAreaManager = gcnew GTA::CClientRadarAreaManager();
		} else {
			GTA::CClientRadarArea::m_pRadarAreaManager->DoPulse();
		}
	}
};

void PulseRadars() {
	ScriptDomain::_scriptDomain->DoCallBack(gcnew CrossAppDomainDelegate(&PulseRadarWorker::PulseRadars));
}

void _declspec(naked) HOOK_CRadar__DrawRadarGangOverlay()
{
    _asm
    {
        pushad
    }

	PulseRadars();

    _asm
    {
        popad
        retn
    }
}

void RadarHook::Install() {
	if (!installed) {
		radarAreaHook.initialize("aaaaaa", 6, (PBYTE)0x586650);
		radarAreaHook.installHook(HOOK_CRadar__DrawRadarGangOverlay, true, true);

		installed = true;
	}
}

#pragma unmanaged
	void DrawAreaOnRadar(float fX1, float fY1, float fX2, float fY2, DWORD abgr )
	{
		CRect myRect;
		myRect.fX1 = fX1;
		myRect.fY1 = fY1;
		myRect.fX2 = fX2;
		myRect.fY2 = fY2;
		DWORD dwFunc = FUNC_DrawAreaOnRadar;
		_asm
		{
			push    eax

			push    0
			lea     eax, abgr
			push    eax
			lea     eax, myRect
			push    eax
			call    dwFunc
			add     esp, 12

			pop     eax
		}
	}
#pragma managed

void DrawRadarEventArgs::DrawArea(float x1, float y1, float x2, float y2, Drawing::Color color) {
	DrawAreaOnRadar(x1, y1, x2, y2, (((((color.A)&0xff)<<24)|(((color.B)&0xff)<<16)|(((color.G)&0xff)<<8)|((color.R)&0xff))));
}

CClientRadarArea::CClientRadarArea ()
{
    // Init
    //m_pManager = pManager;
	if (m_pRadarAreaManager == nullptr) {
		m_pRadarAreaManager = gcnew CClientRadarAreaManager();
	}
    SetColor ( 0xFFFFFFFF );
    m_bFlashing = false;
    m_ulFlashCycleStart = 0;
    m_bStreamedIn = true;

    //SetTypeName ( "radararea" );

    // Make sure we're visible/invisible according to our dimension
    RelateDimension ( m_pRadarAreaManager->GetDimension () );

    // Add us to the manager's list
    m_pRadarAreaManager->AddToList ( this );
}


CClientRadarArea::~CClientRadarArea ( void )
{
    // Remove us from the manager's list
    Unlink ();
}


void CClientRadarArea::Unlink ( void )
{
    m_pRadarAreaManager->RemoveFromList ( this );
}


void CClientRadarArea::DoPulse ( void )
{
	DoPulse ( true );
}


void CClientRadarArea::DoPulse ( bool bRender )
{
    #define RADAR_FLASH_CYCLETIME 1000

	//GTA::Initialize::Log("Rendering in area...");

    // Suppose to show?
    if ( m_bStreamedIn )
    {
		//GTA::Initialize::Log("Rendering in AR4...");

        // If it's flashing, calculate a new alpha
        unsigned long ulColor = m_ulColor;
     
        if ( m_bFlashing )
        {
            // Time to start a new cycle?
            unsigned long ulCurrentTime = timeGetTime();
            if ( m_ulFlashCycleStart == 0 )
            {
                m_ulFlashCycleStart = ulCurrentTime;
            }
            // Time to end the cycle and start a new?
            else if ( ulCurrentTime >= m_ulFlashCycleStart + RADAR_FLASH_CYCLETIME )
            {
                m_ulFlashCycleStart = ulCurrentTime;
            }

            // Calculate the alpha based on the last cycle time and the cycle intervals
            float fAlphaFactor;

            // We're in the fade in part of the cycle?
            if ( ulCurrentTime >= m_ulFlashCycleStart + RADAR_FLASH_CYCLETIME / 2 )
            {
                // Calculate the alpha-factor
                fAlphaFactor = static_cast < float > ( ulCurrentTime - m_ulFlashCycleStart - RADAR_FLASH_CYCLETIME / 2 ) / ( RADAR_FLASH_CYCLETIME / 2 );
            }
            else
            {
                // Calculate the alpha-factor
                fAlphaFactor = 1.0f - static_cast < float > ( ulCurrentTime - m_ulFlashCycleStart ) / ( RADAR_FLASH_CYCLETIME / 2 );
            }

            // Multiply the alpha-factor with the alpha we're supposed to have to find what alpha to use and set it
            unsigned char ucAlpha = static_cast < unsigned char > ( fAlphaFactor * static_cast < float > ( ( ulColor & 0xFF000000 ) >> 24 ) );
            ulColor &= 0x00FFFFFF;
            ulColor |= ucAlpha << 24;
        }

	    // Only render the radar area if we are told to
	    if ( bRender )
	    {
			/*GTA::Initialize::Log("Rendering in AR.");
			GTA::Initialize::Log(System::String::Format("fx1 {0} fy1 {1} fx2 {2} fy2 {3} ulc {4}", m_vecPosition->pX + m_vecSize->pX, m_vecPosition->pY,
                                                    m_vecPosition->pX, m_vecPosition->pY + m_vecSize->pY,
												    ulColor));
			*/
		    // Draw it
		    DrawAreaOnRadar ( m_vecPosition->pX + m_vecSize->pX, m_vecPosition->pY,
                                                    m_vecPosition->pX, m_vecPosition->pY + m_vecSize->pY,
												    ulColor );

			/*DrawAreaOnRadar ( m_vecSize->pX, m_vecSize->pY, m_vecPosition->pX, m_vecPosition->pY,
                                                    
												    ulColor );*/
	    }
    }
}


void CClientRadarArea::SetColor ( unsigned long ulColor )
{
    m_ulColor = ulColor;
}


void CClientRadarArea::SetColor ( unsigned char ucR, unsigned char ucG, unsigned char ucB, unsigned char ucA )
{
	m_ulColor = (((((ucA)&0xff)<<24)|(((ucB)&0xff)<<16)|(((ucG)&0xff)<<8)|((ucR)&0xff)));
}


void CClientRadarArea::SetDimension ( unsigned short usDimension )
{
    //m_usDimension = usDimension;
    RelateDimension ( m_pRadarAreaManager->GetDimension () );
}


void CClientRadarArea::RelateDimension ( unsigned short usDimension )
{
    m_bStreamedIn = true;
}
};
#endif