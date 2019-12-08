/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto v1.0
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        game_sa/CPadSA.h
*  PURPOSE:     Header file for controller pad input class
*  DEVELOPERS:  Ed Lyons <eai@opencoding.net>
*               Christian Myhre Lundheim <>
*               Jax <>
*
*  Multi Theft Auto is available from http://www.multitheftauto.com/
*
*****************************************************************************/
//
#ifndef __CGAMESA_PAD
#define __CGAMESA_PAD

// Set values to 128 unless otherwise specified
public value class ControllerState
{
public:
	signed short LeftStickX; // move/steer left (-128?)/right (+128)
	signed short LeftStickY; // move back(+128)/forwards(-128?)
	signed short RightStickX; // numpad 6(+128)/numpad 4(-128?)
	signed short RightStickY;
	
	signed short LeftShoulder1;
	signed short LeftShoulder2;
	signed short RightShoulder1; // target / hand brake
	signed short RightShoulder2; 
	
	signed short DPadUp; // radio change up
	signed short DPadDown; // radio change down
	signed short DPadLeft;
	signed short DPadRight;

	signed short Start;
	signed short Select;

	signed short ButtonSquare; // jump / reverse
	signed short ButtonTriangle; // get in/out
	signed short ButtonCross; // sprint / accelerate
	signed short ButtonCircle; // fire

	signed short ShockButtonL;
	signed short ShockButtonR; // look behind

	signed short m_bChatIndicated;
	signed short m_bPedWalk;
	signed short m_bVehicleMouseLook;
	signed short m_bRadioTrackSkip;

/*	ControllerState() { 
		memset(this, 0, sizeof(ControllerState));
	}*/
};

class CControllerState
{
public:
	signed short LeftStickX; // move/steer left (-128?)/right (+128)
	signed short LeftStickY; // move back(+128)/forwards(-128?)
	signed short RightStickX; // numpad 6(+128)/numpad 4(-128?)
	signed short RightStickY;
	
	signed short LeftShoulder1;
	signed short LeftShoulder2;
	signed short RightShoulder1; // target / hand brake
	signed short RightShoulder2; 
	
	signed short DPadUp; // radio change up
	signed short DPadDown; // radio change down
	signed short DPadLeft;
	signed short DPadRight;

	signed short Start;
	signed short Select;

	signed short ButtonSquare; // jump / reverse
	signed short ButtonTriangle; // get in/out
	signed short ButtonCross; // sprint / accelerate
	signed short ButtonCircle; // fire

	signed short ShockButtonL;
	signed short ShockButtonR; // look behind

	signed short m_bChatIndicated;
	signed short m_bPedWalk;
	signed short m_bVehicleMouseLook;
	signed short m_bRadioTrackSkip;

	CControllerState() { 
		memset(this, 0, sizeof(CControllerState));
	}
};

#define MAX_HORN_HISTORY		5
#define STEERINGBUFFERLENGTH	10

#define FUNC_CPad_UpdatePads				0x541DD0

class CPadSAInterface
{
public:
	CControllerState	NewState;
	CControllerState	OldState;
	
	signed short 		SteeringLeftRightBuffer[STEERINGBUFFERLENGTH];
	signed long			DrunkDrivingBufferUsed;

	//120
	CControllerState	PCTempKeyState;
	//168
	CControllerState	PCTempJoyState;
	//216
	CControllerState	PCTempMouseState;
	//264
	BYTE				Phase;		// needed for switching into right state (analogue, pressure sensitive etc)
	WORD				Mode;		// Configuration of keys as selected by the player
	signed short		ShakeDur;	// How long will shake go on for (in msecs)
	WORD				DisablePlayerControls;		// If TRUE then the player cannot move, shoot, etc.
	BYTE				ShakeFreq;	// What is the frequency of the shake
	bool				bHornHistory[MAX_HORN_HISTORY]; // Store last 4 states of the horn key TRUE on else FALSE
	BYTE				iCurrHornHistory;				// Where to store new history value
	BYTE				JustOutOfFrontEnd;			// Number of frames we want some of the controls disabled for.
	bool				bApplyBrakes;				// If TRUE then apply the brakes to the player's vehicle
	bool				bDisablePlayerEnterCar;		// Script can set this so that the Enter Car button can be used to pick up objects
	bool				bDisablePlayerDuck;			// Script can set this
	bool				bDisablePlayerFireWeapon;	// Script can set this
	bool				bDisablePlayerFireWeaponWithL1;	//	Script can set this - for Judith's mission where L1 is needed to pick up objects
	bool				bDisablePlayerCycleWeapon;	// Script can set this
	bool				bDisablePlayerJump;			// Script can set this
	bool				bDisablePlayerDisplayVitalStats;	// Script can set this
	DWORD				LastTimeTouched;			// The time the last input was applied by the player
	signed long			AverageWeapon;		// Average value of the weapon button (analogue) since last reset
	signed long			AverageEntries;

	DWORD				NoShakeBeforeThis;
	BYTE				NoShakeFreq;
};

public ref class Pad
{
private:
	CPadSAInterface		* internalInterface;
	CPadSAInterface		* StoredPad;
public:
	// constructor
	Pad(CPadSAInterface * padInterface) { this->internalInterface = padInterface; };
	Pad(System::IntPtr padInterface)	{ this->internalInterface = (CPadSAInterface*)padInterface.ToPointer(); };

	void				DisableCircle(bool yes);
	void				DisableStatDisplay(bool yes);

	CControllerState	* GetCurrentControllerState(CControllerState * ControllerState);
	CControllerState	* GetLastControllerState(CControllerState * ControllerState);
	VOID				SetCurrentControllerState(CControllerState * ControllerState);
	VOID				SetLastControllerState(CControllerState * ControllerState);
	ControllerState		GetCCurrentControllerState();
	ControllerState		GetCLastControllerState();
	VOID				SetCCurrentControllerState(ControllerState ControllerState);
	VOID				SetCLastControllerState(ControllerState ControllerState);
	VOID				Store();
	VOID				Restore();
    bool                IsEnabled ( void );
	VOID				Disable( bool bDisable );
	VOID				Clear ( void );
	CPadSAInterface		* GetInterface() { return this->internalInterface; };
    VOID                SetHornHistoryValue( bool value );
    long                GetAverageWeapon ( void );
    void                SetLastTimeTouched ( DWORD dwTime );

	void				SetControlMode (BYTE mode) {
		//this->internalInterface->Mode = mode;
		if (mode == 0) {
			*(BYTE*)0xB6EC2E = 1;
		} else {
			*(BYTE*)0xB6EC2E = 0;
		}

		*(BYTE*)0xBA6818 = mode;
	}

	BYTE GetShakeFreq() {
		return this->internalInterface->ShakeFreq;
	}
};

#endif