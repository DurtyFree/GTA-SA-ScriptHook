// some code taken from Multi Theft Auto, licensed under the GPLv3.

#pragma once

#ifndef DMARKERS_H
#define DMARKERS_H

using namespace System;
using namespace System::Collections::Generic;

#include "NativeTypes.h"
#include "RenderWare.h"

struct ColorRGBA {
	unsigned char R;
	unsigned char G;
	unsigned char B;
	unsigned char A;
};

namespace GTA {
	class CEntitySAInterface;

	typedef BOOL (__cdecl *WorldCoords2ScreenCoords_t)(CVector * inPoint, CVector * outpoint, float * x, float * y, char, char);
	static WorldCoords2ScreenCoords_t WorldCoords2ScreenCoords = (WorldCoords2ScreenCoords_t)0x70CE30;
}

namespace GTA {	
	public class C3DMarkerSAInterface
	{
	public:
		CMatrix_Padded	m_mat;	// local space to world space transform // 0
		DWORD			dwPad,dwPad2;	// not sure why we need these, it appears to be this way though (eAi)  // 64/68
		RpClump 		*m_pRwObject; // 72
		DWORD			*m_pMaterial; // 76
		
		WORD			m_nType; // 80
		bool			m_bIsUsed;	// has this marker been allocated this frame?	 // 82
		DWORD			m_nIdentifier; // 84

		RGBA			rwColour; // 88 
		WORD			m_nPulsePeriod; // 92
		short			m_nRotateRate;	// deg per frame (in either direction) // 94
		DWORD			m_nStartTime; // 96
		FLOAT			m_fPulseFraction;  // 100
		FLOAT			m_fStdSize; // 104
		FLOAT			m_fSize; // 108
		FLOAT			m_fBrightness; // 112
		FLOAT			m_fCameraRange; // 116

		CVector		m_normal;			// Normal of the object point at             // 120
		// the following variables remember the last time we read the heigh of the
		// map. Using this we don't have to do this every frame and we can still have moving markers.
		WORD			m_LastMapReadX, m_LastMapReadY; // 132 / 134
		FLOAT			m_LastMapReadResultZ; // 136
		FLOAT			m_roofHeight; // 140
		CVector			m_lastPosition; // 144
		DWORD			m_OnScreenTestTime;		// time last screen check was done // 156
	};

	public ref class GTA3DMarker {
	private:
		C3DMarkerSAInterface* internalInterface;

		void GetColor ( unsigned char& Red, unsigned char& Green, unsigned char& Blue, unsigned char& Alpha )
		{
			Red = static_cast < unsigned char > ( internalInterface->rwColour );
			Green = static_cast < unsigned char > ( internalInterface->rwColour >> 8 );
			Blue = static_cast < unsigned char > ( internalInterface->rwColour >> 16 );
			Alpha = static_cast < unsigned char > ( internalInterface->rwColour >> 24 );
		}

		void SetColor ( unsigned char Red, unsigned char Green, unsigned char Blue, unsigned char Alpha )
		{
			internalInterface->rwColour =  (((((Alpha)&0xff)<<24)|(((Blue)&0xff)<<16)|(((Green)&0xff)<<8)|((Red)&0xff)));
		}

		float pulseFraction;
	public:
		GTA3DMarker(C3DMarkerSAInterface * markerInterface) { internalInterface = markerInterface; pulseFraction = 0.0f; };

		C3DMarkerSAInterface* GetInterface() { return internalInterface; }

		void Disable()
		{
			this->GetInterface()->m_nIdentifier = 0;
		}

		property int Type {
			int get() {
				return internalInterface->m_nType;
			}
		}

		property SVector^ Position {
			SVector^ get() {
				CVector position = internalInterface->m_mat.vPos;

				SVector^ ret = gcnew SVector(position.fX, position.fY, position.fZ);

				return ret;
			}

			void set(SVector^ pos) {
				internalInterface->m_mat.vPos = CVector(pos->pX, pos->pY, pos->pZ);
			}
		}

		SVector^ GetNormalPosition() {
			CVector position = internalInterface->m_normal;

			SVector^ ret = gcnew SVector(position.fX, position.fY, position.fZ);

			return ret;
		}

		property bool CanPulse {
			void set(bool value) {
				if (pulseFraction == 0.0f) {
					pulseFraction = internalInterface->m_fPulseFraction;
				}

				if (value) {
					internalInterface->m_fPulseFraction = pulseFraction;
				} else {
					internalInterface->m_fPulseFraction = 0.0f;
					internalInterface->m_nPulsePeriod = 0;
				}
			}
		}

		property bool Exists {
			bool get() {
				return internalInterface->m_bIsUsed;
			}

			void set(bool value) {
				internalInterface->m_bIsUsed = value;
			}
		}

		property int ID {
			int get() {
				return internalInterface->m_nIdentifier;
			}
		}

		void SetZRotation(int degrees);

		void SetAlpha(int nA);
	};

	public ref class GTA3DMarkers {
	private:
		static array<GTA3DMarker^>^ Markers;
	public:
		static GTA3DMarkers();

		static array<GTA3DMarker^>^ GetMarkers();
	internal:
		static GTA3DMarker^ GetFreeMarker();
		//static GTA3DMarker^ CreateMarker(DWORD identifier, Vector3^ position, float size, Drawing::Color color);
	};

	public class CEntitySAInterfaceVTBL
	{	
	public:
		DWORD SCALAR_DELETING_DESTRUCTOR;
		DWORD Add_CRect;
		DWORD Add;
		DWORD Remove;
		DWORD SetIsStatic;
		DWORD SetModelIndex;
		DWORD SetModelIndexNoCreate;
		DWORD CreateRwObject;
		DWORD DeleteRwObject;
		DWORD GetBoundRect;
		DWORD ProcessControl;
		DWORD ProcessCollision;
		DWORD ProcessShift;
		DWORD TestCollision;
		DWORD Teleport;
		DWORD SpecialEntityPreCollisionStuff;
		DWORD SpecialEntityCalcCollisionSteps;
		DWORD PreRender;
		DWORD Render;
		DWORD SetupLighting;
		DWORD RemoveLighting;
		DWORD FlagToDestroyWhenNextProcessed;
	};


	/** 
	 * \todo Move CReferences (and others below?) into it's own file
	 */
	public class CReferences
	{
		DWORD		* pEntity;
	};

	public class CSimpleTransformSAInterface
	{
	public:
		CVector							m_translate;
		FLOAT							m_heading;
	};

	public class CPlaceableSAInterface
	{
	public:
		CSimpleTransformSAInterface		m_transform;
		CMatrix_Padded					* matrix;
	};

	class CEntitySAInterface;

	public class CEntitySAInterface
	{
	public:
		CEntitySAInterfaceVTBL		* vtbl;	// the virtual table
		
		CPlaceableSAInterface	Placeable; // 4

		RpClump		* m_pRwObject; // 24
		/********** BEGIN CFLAGS **************/
		/*unsigned long bUsesCollision : 1;			// does entity use collision
		unsigned long bCollisionProcessed : 1; 	// has object been processed by a ProcessEntityCollision function
		unsigned long bIsStatic : 1;				// is entity static
		unsigned long bHasContacted : 1;			// has entity processed some contact forces
		unsigned long bIsStuck : 1;				// is entity stuck
		unsigned long bIsInSafePosition : 1;		// is entity in a collision free safe position
		unsigned long bWasPostponed : 1;			// was entity control processing postponed
		unsigned long bIsVisible : 1;				//is the entity visible
		
		unsigned long bIsBIGBuilding : 1;			// Set if this entity is a big building
		unsigned long bRenderDamaged : 1;			// use damaged LOD models for objects with applicable damage
		unsigned long bStreamingDontDelete : 1;	// Dont let the streaming remove this 
		unsigned long bRemoveFromWorld : 1;		// remove this entity next time it should be processed
		unsigned long bHasHitWall : 1;				// has collided with a building (changes subsequent collisions)
		unsigned long bImBeingRendered : 1;		// don't delete me because I'm being rendered
		unsigned long bDrawLast :1;				// draw object last
		unsigned long bDistanceFade :1;			// Fade entity because it is far away
		
		unsigned long bDontCastShadowsOn : 1;		// Dont cast shadows on this object
		unsigned long bOffscreen : 1;				// offscreen flag. This can only be trusted when it is set to true
		unsigned long bIsStaticWaitingForCollision : 1; // this is used by script created entities - they are static until the collision is loaded below them
		unsigned long bDontStream : 1;				// tell the streaming not to stream me
		unsigned long bUnderwater : 1;				// this object is underwater change drawing order
		unsigned long bHasPreRenderEffects : 1;	// Object has a prerender effects attached to it
		unsigned long bIsTempBuilding : 1;			// whether or not the building is temporary (i.e. can be created and deleted more than once)
		unsigned long bDontUpdateHierarchy : 1;	// Don't update the aniamtion hierarchy this frame
		
		unsigned long bHasRoadsignText : 1;		// entity is roadsign and has some 2deffect text stuff to be rendered
		unsigned long bDisplayedSuperLowLOD : 1;
		unsigned long bIsProcObject : 1;			// set object has been generate by procedural object generator
		unsigned long bBackfaceCulled : 1;			// has backface culling on
		unsigned long bLightObject : 1;			// light object with directional lights
		unsigned long bUnimportantStream : 1;		// set that this object is unimportant, if streaming is having problems
		unsigned long bTunnel : 1;			// Is this model part of a tunnel
		unsigned long bTunnelTransition : 1;		// This model should be rendered from within and outside of the tunnel*/
		DWORD dwFlags; // 28
		/********** END CFLAGS **************/

		WORD 		RandomSeed; //32
		WORD 		m_nModelIndex;//34
		CReferences	*pReferences; //36
		
		DWORD		* m_pLastRenderedLink; // 	CLink<CEntity*>* m_pLastRenderedLink; +40
		
		WORD m_nScanCode;			// 44
		BYTE m_iplIndex;			// used to define which IPL file object is in +46
		BYTE m_areaCode;			// used to define what objects are visible at this point +47
		
		// LOD shit
		CEntitySAInterface * m_pLod; // 48
		// num child higher level LODs
		BYTE numLodChildren; // 52
		// num child higher level LODs that have been rendered
		signed char numLodChildrenRendered; // 53

		//********* BEGIN CEntityInfo **********//
		BYTE nType : 3; // what type is the entity				// 54 (2 == Vehicle)
		BYTE nStatus : 5;				// control status		// 54
		//********* END CEntityInfo **********//

		//58-66 padded
		BYTE pad[8];
		BYTE nImmunities;
		BYTE pad2 [ 1 ];

		/* IMPORTANT: KEEP "pad" in CVehicle UP-TO-DATE if you add something here (or eventually pad someplace else) */
	};

	public class CPhysicalSAInterface : public CEntitySAInterface // begin +68 (244 bytes total?)
	{
	public:
	/* IMPORTANT: KEEP "pad" in CVehicle UP-TO-DATE if you add something here (or eventually pad someplace else) */
		CVector * vecVelocity;
		CVector * vecSpin;
		CVector * vecUnk3;
		CVector * vecUnk4;
		CVector * vecUnk5;
		CVector * vecUnk6;
		float pad [12];
		float fMass;
		float fTurnMass;

		DWORD dwUnk; // 148
		DWORD dwPhysUnk1; // 152

		float fElasticity; // 156
		float fBuoyancyConstant; // 160
		CVector * vecCenterOfMass; // 164

		DWORD dwUnk2; // 176
		DWORD * unkCPtrNodeDoubleLink; // 180

		BYTE byUnk: 8; 
		BYTE byCollisionRecords: 8; // 185
		BYTE byUnk2: 8;
		BYTE byUnk3: 8;

		float pad4 [8];

		float fDistanceTravelled; // 212
		float fDamageImpulseMagnitude; //216
		CEntitySAInterface * damageEntity; // 220

		BYTE pad2[28];
		CEntitySAInterface * pAttachedEntity;   // 252
		CVector vecAttachedPosition;    // 256
		CVector vecAttachedRotation;    // 268
		BYTE pad3[32];
	};

	public class CObjectSAInterface : public CPhysicalSAInterface // + 372 = burn time stop , +348 = scale // +340 = health
	{
		DWORD Padding[29];
	};

	public class CPickupSAInterface 
	{
	public:	
		float	CurrentValue;		// For the revenue pickups  0
		DWORD	pObject; // 4
		long	MonetaryValue;  // 8
		DWORD	RegenerationTime; // 12
		short	CoorsX, CoorsY, CoorsZ; //16 // 18 // 20
		WORD	MoneyPerDay; //22
		WORD	MI; // 24
		WORD	ReferenceIndex; // 26
		BYTE	Type; // 28
		BYTE	State : 1; //29
		BYTE	bNoAmmo : 1;
		BYTE	bHelpMessageDisplayed : 1;
		BYTE	bIsPickupNearby : 1;	// If the pickup is nearby it will get an object and it will get updated.
		BYTE	TextIndex : 3;			// What text label do we print out above it.
	};

	public ref class GTAPickup {
	private:
		CPickupSAInterface* internalInterface;
	public:
		GTAPickup(CPickupSAInterface * markerInterface) { internalInterface = markerInterface; };

		CPickupSAInterface* GetInterface() { return internalInterface; }

		/*void Disable()
		{
			this->GetInterface()->m_nIdentifier = 0;
		}*/

		property int Model {
			int get() {
				return internalInterface->MI;
			}
		}

		property int CObjectPtr {
			int get() {
				return internalInterface->pObject;
			}
		}

		property SVector^ Position {
			SVector^ get() {
				//CVector position = internalInterface->CoorsX;
				//CVector position = internalInterface->m_mat.vPos;

				SVector^ ret = gcnew SVector(internalInterface->CoorsX / 8.0f, internalInterface->CoorsY / 8.0f, internalInterface->CoorsZ / 8.0f);

				return ret;
			}

			void set(SVector^ vecPosition) {
				//internalInterface->pObject->Placeable.matrix->vPos = CVector(pos->pX, pos->pY, pos->pZ);
				internalInterface->bIsPickupNearby = 0;

				internalInterface->CoorsX = (short)(vecPosition->pX * 8);
				internalInterface->CoorsY = (short)(vecPosition->pY * 8);
				internalInterface->CoorsZ = (short)(vecPosition->pZ * 8);
			}
		}

		/*Vector3^ GetNormalPosition() {
			CVector position = internalInterface->m_normal;

			Vector3^ ret = gcnew Vector3(position.fX, position.fY, position.fZ);

			return ret;
		}

		property bool CanPulse {
			void set(bool value) {
				if (pulseFraction == 0.0f) {
					pulseFraction = internalInterface->m_fPulseFraction;
				}

				if (value) {
					internalInterface->m_fPulseFraction = pulseFraction;
				} else {
					internalInterface->m_fPulseFraction = 0.0f;
					internalInterface->m_nPulsePeriod = 0;
				}
			}
		}*/

		property bool Exists {
			bool get() {
				return (internalInterface->Type != 0 && internalInterface->bIsPickupNearby);
			}
		}

		/*property int ID {
			int get() {
				return internalInterface->ReferenceIndex;
			}
		}*/

		void SetVisible(bool vis) {
			//internalInterface->pObject->bIsVisible = vis;
		}

		void SetRotation(int x, int y, int z) {
			float xr = x * (3.1415926535897932384626433832795f / 180.0f);
			float yr = y * (3.1415926535897932384626433832795f / 180.0f);
			float zr = z * (3.1415926535897932384626433832795f / 180.0f);

			/*CMatrix_Padded* mat = (internalInterface->pObject->Placeable.matrix);

			ConvertFromEulerAngles(mat, xr, yr, zr);*/

			//float xr = x;
			//float yr = y;
			//float zr = z;

			//SetObjectOrientation(internalInterface->pObject, xr, yr, zr);

			//mat.vRoll.fZ = z;
			//internalInterface->pObject->Placeable.matrix = &mat;
		}
	};

	public ref class GTAPickups {
	private:
		static array<GTAPickup^>^ Pickups;
	public:
		static GTAPickups();

		static array<GTAPickup^>^ GetPickups();
	};

const int NUMBER_OF_VECTORS_FOR_AVERAGE=2;
#define CAM_NUM_TARGET_HISTORY			4

#define MAX_CAMS							3 

#define MAX_NUM_OF_NODES					800 // for trains

/*** R* Defines ***/
#define NUMBER_OF_VECTORS_FOR_AVERAGE 2
#define MAX_NUM_OF_SPLINETYPES (4)

	class CCamPathSplines
{
	public: 
	enum {MAXPATHLENGTH=800};
	FLOAT *m_arr_PathData;//	FLOAT m_arr_PathData[MAXPATHLENGTH];	
};

class CQueuedMode
{
public:
	short		Mode;					// CameraMode
	FLOAT		Duration;				// How long for (<0.0f -> indefinately)
	short		MinZoom, MaxZoom;		// How far is player allowed to zoom in & out
};

class CTrainCamNode
{
	public:
	CVector m_cvecCamPosition;
	CVector m_cvecPointToLookAt;
	CVector m_cvecMinPointInRange;//this is the minimum required distance the train has to be to the camera to 
	//allow a switch to the node cam 
	CVector m_cvecMaxPointInRange;//this is the minimum required distance the train has to be to from the camera 
	FLOAT m_fDesiredFOV;
	FLOAT m_fNearClip;
	//to switch from the  the node cam
};

/*** END PURE R* CLASSES ***/

class CCamSAInterface // 568 bytes?
{
public:

	bool	bBelowMinDist; //used for follow ped mode
	bool	bBehindPlayerDesired; //used for follow ped mode
	bool 	m_bCamLookingAtVector;
	bool 	m_bCollisionChecksOn;
	bool	m_bFixingBeta; //used for camera on a string
	bool 	m_bTheHeightFixerVehicleIsATrain;
	bool 	LookBehindCamWasInFront;
	bool 	LookingBehind;
	bool 	LookingLeft; // 32
	bool 	LookingRight;
	bool 	ResetStatics; //for interpolation type stuff to work
	bool 	Rotating;

	short	Mode;					// CameraMode
	unsigned int  m_uiFinishTime; // 52
	
	int 	m_iDoCollisionChecksOnFrameNum; 
	int 	m_iDoCollisionCheckEveryNumOfFrames;
	int 	m_iFrameNumWereAt;	// 64
	int 	m_iRunningVectorArrayPos;
	int 	m_iRunningVectorCounter;
	int 	DirectionWasLooking;
	
	float 	f_max_role_angle; //=DEGTORAD(5.0f);	
	float 	f_Roll; //used for adding a slight roll to the camera in the
	float 	f_rollSpeed; //camera on a string mode
	float 	m_fSyphonModeTargetZOffSet;
	float 	m_fAmountFractionObscured;
	float 	m_fAlphaSpeedOverOneFrame; // 100
	float 	m_fBetaSpeedOverOneFrame;
	float 	m_fBufferedTargetBeta;
	float 	m_fBufferedTargetOrientation;
	float	m_fBufferedTargetOrientationSpeed;
	float 	m_fCamBufferedHeight;
	float 	m_fCamBufferedHeightSpeed;
	float 	m_fCloseInPedHeightOffset;
	float 	m_fCloseInPedHeightOffsetSpeed; // 132
	float 	m_fCloseInCarHeightOffset;
	float 	m_fCloseInCarHeightOffsetSpeed;
	float 	m_fDimensionOfHighestNearCar;		
	float	m_fDistanceBeforeChanges;
	float 	m_fFovSpeedOverOneFrame;
	float 	m_fMinDistAwayFromCamWhenInterPolating;
	float 	m_fPedBetweenCameraHeightOffset;
	float 	m_fPlayerInFrontSyphonAngleOffSet; // 164
	float	m_fRadiusForDead;
	float	m_fRealGroundDist; //used for follow ped mode
	float 	m_fTargetBeta;
	float 	m_fTimeElapsedFloat;	
	float 	m_fTilt;
	float 	m_fTiltSpeed;

	float   m_fTransitionBeta;
	float 	m_fTrueBeta;
	float 	m_fTrueAlpha; // 200
	float	m_fInitialPlayerOrientation; //used for first person

	float	Alpha;
	float	AlphaSpeed;
	float	FOV;
    float	FOVSpeed;
	float	Beta;
	float	BetaSpeed;
	float	Distance; // 232
	float	DistanceSpeed;
	float 	CA_MIN_DISTANCE;
	float 	CA_MAX_DISTANCE;
	float	SpeedVar;
	float	m_fCameraHeightMultiplier; //used by TwoPlayer_Separate_Cars_TopDown
	
	// ped onfoot zoom distance
	float m_fTargetZoomGroundOne;
	float m_fTargetZoomGroundTwo; // 256
	float m_fTargetZoomGroundThree;
	// ped onfoot alpha angle offset
	float m_fTargetZoomOneZExtra;
	float m_fTargetZoomTwoZExtra;
	float m_fTargetZoomTwoInteriorZExtra; //extra one for interior
	float m_fTargetZoomThreeZExtra;
	
	float m_fTargetZoomZCloseIn;
	float m_fMinRealGroundDist;
	float m_fTargetCloseInDist;

	// For targetting in cooperative mode.
	float	Beta_Targeting; // 292
	float	X_Targetting, Y_Targetting;
	int	CarWeAreFocussingOn; //which car is closer to the camera in 2 player cooperative mode with separate cars.
	float	CarWeAreFocussingOnI; //interpolated version
	
	float m_fCamBumpedHorz; // 312
	float m_fCamBumpedVert;
	int	m_nCamBumpedTime; // 320
	static int CAM_BUMPED_SWING_PERIOD;
	static int CAM_BUMPED_END_TIME;
	static float CAM_BUMPED_DAMP_RATE;
	static float CAM_BUMPED_MOVE_MULT;

	CVector m_cvecSourceSpeedOverOneFrame; // 324
	CVector m_cvecTargetSpeedOverOneFrame; // 336
	CVector m_cvecUpOverOneFrame; // 348
	
	CVector m_cvecTargetCoorsForFudgeInter; // 360
	CVector m_cvecCamFixedModeVector; // 372
	CVector m_cvecCamFixedModeSource; // 384
  	CVector m_cvecCamFixedModeUpOffSet; // 396
	CVector m_vecLastAboveWaterCamPosition; //408  //helper for when the player has gone under the water

	CVector m_vecBufferedPlayerBodyOffset; // 420

	// The three vectors that determine this camera for this frame
	CVector	Front;	// 432												// Direction of looking in
	CVector	Source;													// Coors in world space
	CVector	SourceBeforeLookBehind;
	CVector	Up;														// Just that
	CVector	m_arrPreviousVectors[NUMBER_OF_VECTORS_FOR_AVERAGE];	// used to average stuff

	CVector m_aTargetHistoryPos[CAM_NUM_TARGET_HISTORY];
	DWORD m_nTargetHistoryTime[CAM_NUM_TARGET_HISTORY];
	DWORD m_nCurrentHistoryPoints;

	CEntitySAInterface *CamTargetEntity;
protected:
	float 		m_fCameraDistance;
	float 		m_fIdealAlpha;
	float 		m_fPlayerVelocity;
	//CVector TempRight;
	void	*m_pLastCarEntered; // So interpolation works
	void			*m_pLastPedLookedAt;// So interpolation works 
	bool		m_bFirstPersonRunAboutActive;
};

class CCameraSAInterface 
{
public:
	// CPlaceable
	CPlaceableSAInterface	Placeable;
	// End CPlaceable

	//move these out the class, have decided to set up a mirrored enumerated type thingy at the top
	bool 	m_bAboveGroundTrainNodesLoaded;
	bool 	m_bBelowGroundTrainNodesLoaded;
	bool 	m_bCamDirectlyBehind;	
	bool 	m_bCamDirectlyInFront;	
  	bool	m_bCameraJustRestored;
	bool 	m_bcutsceneFinished;
	bool 	m_bCullZoneChecksOn;
	bool 	m_bFirstPersonBeingUsed; // To indicate if the m_bFirstPersonBeingUsed viewer is being used.
	bool	m_bJustJumpedOutOf1stPersonBecauseOfTarget;
	bool 	m_bIdleOn;
	bool  	m_bInATunnelAndABigVehicle;
	bool 	m_bInitialNodeFound;
    bool 	m_bInitialNoNodeStaticsSet;
	bool   	m_bIgnoreFadingStuffForMusic;
	bool  	m_bPlayerIsInGarage;
	bool	m_bPlayerWasOnBike;
	bool  	m_bJustCameOutOfGarage;
	bool 	m_bJustInitalised;//Just so the speed thingy doesn't go mad right at the start
    unsigned char 	m_bJust_Switched;//Variable to indicate that we have jumped somewhere, Raymond needs this for the audio engine
	bool 	m_bLookingAtPlayer;
	bool 	m_bLookingAtVector;
	bool 	m_bMoveCamToAvoidGeom;
	bool 	m_bObbeCinematicPedCamOn;
	bool 	m_bObbeCinematicCarCamOn;
	bool 	m_bRestoreByJumpCut;
	bool   	m_bUseNearClipScript;
	bool 	m_bStartInterScript;
	unsigned char 	m_bStartingSpline;
	bool 	m_bTargetJustBeenOnTrain; //this variable is needed to be able to restore the camera
	bool 	m_bTargetJustCameOffTrain;
    bool 	m_bUseSpecialFovTrain;
	bool    m_bUseTransitionBeta;
	bool 	m_bUseScriptZoomValuePed;
	bool 	m_bUseScriptZoomValueCar;
	bool 	m_bWaitForInterpolToFinish;
	bool	m_bItsOkToLookJustAtThePlayer; //Used when interpolating
	bool 	m_bWantsToSwitchWidescreenOff;	
	bool 	m_WideScreenOn;	
	bool	m_1rstPersonRunCloseToAWall;
	bool	m_bHeadBob;
	bool 	m_bVehicleSuspenHigh;
	bool 	m_bEnable1rstPersonCamCntrlsScript; 
	bool 	m_bAllow1rstPersonWeaponsCamera;
	bool	m_bCooperativeCamMode;
	bool	m_bAllowShootingWith2PlayersInCar;
	bool	m_bDisableFirstPersonInCar;
	static bool	m_bUseMouse3rdPerson;
#ifndef FINALBUILD	
	bool 	bStaticFrustum;
#endif	

	// for debug keyboard stuff
#ifndef MASTER
	unsigned char display_kbd_debug;
	float kbd_fov_value;
#endif // MASTER

		// The following fields allow the level designers to specify the camera for 2 player games.
	short	m_ModeForTwoPlayersSeparateCars;
	short	m_ModeForTwoPlayersSameCarShootingAllowed;
	short	m_ModeForTwoPlayersSameCarShootingNotAllowed;
	short	m_ModeForTwoPlayersNotBothInCar;

	bool 	m_bGarageFixedCamPositionSet;
    bool 	m_vecDoingSpecialInterPolation;
	bool 	m_bScriptParametersSetForInterPol;

	
	bool 	m_bFading;//to indicate that we are fading 
	bool 	m_bMusicFading;
	bool 	m_bMusicFadedOut;

	bool 	m_bFailedCullZoneTestPreviously;
	bool 	m_FadeTargetIsSplashScreen;//used as hack for fading 
	bool 	WorldViewerBeingUsed; // To indicate if the world viewer is being used.										 

	
	unsigned char	m_uiTransitionJUSTStarted;	// This is the first frame of a transition.
	unsigned char	m_uiTransitionState;		// 0:one mode 1:transition
	unsigned char	ActiveCam;				// Which one at the moment (0 or 1)
										// Their is a fudge at the end when the renderware matrix will receive either
										// the active camera or the worldviewer camera
	unsigned int	m_uiCamShakeStart;			// When did the camera shake start.
	unsigned int 	m_uiFirstPersonCamLastInputTime;
 	unsigned int 	m_uiLongestTimeInMill;
  	unsigned int 	m_uiNumberOfTrainCamNodes;
    unsigned int 	m_uiTimeLastChange;
	unsigned int 	m_uiTimeWeLeftIdle_StillNoInput;
	unsigned int  m_uiTimeWeEnteredIdle;
	unsigned int	m_uiTimeTransitionStart;	// When was the transition started ?
	unsigned int	m_uiTransitionDuration;		// How long does the transition take ?
	unsigned int	m_uiTransitionDurationTargetCoors;
	int 	m_BlurBlue;
	int 	m_BlurGreen;
	int 	m_BlurRed;
	int 	m_BlurType;
	int 	m_iWorkOutSpeedThisNumFrames;//duh	
	int 	m_iNumFramesSoFar; //counter
	int 	m_iCurrentTrainCamNode;//variable indicating which camera node we are at for the train
  	int 	m_motionBlur;//to indicate that we are fading

	int 	m_imotionBlurAddAlpha;
	int 	m_iCheckCullZoneThisNumFrames; 
	int 	m_iZoneCullFrameNumWereAt;
	int 	WhoIsInControlOfTheCamera; //to discern between obbe and scripts


//	float	CarZoomIndicator;
//	float 	CarZoomValue;
//	float	CarZoomValueSmooth;
//	float 	m_fCarZoomValueScript;
//	float 	PedZoomIndicator;
//	float	m_fPedZoomValue;
//	float	m_fPedZoomValueSmooth;
//	float 	m_fPedZoomValueScript;
	int	m_nCarZoom; 				// store zoom index
	float 	m_fCarZoomBase;				// store base zoom distance from index
	float	m_fCarZoomTotal;			// store total zoom after modded by camera modes
	float	m_fCarZoomSmoothed;			// buffered version of the var above
	float 	m_fCarZoomValueScript;
	int 	m_nPedZoom;					// store zoom index
	float	m_fPedZoomBase;				// store base zoom distance from index
	float	m_fPedZoomTotal;			// store total zoom after modded by camera modes
	float	m_fPedZoomSmoothed;			// buffered version of the var above
	float 	m_fPedZoomValueScript;


	float	CamFrontXNorm, CamFrontYNorm;
	float	DistanceToWater;
	float	HeightOfNearestWater;
	float 	FOVDuringInter;
	float	LODDistMultiplier;	// This takes into account the FOV and the standard LOD multiplier Smaller aperture->bigger LOD multipliers.
	float 	GenerationDistMultiplier;	// This takes into account the FOV but noy the standard LOD multiplier

	float 	m_fAlphaSpeedAtStartInter;
  	float	m_fAlphaWhenInterPol;
	float 	m_fAlphaDuringInterPol;
	float   m_fBetaDuringInterPol;
	float 	m_fBetaSpeedAtStartInter;
  	float 	m_fBetaWhenInterPol;
	float 	m_fFOVWhenInterPol;
	float 	m_fFOVSpeedAtStartInter;
	float 	m_fStartingBetaForInterPol;
	float 	m_fStartingAlphaForInterPol;
  	float   m_PedOrientForBehindOrInFront;

	float 	m_CameraAverageSpeed; //this is an average depending on how many frames we work it out
	float 	m_CameraSpeedSoFar; //this is a running total
	float	m_fCamShakeForce;			// How severe is the camera shake.
    float 	m_fFovForTrain;
	float 	m_fFOV_Wide_Screen;

	float  	m_fNearClipScript;
	float	m_fOldBetaDiff;			// Needed for interpolation between 2 modes
	float 	m_fPositionAlongSpline;//Variable used to indicate how far along the spline we are 0-1 for started to completed respectively
	float 	m_ScreenReductionPercentage;
	float 	m_ScreenReductionSpeed;
	float 	m_AlphaForPlayerAnim1rstPerson;
	
	float	Orientation;			// The orientation of the camera. Used for peds walking.
	float	PlayerExhaustion;		// How tired is player (inaccurate sniping) 0.0f-1.0f
					// The following things are used by the sound code to
					// play reverb depending on the surroundings. From a point
					// in front of the camera the disance is measured to the
					// nearest obstacle (building)
	float	SoundDistUp; //, SoundDistLeft, SoundDistRight;		// These ones are buffered and should be used by the audio
	float	SoundDistUpAsRead; //, SoundDistLeftAsRead, SoundDistRightAsRead;
	float	SoundDistUpAsReadOld; //, SoundDistLeftAsReadOld, SoundDistRightAsReadOld;
					// Very rough distance to the nearest water for the sound to use
					// Front vector X&Y normalised to 1. Used by loads of stuff.

	
	float	m_fAvoidTheGeometryProbsTimer;
	short	m_nAvoidTheGeometryProbsDirn;
	
	float 	m_fWideScreenReductionAmount;//0 for not reduced 1 for fully reduced (Variable for Les)
	float   m_fStartingFOVForInterPol;
	
		// These ones are static so that they don't get cleared in CCamera::Init()
	static	float m_fMouseAccelHorzntl;// acceleration multiplier for 1st person controls
	static	float m_fMouseAccelVertical;// acceleration multiplier for 1st person controls
	static	float m_f3rdPersonCHairMultX;
	static	float m_f3rdPersonCHairMultY;

	CCamSAInterface	Cams[3];				// The actual cameras (usually only one of the two is active)
							// And to complicate this we have a third camera, this camera is 
							// used for debugging when we want to have a look at the world.
							// We can't change the camera mode because other objects depend on their

	// #########################################//
	// DATA NOT UPDATED FOR SA  BELOW HERE!!!!! //
	// #########################################//

	void *pToGarageWeAreIn;
	void *pToGarageWeAreInForHackAvoidFirstPerson;
	CQueuedMode m_PlayerMode;
	// The higher priority player camera mode. This one is used
	// for the sniper mode and rocket launcher mode.
	// This one overwrites the m_PlayerMode above.
	CQueuedMode PlayerWeaponMode;
	CVector m_PreviousCameraPosition; //needed to work out speed
	CVector m_RealPreviousCameraPosition; // This cane be used by stuff outside the camera code. The one above is the same as the current coordinates outwidth the camera code.
										// an active camera for range finding etc
	CVector m_cvecAimingTargetCoors;		// Coors to look at with Gordons aiming thing
	// The player camera that is waiting to be used
	// This camera can replace the default camera where this is
	// needed (in tricky situations like tunnels for instance)
	CVector m_vecFixedModeVector;
	CVector m_vecFixedModeSource;
	CVector m_vecFixedModeUpOffSet;
	CVector m_vecCutSceneOffset;
	CVector m_cvecStartingSourceForInterPol;
	CVector m_cvecStartingTargetForInterPol;
	CVector m_cvecStartingUpForInterPol;
	CVector m_cvecSourceSpeedAtStartInter;
	CVector m_cvecTargetSpeedAtStartInter;
	CVector m_cvecUpSpeedAtStartInter;
	CVector m_vecSourceWhenInterPol;
	CVector m_vecTargetWhenInterPol;
	CVector m_vecUpWhenInterPol;
	CVector m_vecClearGeometryVec;
	CVector m_vecGameCamPos;
	CVector SourceDuringInter, TargetDuringInter, UpDuringInter;


	CVector m_vecAttachedCamOffset; // for attaching the camera to a ped or vehicle (set by level designers for use in cutscenes)
	CVector m_vecAttachedCamLookAt;	
	FLOAT m_fAttachedCamAngle; // for giving the attached camera a tilt.

	// RenderWare camera pointer
	DWORD * m_pRwCamera; // was RwCamera *
	///stuff for cut scenes
	CEntitySAInterface *pTargetEntity;
	CEntitySAInterface *pAttachedEntity;
	//CVector CutScene; 
	CCamPathSplines m_arrPathArray[MAX_NUM_OF_SPLINETYPES]; //These only get created when the script calls the load splines function
	// maybe this shouldn't be here depends if GTA_TRAIN is defined (its not)
	//CTrainCamNode 	m_arrTrainCamNode[MAX_NUM_OF_NODES];

	bool m_bMirrorActive;
	bool m_bResetOldMatrix;

//	protected:
	CMatrix_Padded m_cameraMatrix;
	CMatrix_Padded m_cameraMatrixOld;
	CMatrix_Padded m_viewMatrix;
	CMatrix_Padded m_matInverse;
	CMatrix_Padded m_matMirrorInverse;
	CMatrix_Padded m_matMirror;

	CVector m_vecFrustumNormals[4];
	CVector m_vecFrustumWorldNormals[4];
	CVector m_vecFrustumWorldNormals_Mirror[4];

	FLOAT m_fFrustumPlaneOffsets[4];
	FLOAT m_fFrustumPlaneOffsets_Mirror[4];

	CVector m_vecRightFrustumNormal;
	CVector m_vecBottomFrustumNormal;
	CVector m_vecTopFrustumNormal;

	CVector m_vecOldSourceForInter;
	CVector m_vecOldFrontForInter;
	CVector m_vecOldUpForInter;
	FLOAT 	m_vecOldFOVForInter;
	FLOAT 	m_fFLOATingFade;//variable representing the FLOAT version of CDraw::Fade. Necessary to stop loss of precision
	FLOAT 	m_fFLOATingFadeMusic;
	FLOAT 	m_fTimeToFadeOut;
	FLOAT 	m_fTimeToFadeMusic;
	FLOAT	m_fTimeToWaitToFadeMusic;
	FLOAT   m_fFractionInterToStopMoving; 
	FLOAT 	m_fFractionInterToStopCatchUp;
	FLOAT   m_fFractionInterToStopMovingTarget; 
	FLOAT 	m_fFractionInterToStopCatchUpTarget;

	FLOAT 	m_fGaitSwayBuffer;
	FLOAT   m_fScriptPercentageInterToStopMoving;
	FLOAT   m_fScriptPercentageInterToCatchUp;
	DWORD	m_fScriptTimeForInterPolation;


	short 	m_iFadingDirection;
	int 	m_iModeObbeCamIsInForCar;
	short 	m_iModeToGoTo;
	short 	m_iMusicFadingDirection;
	short 	m_iTypeOfSwitch;

	DWORD 	m_uiFadeTimeStarted;
	DWORD 	m_uiFadeTimeStartedMusic;
};

class CPedFlags
{
public:
unsigned int bIsStanding : 1; // is ped standing on something
unsigned int bWasStanding : 1; // was ped standing on something
unsigned int bIsLooking : 1; // is ped looking at something or in a direction
unsigned int bIsRestoringLook : 1; // is ped restoring head postion from a look
unsigned int bIsAimingGun : 1; // is ped aiming gun
unsigned int bIsRestoringGun : 1; // is ped moving gun back to default posn
unsigned int bCanPointGunAtTarget : 1; // can ped point gun at target
unsigned int bIsTalking : 1; // is ped talking(see Chat())

unsigned int bInVehicle : 1; // is in a vehicle
unsigned int bIsInTheAir : 1; // is in the air
unsigned int bIsLanding : 1; // is landing after being in the air
unsigned int bHitSomethingLastFrame : 1; // has been in a collision last fram
unsigned int bIsNearCar : 1; // has been in a collision last fram
unsigned int bRenderPedInCar : 1; // has been in a collision last fram
unsigned int bUpdateAnimHeading : 1; // update ped heading due to heading change during anim sequence
unsigned int bRemoveHead : 1; // waiting on AntiSpazTimer to remove head

unsigned int bFiringWeapon : 1; // is pulling trigger
unsigned int bHasACamera : 1; // does ped possess a camera to document accidents
unsigned int bPedIsBleeding : 1; // Ped loses a lot of blood if true
unsigned int bStopAndShoot : 1; // Ped cannot reach target to attack with fist, need to use gun
unsigned int bIsPedDieAnimPlaying : 1; // is ped die animation finished so can dead now
unsigned int bStayInSamePlace :1; // when set, ped stays put
unsigned int bKindaStayInSamePlace :1; // when set, ped doesn't seek out opponent or cover large distances. Will still shuffle and look for cover
unsigned int bBeingChasedByPolice :1; // use nodes for routefind

unsigned int bNotAllowedToDuck :1; // Is this ped allowed to duck at all?
unsigned int bCrouchWhenShooting :1; // duck behind cars etc
unsigned int bIsDucking :1; // duck behind cars etc
unsigned int bGetUpAnimStarted :1; // don't want to play getup anim if under something
unsigned int bDoBloodyFootprints :1; // unsigned int bIsLeader :1;
unsigned int bDontDragMeOutCar :1;
unsigned int bStillOnValidPoly :1; // set if the polygon the ped is on is still valid for collision
unsigned int bAllowMedicsToReviveMe :1;

unsigned int bResetWalkAnims :1;
unsigned int bOnBoat :1; // flee but only using nodes
unsigned int bBusJacked :1; // flee but only using nodes
unsigned int bFadeOut :1; // set if you want ped to fade out
unsigned int bKnockedUpIntoAir :1; // has ped been knocked up into the air by a car collision
unsigned int bHitSteepSlope :1; // has ped collided/is standing on a steep slope (surface type)
unsigned int bCullExtraFarAway :1; // special ped only gets culled if it's extra far away (for roadblocks)
unsigned int bTryingToReachDryLand :1; // has ped just exited boat and trying to get to dry land

unsigned int bCollidedWithMyVehicle :1;
unsigned int bRichFromMugging :1; // ped has lots of cash cause they've been mugging people
unsigned int bChrisCriminal :1; // Is a criminal as killed during Chris' police mission (should be counted as such)
unsigned int bShakeFist :1; // test shake hand at look entity
unsigned int bNoCriticalHits : 1; // ped cannot be killed by a single bullet
unsigned int bHasAlreadyBeenRecorded : 1; // Used for replays
unsigned int bUpdateMatricesRequired : 1; // if PedIK has altered bones so matrices need updated this frame
unsigned int bFleeWhenStanding :1; //

unsigned int bMiamiViceCop :1;  //
unsigned int bMoneyHasBeenGivenByScript :1; //
unsigned int bHasBeenPhotographed :1;  //
unsigned int bIsDrowning : 1;
unsigned int bDrownsInWater : 1;
unsigned int bHeadStuckInCollision : 1;
unsigned int bDeadPedInFrontOfCar :1;
unsigned int bStayInCarOnJack :1;

unsigned int bDontFight :1;
unsigned int bDoomAim :1;
unsigned int bCanBeShotInVehicle : 1;
unsigned int bPushedAlongByCar :1; // ped is getting pushed along by car collision (so don't take damage from horz velocity)
unsigned int bNeverEverTargetThisPed :1;
unsigned int bThisPedIsATargetPriority :1;
unsigned int bCrouchWhenScared :1;
unsigned int bKnockedOffBike :1;

unsigned int bDonePositionOutOfCollision :1;
unsigned int bDontRender : 1;
unsigned int bHasBeenAddedToPopulation :1;
unsigned int bHasJustLeftCar :1;
unsigned int bIsInDisguise :1;
unsigned int bDoesntListenToPlayerGroupCommands :1;
unsigned int bIsBeingArrested :1;
unsigned int bHasJustSoughtCover :1;

unsigned int bKilledByStealth :1;
unsigned int bDoesntDropWeaponsWhenDead :1;
unsigned int bCalledPreRender :1;
unsigned int bBloodPuddleCreated : 1; // Has a static puddle of blood been created yet
unsigned int bPartOfAttackWave :1;
unsigned int bClearRadarBlipOnDeath :1;
unsigned int bNeverLeavesGroup :1; // flag that we want to test 3 extra spheres on col model
unsigned int bTestForBlockedPositions :1; // this sets these indicator flags for various posisions on the front of the ped

unsigned int bRightArmBlocked :1;
unsigned int bLeftArmBlocked :1;
unsigned int bDuckRightArmBlocked :1;
unsigned int bMidriffBlockedForJump :1;
unsigned int bFallenDown :1;
unsigned int bUseAttractorInstantly :1;
unsigned int bDontAcceptIKLookAts :1;
unsigned int bHasAScriptBrain : 1;

unsigned int bWaitingForScriptBrainToLoad : 1;
unsigned int bHasGroupDriveTask :1;
unsigned int bCanExitCar :1;
unsigned int CantBeKnockedOffBike :2; // 0=Default(harder for mission peds) 1=Never 2=Always normal(also for mission peds)
unsigned int bHasBeenRendered : 1;
unsigned int bIsCached :1;
unsigned int bPushOtherPeds :1; // GETS RESET EVERY FRAME - SET IN TASK: want to push other peds around (eg. leader of a group or ped trying to get in a car)
unsigned int bHasBulletProofVest :1;

unsigned int bUsingMobilePhone :1;
unsigned int bUpperBodyDamageAnimsOnly :1;
unsigned int bStuckUnderCar :1;
unsigned int bKeepTasksAfterCleanUp :1; // If true ped will carry on with task even after cleanup
unsigned int bIsDyingStuck :1;
unsigned int bIgnoreHeightCheckOnGotoPointTask :1; // set when walking round buildings, reset when task quits
unsigned int bForceDieInCar:1;
unsigned int bCheckColAboveHead:1;

unsigned int bIgnoreWeaponRange : 1;
unsigned int bDruggedUp : 1;
unsigned int bWantedByPolice : 1; // if this is set, the cops will always go after this ped when they are doing a KillCriminal task
unsigned int bSignalAfterKill: 1;
unsigned int bCanClimbOntoBoat :1;
unsigned int bPedHitWallLastFrame: 1; // useful to store this so that AI knows (normal will still be available)
unsigned int bIgnoreHeightDifferenceFollowingNodes: 1;
unsigned int bMoveAnimSpeedHasBeenSetByTask: 1;

unsigned int bGetOutUpsideDownCar :1;
unsigned int bJustGotOffTrain :1;
unsigned int bDeathPickupsPersist :1;
unsigned int bTestForShotInVehicle :1;
//#ifdef GTA_REPLAY
unsigned int bUsedForReplay : 1; // This ped is controlled by replay and should be removed when replay is done.
//#endif

};

class CWeaponSAInterface
{
public:
	DWORD		m_eWeaponType;
	DWORD	m_eState;
	DWORD			m_nAmmoInClip;
	DWORD			m_nAmmoTotal;
	DWORD			m_nTimer;
	DWORD			m_Unknown;
    DWORD           m_Unknown_2;
};

class CPedSoundSAInterface
{
public:
    BYTE ucPad1[0x92];
    short m_sVoiceType;
    short m_sVoiceID;
};

class CPedSAInterface;

class CFightManagerInterface
{
public:
    BYTE			Pad1 [ 16 ];
	BYTE			UnknownState;
	BYTE			Pad2 [ 3 ];
	float			fStrafeState;
	float			fForwardBackwardState;
};

enum eWeaponSlot
{
	WEAPONSLOT_TYPE_UNARMED = 0,
	WEAPONSLOT_TYPE_MELEE,
	WEAPONSLOT_TYPE_HANDGUN,
	WEAPONSLOT_TYPE_SHOTGUN,
	WEAPONSLOT_TYPE_SMG,		//4
	WEAPONSLOT_TYPE_MG,	
	WEAPONSLOT_TYPE_RIFLE,
	WEAPONSLOT_TYPE_HEAVY,
	WEAPONSLOT_TYPE_THROWN,
	WEAPONSLOT_TYPE_SPECIAL,	//9
	WEAPONSLOT_TYPE_GIFT,  		//10
	WEAPONSLOT_TYPE_PARACHUTE,	//11
	WEAPONSLOT_TYPE_DETONATOR,	//12

    WEAPONSLOT_MAX
};

class CPedIntelligenceSAInterface 
{
public:
// CEventHandlerHistory @ + 56
	CPedSAInterface *           pPed;
	DWORD               	    taskManager;	    // +4 (really CTaskManagerSAInterface)
    BYTE                        bPad[16];
    CFightManagerInterface *    fightInterface;     // +24
    BYTE                        bPad2[184];
    DWORD                       vehicleScanner;     // +212 (really CVehicleScannerSAInterface)
};

class CTaskTimer
{
public:
    DWORD dwTimeStart; // ?
    DWORD dwTimeEnd; // ?
    bool bSet;
    bool bStopped;
};

class TaskVTBL
{
public:
	DWORD DeletingDestructor;
	DWORD Clone;
	DWORD GetSubTask;
	DWORD IsSimpleTask;
	DWORD GetTaskType;
	DWORD StopTimer;
	DWORD MakeAbortable;
};

class TaskSimpleVTBL : public TaskVTBL
{
public:
	DWORD ProcessPed;
	DWORD SetPedPosition;
};

class TaskComplexVTBL : public TaskVTBL
{
public:
	DWORD SetSubTask; 
	DWORD CreateNextSubTask;
	DWORD CreateFirstSubTask;
	DWORD ControlSubTask;
};

class CTaskSAInterface
{
public:
	TaskVTBL * VTBL; // cast to either TaskSimpleVTBL or TaskComplexVTBL
	CTaskSAInterface * m_pParent;
};

class CTaskSimpleSAInterface : public CTaskSAInterface
{
	public:
};

class CTaskSimpleGangDriveBySAInterface : public CTaskSimpleSAInterface
{
public:
	bool m_bIsFinished;
    bool m_bAnimsReferenced;
    bool m_bSeatRHS;
    bool m_bInRangeToShoot;
    bool m_bInWeaponRange;
    bool m_bReachedAbortRange;
    bool m_bFromScriptCommand;

	char m_nNextCommand;
	char m_nLastCommand;	// active command
	char m_nBurstShots;
	char m_nDrivebyStyle;		// what type of driveby are we doing
	char m_nFrequencyPercentage;
	char m_nFakeShootDirn;
	short m_nAttackTimer;
	
	unsigned int m_nLOSCheckTime;
	bool m_nLOSBlocked;
	
	float m_fAbortRange;		// range from target at which this task will be aborted

	DWORD m_nRequiredAnim;
	DWORD m_nRequiredAnimGroup;
	void *m_pAnim;
	void *m_pWeaponInfo;

	void *m_pTargetEntity;
    CVector m_vecCoords;
};

class CPedSAInterface : public CPhysicalSAInterface // +1420  = current vehicle   312 first byte
{
public:
    // current weapon slot 1184 ( and +1816?)
	//CPedIKSAInterface		pedIK; // 528
	//CWeaponSAInterface	Weapons[9];	// 1032
	BYTE bPad[348];
    CPedSoundSAInterface pedSound;
    BYTE bPad11[472 - sizeof(CPedSoundSAInterface)];
    CPedFlags pedFlags; // 1132 (16 bytes long including alignment probably)
    CPedIntelligenceSAInterface * pPedIntelligence;
    void * pPlayerData; //1152
    BYTE bPad4a[80];
    int iMoveAnimGroup;      // 1236
    BYTE bPad4b[52];
    BYTE pedIK[32]; // 1292 (length 32 bytes)
    int bPad5[5];

    float fHealth;
    int  iUnknown121;
    float fArmor;

    int iUnknown313 [3];        // +1356
    // +1368 = rotation
    float fCurrentRotation;
    float fTargetRotation;
    float fRotationSpeed;
    BYTE bPad8[4];
    CEntitySAInterface * pContactEntity;
    BYTE bPad3[32];
	CEntitySAInterface * CurrentObjective; // current vehicle    1420
    BYTE bPad2[8];
	BYTE bPedType;	// ped type? 0 = player, >1 = ped?
	BYTE bPad9[7];
    CWeaponSAInterface      Weapons[WEAPONSLOT_MAX];
    //weapons at +1440 ends at +1804
    BYTE bPad4[12];
    BYTE bCurrentWeaponSlot; // is actually here
    BYTE bPad6[20];
    BYTE bFightingStyle; // 1837
    BYTE bFightingStyleExtra;
    BYTE bPad7[1];
    void* pFireOnPed;
    BYTE bPad10[104];
    CEntitySAInterface * pTargetedEntity; // 1948
};

enum 
{
    TASK_PRIORITY_PHYSICAL_RESPONSE=0,
    TASK_PRIORITY_EVENT_RESPONSE_TEMP,
    TASK_PRIORITY_EVENT_RESPONSE_NONTEMP,
    TASK_PRIORITY_PRIMARY,
    TASK_PRIORITY_DEFAULT,
    TASK_PRIORITY_MAX
};

enum
{
	TASK_SECONDARY_ATTACK=0,				// want duck to be after attack
	TASK_SECONDARY_DUCK,				    // because attack controls ducking movement
	TASK_SECONDARY_SAY,
	TASK_SECONDARY_FACIAL_COMPLEX,
	TASK_SECONDARY_PARTIAL_ANIM,
	TASK_SECONDARY_IK,
	TASK_SECONDARY_MAX
};

class CTaskManagerSAInterface
{
public:
    CTaskSAInterface	* m_tasks[TASK_PRIORITY_MAX];  
    CTaskSAInterface	* m_tasksSecondary[TASK_SECONDARY_MAX];

    CPedSAInterface		* m_pPed;    
};

#define FUNC_CTask__Operator_New			0x61A5A0
#define FUNC_CTaskSimpleGangDriveBy__Constructor        0x6217d0
#define FUNC_SetTask					0x681AF0

public ref class NativeFunctions {
public:
	static void OverridePedSpawn(cli::array<int>^ peds);
	static void PlayFrontendAudio(int audioID);
	static float GetCameraFOV();
	static void SetCameraFOV(float value);

	static SVector^ GetScreenCoords(SVector^ world);
};
}

#endif