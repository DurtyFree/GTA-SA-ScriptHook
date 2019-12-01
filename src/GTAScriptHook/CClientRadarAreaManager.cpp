/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto v1.0
*               (Shared logic for modifications)
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        mods/shared_logic/CClientRadarAreaManager.cpp
*  PURPOSE:     Radar area entity manager class
*  DEVELOPERS:  Christian Myhre Lundheim <>
*               Oliver Brown <>
*               Chris McArthur <>
*
*****************************************************************************/

//#include <StdInc.h>
#include "stdafx.h"
#ifdef GTA_SA
#include "CClientRadarAreas.h"

namespace GTA {
CClientRadarAreaManager::CClientRadarAreaManager ()
{
    // Init
    //m_pManager = pManager;
    m_bDontRemoveFromList = false;
    m_usDimension = 0;

	processing = false;

	//m_List 
}


CClientRadarAreaManager::~CClientRadarAreaManager ( void )
{
    // Make sure all the radar areas are deleted
    DeleteAll ();
}


/*CClientRadarArea^ CClientRadarAreaManager::Create ()
{
    //if ( !Get ( EntityID ) )
    //{
        return new CClientRadarArea ();
    //}

    return NULL;
}*/


void CClientRadarAreaManager::Delete ( CClientRadarArea^ pRadarArea )
{
    pRadarArea = nullptr;
}


void CClientRadarAreaManager::DeleteAll ( void )
{
    // Delete all the radar areas
    m_bDontRemoveFromList = true;
    /*list < CClientRadarArea* > ::const_iterator iter = m_List.begin ();
    for ( ; iter != m_List.end (); iter++ )
    {
        delete *iter;
    }*/

	for each (CClientRadarArea^ ra in m_List) {
		ra = nullptr;
	}
    m_bDontRemoveFromList = false;

    // Clear the list
    m_List.Clear ();
}

/*CClientRadarArea* CClientRadarAreaManager::Get ( ElementID ID )
{
    // Grab the element with the given id. Check its type.
    CClientEntity* pEntity = CElementIDs::GetElement ( ID );
    if ( pEntity && pEntity->GetType () == CCLIENTRADARAREA )
    {
        return static_cast < CClientRadarArea* > ( pEntity );
    }

    return NULL;
}*/


void CClientRadarAreaManager::SetDimension ( unsigned short usDimension )
{
    /*list < CClientRadarArea* > ::iterator iter = m_List.begin ();
    for ( ; iter != m_List.end (); iter++ )
    {
        (*iter)->RelateDimension ( usDimension );
    }*/

	for each (CClientRadarArea^ ra in m_List) {
		ra->RelateDimension(usDimension);
	}

    m_usDimension = usDimension;
}


void CClientRadarAreaManager::DoPulse ( void )
{
	// Always assume that we are rendering
	DoPulse ( true );

	//GTA::Initialize::Log("Rendering in manager...");
}

// DoPulse with a rendering flag, as this can be called from either a hook (render == true) or the CClientManager::DoPulse (render == false)
void CClientRadarAreaManager::DoPulse ( bool bRender )
{
    // Pulse each radar area marker
    /*list < CClientRadarArea* > ::const_iterator iter = m_List.begin ();
    for ( ; iter != m_List.end (); iter++ )
    {
        (*iter)->DoPulse ( bRender );
    }*/

	processing = true;

	for each (CClientRadarArea^ ra in m_List) {
		ra->DoPulse(bRender);
	}

	OnDrawRadar(this, gcnew DrawRadarEventArgs());

	processing = false;
}

void CClientRadarAreaManager::RemoveFromList ( CClientRadarArea^ pRadarArea )
{
    if ( !m_bDontRemoveFromList )
    {
        //if ( !m_List.empty() ) m_List.remove ( pRadarArea );
		m_List.Remove(pRadarArea);
    }
}
};
#endif