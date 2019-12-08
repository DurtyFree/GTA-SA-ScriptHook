// some code taken from Multi Theft Auto, licensed under the GPLv3.

#pragma once

#include <windows.h>
#include <math.h>

typedef DWORD RGBA;
typedef DWORD BGRA;
typedef DWORD ARGB;
typedef DWORD ABGR;

#define COLOR_ARGB(a,r,g,b) \
	((ARGB)((((a)&0xff)<<24)|(((r)&0xff)<<16)|(((g)&0xff)<<8)|((b)&0xff)))
#define COLOR_RGBA(r,g,b,a) (RGBA)COLOR_ARGB(a,r,g,b)

#define COLOR_ABGR(a,b,g,r) \
	((ABGR)((((a)&0xff)<<24)|(((b)&0xff)<<16)|(((g)&0xff)<<8)|((r)&0xff)))
#define COLOR_BGRA(b,g,r,a) (BGRA)COLOR_ARGB(a,b,g,r)

/**
 * CVector Structure used to store a 3D vertex.
 */
public class CVector
{
public:
	FLOAT fX, fY, fZ;
	
	CVector() 
	{
		this->fX = 0;
		this->fY = 0;
		this->fZ = 0;
	};
	// contructor
	CVector(FLOAT fX, FLOAT fY, FLOAT fZ) 
	{ 
		this->fX = fX;
		this->fY = fY;
		this->fZ = fZ;
	}

	void Normalize ( void ) 
	{ 
		double t = sqrt(fX*fX + fY*fY + fZ*fZ);
		if ( t > 0 )
		{
			double fX2 = fX / t;
			double fY2 = fY / t;
			double fZ2 = fZ / t;
			fX = (float)fX2;
			fY = (float)fY2;
			fZ = (float)fZ2;
		}
	}

	float Length ( void ) const
	{
		return sqrt((fX*fX) + (fY*fY) + (fZ*fZ));
	}

	float DotProduct ( CVector * param ) const
	{
		return fX*param->fX + fY*param->fY + fZ*param->fZ;
	}

	void CrossProduct ( CVector * param ) 
	{ 
		fX = fY * param->fZ - param->fY * fZ;
		fY = fZ * param->fX - param->fZ * fX;
		fZ = fX * param->fY - param->fX * fY;
	}

	CVector operator + ( const CVector& vecRight ) const
	{
		return CVector ( fX + vecRight.fX, fY + vecRight.fY, fZ + vecRight.fZ );
	}

	CVector operator - ( const CVector& vecRight ) const
	{
		return CVector ( fX - vecRight.fX, fY - vecRight.fY, fZ - vecRight.fZ );
	}

	CVector operator * ( const CVector& vecRight ) const
	{
		return CVector ( fX * vecRight.fX, fY * vecRight.fY, fZ * vecRight.fZ );
	}

	CVector operator * ( float fRight ) const
	{
		return CVector ( fX * fRight, fY * fRight, fZ * fRight );
	}

	CVector operator / ( const CVector& vecRight ) const
	{
		return CVector ( fX / vecRight.fX, fY / vecRight.fY, fZ / vecRight.fZ );
	}

	void operator += ( float fRight )
	{
		fX += fRight;
		fY += fRight;
		fZ += fRight;
	}

	void operator += ( const CVector& vecRight )
	{
		fX += vecRight.fX;
		fY += vecRight.fY;
		fZ += vecRight.fZ;
	}

	void operator -= ( float fRight )
	{
		fX -= fRight;
		fY -= fRight;
		fZ -= fRight;
	}

	void operator -= ( const CVector& vecRight )
	{
		fX -= vecRight.fX;
		fY -= vecRight.fY;
		fZ -= vecRight.fZ;
	}

	void operator *= ( float fRight )
	{
		fX *= fRight;
		fY *= fRight;
		fZ *= fRight;
	}

	void operator *= ( const CVector& vecRight )
	{
		fX *= vecRight.fX;
		fY *= vecRight.fY;
		fZ *= vecRight.fZ;
	}

	void operator /= ( float fRight )
	{
		fX /= fRight;
		fY /= fRight;
		fZ /= fRight;
	}

	void operator /= ( const CVector& vecRight )
	{
		fX /= vecRight.fX;
		fY /= vecRight.fY;
		fZ /= vecRight.fZ;
	}

	bool operator== ( const CVector& param ) const
	{
		return (fX == param.fX && fY == param.fY && fZ == param.fZ);
	}

	bool operator!= ( const CVector& param ) const
	{
		return (fX != param.fX || fY != param.fY || fZ != param.fZ);
	}
};

public class CMatrix
{
public:
	CVector vRoll;
	CVector vDirection;
	CVector vWas;
	CVector vPos;
};

/**
 * CVector Structure used internally by GTA.
 */
public class CMatrix_Padded
{
public:
	CVector vRoll; // 0			RIGHT
	DWORD	 dwPadRoll; // 12
	CVector vDirection; // 16	FOREWARDS
	DWORD	 dwPadDirection; // 28
	CVector vWas; // 32			UP
	DWORD	 dwPadWas; // 44	
	CVector vPos;  // 48		TRANSLATE
	DWORD	 dwPadPos; // 60

	CMatrix_Padded()
	{
		memset ( this, 0, sizeof ( CMatrix_Padded ) );
	}

	CMatrix_Padded ( const CMatrix& Matrix )
	{
		SetFromMatrix ( Matrix );
	}

	void ConvertToMatrix ( CMatrix& Matrix ) const
	{
		Matrix.vPos = vPos;
		Matrix.vDirection = vDirection;
		Matrix.vWas = vWas;
		Matrix.vRoll = vRoll;
	}

	void SetFromMatrix ( const CMatrix& Matrix )
	{
		vPos = Matrix.vPos;
		dwPadPos = 0;

		vDirection = Matrix.vDirection;
		dwPadDirection = 0;

		vWas = Matrix.vWas;
		dwPadWas = 0;

		vRoll = Matrix.vRoll;
		dwPadRoll = 0;
	}
};