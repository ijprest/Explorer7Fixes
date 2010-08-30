/*SDOC**********************************************************************

	$Header$

	Module:				stdafx.h

	Copyright (C) 2010 Ian Prest

	Description:	Precompiled header

***********************************************************************EDOC*/
#ifndef __STDAFX_H
#define __STDAFX_H
#pragma once

// Windows headers
#define STRICT
#define WINVER					0x0600
#define _WIN32_WINNT		0x0600
#define _WIN32_WINDOWS	0x0410
#define _WIN32_IE				0x0700
#define WIN32_LEAN_AND_MEAN	// Exclude rarely-used stuff from Windows headers
#include <windows.h>

// ATL headers
#define _ATL_APARTMENT_THREADED
#define _ATL_NO_AUTOMATIC_NAMESPACE
#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS
#include <atlbase.h>
#include <atlcom.h>
#include <atlctl.h>
#include <atlstr.h>
using namespace ATL;

// Shell headers
#include <shobjidl.h>
#include <exdispid.h>
#include <shlguid.h>
#include <shlobj.h>

// Resource IDs
#define IDR_EXPLORER7FIXES	1000
#define IDR_BHO							1001

extern HINSTANCE g_Instance;

#endif // __STDAFX_H
