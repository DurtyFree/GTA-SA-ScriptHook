
/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto v1.0
*               (Shared logic for modifications)
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        mods/shared_logic/CClientRadarAreaManager.h
*  PURPOSE:     Radar area entity manager class header
*  DEVELOPERS:  Christian Myhre Lundheim <>
*               Oliver Brown <>
*               Chris McArthur <>
*
*****************************************************************************/

#ifndef __CCLIENTRADARAREAMANAGER_H
#define __CCLIENTRADARAREAMANAGER_H

#include <list>
#include "NativeTypes.h"

using namespace std;
using namespace System;
using namespace System::Collections::Generic;

namespace GTA {
ref class CClientRadarArea;

public ref class DrawRadarEventArgs : EventArgs {
public:
	void DrawArea(float x1, float y1, float x2, float y2, Drawing::Color color);
};

public ref class CClientRadarAreaManager
{
    //friend class CClientManager;
    //friend class CClientRadarArea;
    //friend class CClientGame;

public:
	bool processing;

                                                            CClientRadarAreaManager             ();
                                                            ~CClientRadarAreaManager            ( void );

    //CClientRadarArea^                                       Create                              ();

    void                                                    Delete                              ( CClientRadarArea^ pRadarArea );
    void                                                    DeleteAll                           ( void );

    //inline list < CClientRadarArea* > ::const_iterator      IterBegin                           ( void )                                { return m_List.begin (); };
    //inline list < CClientRadarArea* > ::const_iterator      IterEnd                             ( void )                                { return m_List.end (); };

    //static CClientRadarArea^                                Get                                 ();

    unsigned short                                          GetDimension                        ( void )                                { return m_usDimension; };
    void                                                    SetDimension                        ( unsigned short usDimension );

	event EventHandler<DrawRadarEventArgs^>^ OnDrawRadar {
			  void add( EventHandler<DrawRadarEventArgs^>^ handler )
			  {
			   EnterHandler += handler;
			  }
			  void remove( EventHandler<DrawRadarEventArgs^>^ handler )
			  {
			   EnterHandler -= handler;
			  }
			  void raise( Object^ sender, DrawRadarEventArgs^ args )
			  {
				  if (EnterHandler) {
						EnterHandler(sender, args);
				  }
			  }	
		}

internal:
    void                                                    DoPulse                             ( void );
	void													DoPulse								( bool bRender );

    inline void                                             AddToList                           ( CClientRadarArea^ pRadarArea )        { m_List.Add ( pRadarArea ); };
    void                                                    RemoveFromList                      ( CClientRadarArea^ pRadarArea );

private:
	EventHandler<DrawRadarEventArgs^>^ EnterHandler;

    //CClientManager*                                         m_pManager;

	System::Collections::Generic::List < CClientRadarArea^ >  m_List;
    bool                                                    m_bDontRemoveFromList;
    unsigned short                                          m_usDimension;

};
};

#endif


/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto v1.0
*               (Shared logic for modifications)
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        mods/shared_logic/CClientRadarArea.h
*  PURPOSE:     Radar area entity class header
*  DEVELOPERS:  Christian Myhre Lundheim <>
*               Oliver Brown <>
*               Ed Lyons <eai@opencoding.net>
*               Jax <>
*               Chris McArthur <>
*               Stanislav Bobrov <lil_toady@hotmail.com>
*               Alberto Alonso <rydencillo@gmail.com>
*
*****************************************************************************/

#include "NativeTypes.h"

#ifndef __CCLIENTRADARAREA_H
#define __CCLIENTRADARAREA_H

//#include "CClientRadarAreaManager.h"
namespace GTA {
struct CRect {
    float fX1, fY1, fX2, fY2;
};

#define FUNC_DrawAreaOnRadar				0x5853d0

	void DrawAreaOnRadar(float fX1, float fY1, float fX2, float fY2, DWORD abgr );

public ref class CClientRadarArea
{
    //friend class CClientRadarAreaManager;

public:
                                CClientRadarArea            ();
                                ~CClientRadarArea           ( void );

    void                        Unlink                      ( void );

    //inline eClientEntityType    GetType                     ( void ) const                      { return CCLIENTRADARAREA; };

    /*inline const CVector2D&     GetPosition                 ( void ) const                      { return m_vecPosition; };
    inline void                 GetPosition                 ( CVector2D& vecPosition ) const    { vecPosition = m_vecPosition; };
    inline void                 GetPosition                 ( CVector& vecPosition ) const      { vecPosition = CVector ( m_vecPosition.fX, m_vecPosition.fY, 0.0f ); };
    inline void                 SetPosition                 ( const CVector2D& vecPosition )    { m_vecPosition = vecPosition; };
    inline void                 SetPosition                 ( const CVector& vecPosition )      { m_vecPosition = CVector2D ( vecPosition.fX, vecPosition.fY ); };*/

    /*inline const CVector2D&     GetSize                     ( void ) const                      { return m_vecSize; };
    inline void                 GetSize                     ( CVector2D& vecSize )              { vecSize = m_vecSize; };
    inline void                 SetSize                     ( const CVector2D& vecSize )        { m_vecSize = vecSize; };*/

    inline unsigned long        GetColor                    ( void )                       { return m_ulColor; };
    void                        SetColor                    ( unsigned long ulColor );
    void                        SetColor                    ( unsigned char ucR, unsigned char ucG, unsigned char ucB, unsigned char ucA );

    inline bool                 IsFlashing                  ( void )                       { return m_bFlashing; };
    inline void                 SetFlashing                 ( bool bFlashing )                  { m_bFlashing = bFlashing; };

    void                        SetDimension                ( unsigned short usDimension );
    void                        RelateDimension             ( unsigned short usDimension );

	property SVector^ Position {
		SVector^ get() {
			return m_vecPosition;
		}
		void set(SVector^ value) {
			m_vecPosition = value;
		}
	}

	property SVector^ Size {
		SVector^ get() {
			return m_vecSize;
		}
		void set(SVector^ value) {
			m_vecSize = value;
		}
	}

	static property CClientRadarAreaManager^ Manager {
		CClientRadarAreaManager^ get() {
			return m_pRadarAreaManager;
		}

		void set(CClientRadarAreaManager^ value) {
			m_pRadarAreaManager = value;
		}
	}

internal:
	void                        DoPulse                     ( void );
	void						DoPulse						( bool bRender );


    static CClientRadarAreaManager^    m_pRadarAreaManager;
protected:
    SVector^                    m_vecPosition;
    SVector^                    m_vecSize;
    unsigned long               m_ulColor;

    bool                        m_bStreamedIn;
    bool                        m_bFlashing;
    unsigned long               m_ulFlashCycleStart;

};

public ref class RadarHook {
public:
	static void Install();
};
};

#endif
