/*****************************************************************************
*
*  PROJECT:     Multi Theft Auto v1.0
*  LICENSE:     See LICENSE in the top level directory
*  FILE:        game_sa/Pad.cpp
*  PURPOSE:     Controller pad input logic
*  DEVELOPERS:  Ed Lyons <eai@opencoding.net>
*               Christian Myhre Lundheim <>
*               Jax <>
*
*  Multi Theft Auto is available from http://www.multitheftauto.com/
*
*****************************************************************************/

#include "stdafx.h"
#ifdef GTA_SA
#include "CPadSA.h"

ControllerState Pad::GetCCurrentControllerState()
{
	//DEBUG_TRACE("CControllerState * Pad::GetCurrentControllerState(CControllerState * ControllerState)");
	ControllerState State;
	//memcpy(&ControllerState, &this->internalInterface->NewState, sizeof(CControllerState));
	CControllerState OrigState = this->internalInterface->PCTempJoyState;

	State.LeftStickX = OrigState.LeftStickX; // move/steer left (-128?)/right (+128)
	State.LeftStickY = OrigState.LeftStickY; // move back(+128)/forwards(-128?)
	State.RightStickX = OrigState.RightStickX; // numpad 6(+128)/numpad 4(-128?)
	State.RightStickY = OrigState.RightStickY;
	
	State.LeftShoulder1 = OrigState.LeftShoulder1;
	State.LeftShoulder2 = OrigState.LeftShoulder2;
	State.RightShoulder1 = OrigState.RightShoulder1; // target / hand brake
	State.RightShoulder2 = OrigState.RightShoulder2; 
	
	State.DPadUp = OrigState.DPadUp; // radio change up
	State.DPadDown = OrigState.DPadDown; // radio change down
	State.DPadLeft = OrigState.DPadLeft;
	State.DPadRight = OrigState.DPadRight;

	State.Start = OrigState.Start;
	State.Select = OrigState.Select;

	State.ButtonSquare = OrigState.ButtonSquare; // jump / reverse
	State.ButtonTriangle = OrigState.ButtonTriangle; // get in/out
	State.ButtonCross = OrigState.ButtonCross; // sprint / accelerate
	State.ButtonCircle = OrigState.ButtonCircle; // fire

	State.ShockButtonL = OrigState.ShockButtonL;
	State.ShockButtonR = OrigState.ShockButtonR; // look behind

	State.m_bChatIndicated = OrigState.m_bChatIndicated;
	State.m_bPedWalk = OrigState.m_bPedWalk;
	State.m_bVehicleMouseLook = OrigState.m_bVehicleMouseLook;
	State.m_bRadioTrackSkip = OrigState.m_bRadioTrackSkip;
	return State;
}

ControllerState Pad::GetCLastControllerState()
{
	//DEBUG_TRACE("CControllerState * Pad::GetLastControllerState(CControllerState * ControllerState)");
	ControllerState State;
	//memcpy(&ControllerState, &this->internalInterface->NewState, sizeof(CControllerState));
	CControllerState OrigState = this->internalInterface->OldState;

	State.LeftStickX = OrigState.LeftStickX; // move/steer left (-128?)/right (+128)
	State.LeftStickY = OrigState.LeftStickY; // move back(+128)/forwards(-128?)
	State.RightStickX = OrigState.RightStickX; // numpad 6(+128)/numpad 4(-128?)
	State.RightStickY = OrigState.RightStickY;
	
	State.LeftShoulder1 = OrigState.LeftShoulder1;
	State.LeftShoulder2 = OrigState.LeftShoulder2;
	State.RightShoulder1 = OrigState.RightShoulder1; // target / hand brake
	State.RightShoulder2 = OrigState.RightShoulder2; 
	
	State.DPadUp = OrigState.DPadUp; // radio change up
	State.DPadDown = OrigState.DPadDown; // radio change down
	State.DPadLeft = OrigState.DPadLeft;
	State.DPadRight = OrigState.DPadRight;

	State.Start = OrigState.Start;
	State.Select = OrigState.Select;

	State.ButtonSquare = OrigState.ButtonSquare; // jump / reverse
	State.ButtonTriangle = OrigState.ButtonTriangle; // get in/out
	State.ButtonCross = OrigState.ButtonCross; // sprint / accelerate
	State.ButtonCircle = OrigState.ButtonCircle; // fire

	State.ShockButtonL = OrigState.ShockButtonL;
	State.ShockButtonR = OrigState.ShockButtonR; // look behind

	State.m_bChatIndicated = OrigState.m_bChatIndicated;
	State.m_bPedWalk = OrigState.m_bPedWalk;
	State.m_bVehicleMouseLook = OrigState.m_bVehicleMouseLook;
	State.m_bRadioTrackSkip = OrigState.m_bRadioTrackSkip;
	return State;
}

void Pad::DisableCircle(bool yes) {
	this->internalInterface->bDisablePlayerJump = yes;
}

void Pad::DisableStatDisplay(bool yes) {
	this->internalInterface->bDisablePlayerDisplayVitalStats = yes;
}

VOID Pad::SetCCurrentControllerState(ControllerState State)
{
	//DEBUG_TRACE("VOID Pad::SetCurrentControllerState(CControllerState * ControllerState)");
	//memcpy(&this->internalInterface->NewState, &ControllerState, sizeof(CControllerState));
	memset(&this->internalInterface->PCTempJoyState, 0x00, sizeof(CControllerState));
	this->internalInterface->PCTempJoyState.LeftStickX = State.LeftStickX; // move/steer left (-128?)/right (+128)
	this->internalInterface->PCTempJoyState.LeftStickY = State.LeftStickY; // move back(+128)/forwards(-128?)
	this->internalInterface->PCTempJoyState.RightStickX = State.RightStickX; // numpad 6(+128)/numpad 4(-128?)
	this->internalInterface->PCTempJoyState.RightStickY = State.RightStickY;
	
	this->internalInterface->PCTempJoyState.LeftShoulder1 = State.LeftShoulder1;
	this->internalInterface->PCTempJoyState.LeftShoulder2 = State.LeftShoulder2;
	this->internalInterface->PCTempJoyState.RightShoulder1 = State.RightShoulder1; // target / hand brake
	this->internalInterface->PCTempJoyState.RightShoulder2 = State.RightShoulder2; 
	
	this->internalInterface->PCTempJoyState.DPadUp = State.DPadUp; // radio change up
	this->internalInterface->PCTempJoyState.DPadDown = State.DPadDown; // radio change down
	this->internalInterface->PCTempJoyState.DPadLeft = State.DPadLeft;
	this->internalInterface->PCTempJoyState.DPadRight = State.DPadRight;

	this->internalInterface->PCTempJoyState.Start = State.Start;
	this->internalInterface->PCTempJoyState.Select = State.Select;

	this->internalInterface->PCTempJoyState.ButtonSquare = State.ButtonSquare; // jump / reverse
	this->internalInterface->PCTempJoyState.ButtonTriangle = State.ButtonTriangle; // get in/out
	this->internalInterface->PCTempJoyState.ButtonCross = State.ButtonCross; // sprint / accelerate
	this->internalInterface->PCTempJoyState.ButtonCircle = State.ButtonCircle; // fire

	this->internalInterface->PCTempJoyState.ShockButtonL = State.ShockButtonL;
	this->internalInterface->PCTempJoyState.ShockButtonR = State.ShockButtonR; // look behind

	this->internalInterface->PCTempJoyState.m_bChatIndicated = State.m_bChatIndicated;
	this->internalInterface->PCTempJoyState.m_bPedWalk = State.m_bPedWalk;
	this->internalInterface->PCTempJoyState.m_bVehicleMouseLook = State.m_bVehicleMouseLook;
	this->internalInterface->PCTempJoyState.m_bRadioTrackSkip = State.m_bRadioTrackSkip;

	/*this->internalInterface->PCTempKeyState.LeftStickX = State.LeftStickX; // move/steer left (-128?)/right (+128)
	this->internalInterface->PCTempKeyState.LeftStickY = State.LeftStickY; // move back(+128)/forwards(-128?)
	this->internalInterface->PCTempKeyState.RightStickX = State.RightStickX; // numpad 6(+128)/numpad 4(-128?)
	this->internalInterface->PCTempKeyState.RightStickY = State.RightStickY;
	
	this->internalInterface->PCTempKeyState.LeftShoulder1 = State.LeftShoulder1;
	this->internalInterface->PCTempKeyState.LeftShoulder2 = State.LeftShoulder2;
	this->internalInterface->PCTempKeyState.RightShoulder1 = State.RightShoulder1; // target / hand brake
	this->internalInterface->PCTempKeyState.RightShoulder2 = State.RightShoulder2; 
	
	this->internalInterface->PCTempKeyState.DPadUp = State.DPadUp; // radio change up
	this->internalInterface->PCTempKeyState.DPadDown = State.DPadDown; // radio change down
	this->internalInterface->PCTempKeyState.DPadLeft = State.DPadLeft;
	this->internalInterface->PCTempKeyState.DPadRight = State.DPadRight;

	this->internalInterface->PCTempKeyState.Start = State.Start;
	this->internalInterface->PCTempKeyState.Select = State.Select;

	this->internalInterface->PCTempKeyState.ButtonSquare = State.ButtonSquare; // jump / reverse
	this->internalInterface->PCTempKeyState.ButtonTriangle = State.ButtonTriangle; // get in/out
	this->internalInterface->PCTempKeyState.ButtonCross = State.ButtonCross; // sprint / accelerate
	this->internalInterface->PCTempKeyState.ButtonCircle = State.ButtonCircle; // fire

	this->internalInterface->PCTempKeyState.ShockButtonL = State.ShockButtonL;
	this->internalInterface->PCTempKeyState.ShockButtonR = State.ShockButtonR; // look behind

	this->internalInterface->PCTempKeyState.m_bChatIndicated = State.m_bChatIndicated;
	this->internalInterface->PCTempKeyState.m_bPedWalk = State.m_bPedWalk;
	this->internalInterface->PCTempKeyState.m_bVehicleMouseLook = State.m_bVehicleMouseLook;
	this->internalInterface->PCTempKeyState.m_bRadioTrackSkip = State.m_bRadioTrackSkip;*/

		/*this->internalInterface->NewState.LeftStickX = State.LeftStickX; // move/steer left (-128?)/right (+128)
	this->internalInterface->NewState.LeftStickY = State.LeftStickY; // move back(+128)/forwards(-128?)
	this->internalInterface->NewState.RightStickX = State.RightStickX; // numpad 6(+128)/numpad 4(-128?)
	this->internalInterface->NewState.RightStickY = State.RightStickY;
	
	this->internalInterface->NewState.LeftShoulder1 = State.LeftShoulder1;
	this->internalInterface->NewState.LeftShoulder2 = State.LeftShoulder2;
	this->internalInterface->NewState.RightShoulder1 = State.RightShoulder1; // target / hand brake
	this->internalInterface->NewState.RightShoulder2 = State.RightShoulder2; 
	
	this->internalInterface->NewState.DPadUp = State.DPadUp; // radio change up
	this->internalInterface->NewState.DPadDown = State.DPadDown; // radio change down
	this->internalInterface->NewState.DPadLeft = State.DPadLeft;
	this->internalInterface->NewState.DPadRight = State.DPadRight;

	this->internalInterface->NewState.Start = State.Start;
	this->internalInterface->NewState.Select = State.Select;

	this->internalInterface->NewState.ButtonSquare = State.ButtonSquare; // jump / reverse
	this->internalInterface->NewState.ButtonTriangle = State.ButtonTriangle; // get in/out
	this->internalInterface->NewState.ButtonCross = State.ButtonCross; // sprint / accelerate
	this->internalInterface->NewState.ButtonCircle = State.ButtonCircle; // fire

	this->internalInterface->NewState.ShockButtonL = State.ShockButtonL;
	this->internalInterface->NewState.ShockButtonR = State.ShockButtonR; // look behind

	this->internalInterface->NewState.m_bChatIndicated = State.m_bChatIndicated;
	this->internalInterface->NewState.m_bPedWalk = State.m_bPedWalk;
	this->internalInterface->NewState.m_bVehicleMouseLook = State.m_bVehicleMouseLook;
	this->internalInterface->NewState.m_bRadioTrackSkip = State.m_bRadioTrackSkip;*/
}

VOID Pad::SetCLastControllerState(ControllerState State)
{
	//DEBUG_TRACE("VOID Pad::SetLastControllerState(CControllerState * ControllerState)");
		this->internalInterface->OldState.LeftStickX = State.LeftStickX; // move/steer left (-128?)/right (+128)
	this->internalInterface->OldState.LeftStickY = State.LeftStickY; // move back(+128)/forwards(-128?)
	this->internalInterface->OldState.RightStickX = State.RightStickX; // numpad 6(+128)/numpad 4(-128?)
	this->internalInterface->OldState.RightStickY = State.RightStickY;
	
	this->internalInterface->OldState.LeftShoulder1 = State.LeftShoulder1;
	this->internalInterface->OldState.LeftShoulder2 = State.LeftShoulder2;
	this->internalInterface->OldState.RightShoulder1 = State.RightShoulder1; // target / hand brake
	this->internalInterface->OldState.RightShoulder2 = State.RightShoulder2; 
	
	this->internalInterface->OldState.DPadUp = State.DPadUp; // radio change up
	this->internalInterface->OldState.DPadDown = State.DPadDown; // radio change down
	this->internalInterface->OldState.DPadLeft = State.DPadLeft;
	this->internalInterface->OldState.DPadRight = State.DPadRight;

	this->internalInterface->OldState.Start = State.Start;
	this->internalInterface->OldState.Select = State.Select;

	this->internalInterface->OldState.ButtonSquare = State.ButtonSquare; // jump / reverse
	this->internalInterface->OldState.ButtonTriangle = State.ButtonTriangle; // get in/out
	this->internalInterface->OldState.ButtonCross = State.ButtonCross; // sprint / accelerate
	this->internalInterface->OldState.ButtonCircle = State.ButtonCircle; // fire

	this->internalInterface->OldState.ShockButtonL = State.ShockButtonL;
	this->internalInterface->OldState.ShockButtonR = State.ShockButtonR; // look behind

	this->internalInterface->OldState.m_bChatIndicated = State.m_bChatIndicated;
	this->internalInterface->OldState.m_bPedWalk = State.m_bPedWalk;
	this->internalInterface->OldState.m_bVehicleMouseLook = State.m_bVehicleMouseLook;
	this->internalInterface->OldState.m_bRadioTrackSkip = State.m_bRadioTrackSkip;
}

CControllerState * Pad::GetCurrentControllerState(CControllerState * ControllerState)
{
	//DEBUG_TRACE("CControllerState * Pad::GetCurrentControllerState(CControllerState * ControllerState)");
	memcpy(ControllerState, &this->internalInterface->NewState, sizeof(CControllerState));
	return ControllerState;
}

CControllerState * Pad::GetLastControllerState(CControllerState * ControllerState)
{
	//DEBUG_TRACE("CControllerState * Pad::GetLastControllerState(CControllerState * ControllerState)");
	memcpy(ControllerState, &this->internalInterface->OldState, sizeof(CControllerState));
	return ControllerState;
}

VOID Pad::SetCurrentControllerState(CControllerState * ControllerState)
{
	//DEBUG_TRACE("VOID Pad::SetCurrentControllerState(CControllerState * ControllerState)");
	memcpy(&this->internalInterface->NewState, ControllerState, sizeof(CControllerState));
}

VOID Pad::SetLastControllerState(CControllerState * ControllerState)
{
	//DEBUG_TRACE("VOID Pad::SetLastControllerState(CControllerState * ControllerState)");
	memcpy(&this->internalInterface->OldState, ControllerState, sizeof(CControllerState));
}

VOID Pad::Store()
{
	//DEBUG_TRACE("VOID Pad::Store()");
	memcpy(this->StoredPad, this->internalInterface, sizeof(CPadSAInterface));
}

VOID Pad::Restore()
{
	//DEBUG_TRACE("VOID Pad::Restore()");
	//cli::pin_ptr<CPadSAInterface> ptr = this->StoredPad;
	memcpy(this->internalInterface, this->StoredPad, sizeof(CPadSAInterface));
}

bool Pad::IsEnabled ( void )
{
    bool bEnabled = *(BYTE *)FUNC_CPad_UpdatePads == 0x56;
    return bEnabled;
}

VOID Pad::Disable( bool bDisable )
{
	if ( bDisable )
		*(BYTE *)FUNC_CPad_UpdatePads = 0xC3;
	else
		*(BYTE *)FUNC_CPad_UpdatePads = 0x56;

	//this->internalInterface->DisablePlayerControls = bDisable;
}

VOID Pad::Clear ( void )
{
	CControllerState cs; // create a null controller (class is inited to null)
	SetCurrentControllerState ( &cs );
	SetLastControllerState ( &cs );
}

VOID Pad::SetHornHistoryValue( bool value )
{
    internalInterface->iCurrHornHistory++;
    if ( internalInterface->iCurrHornHistory >= MAX_HORN_HISTORY )
        internalInterface->iCurrHornHistory = 0;
    internalInterface->bHornHistory[internalInterface->iCurrHornHistory] = value;
}

long Pad::GetAverageWeapon ( void )
{
    return internalInterface->AverageWeapon;
}

void Pad::SetLastTimeTouched ( DWORD dwTime )
{
    internalInterface->LastTimeTouched = dwTime;
}
#endif