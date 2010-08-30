/*SDOC**********************************************************************

	Module:				dllmain.cpp

	Copyright (C) 2010 Ian Prest

	Description:	Defines the entry point for the DLL application.

***********************************************************************EDOC*/
#include "stdafx.h"
#include "Explorer7Fixes_h.h"

// Globals
bool g_bExplorerExe = true;
HINSTANCE g_Instance = NULL;

//**************************************************************************
//************************* CExplorer7Fixes Class **************************
//**************************************************************************
class CExplorer7Fixes : public CAtlDllModuleT<CExplorer7Fixes>
{
public :
	DECLARE_LIBID(LIBID_Explorer7FixesLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_EXPLORER7FIXES, "{fc587279-c98f-0f80-422e-cf3833b6c78e}")
} _AtlModule;


/*SDOC**********************************************************************

	Name:			DllMain

	Action:		DLL entry point

***********************************************************************EDOC*/
extern "C" BOOL WINAPI DllMain( HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved )
{
	if( dwReason == DLL_PROCESS_ATTACH )
	{
		wchar_t path[_MAX_PATH];
		GetModuleFileName(NULL, path, _countof(path));
		const wchar_t* exe = PathFindFileName(path);
		g_bExplorerExe = (_wcsicmp(exe, L"explorer.exe") == 0 || _wcsicmp(exe, L"verclsid.exe") == 0);
		if( _wcsicmp(exe, L"regsvr32.exe") != 0 && _wcsicmp(exe, L"msiexec.exe") != 0 && !g_bExplorerExe )
			return FALSE;
		g_Instance = hInstance;
	}
	return _AtlModule.DllMain(dwReason, lpReserved);
}


/*SDOC**********************************************************************

	Name:			DllCanUnloadNow

	Action:		Used to determine whether the DLL can be unloaded by OLE

***********************************************************************EDOC*/
STDAPI DllCanUnloadNow()
{
	return _AtlModule.DllCanUnloadNow();
}


/*SDOC**********************************************************************

	Name:			DllGetClassObject

	Action:		Returns a class factory to create an object of the requested type

***********************************************************************EDOC*/
STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID* ppv)
{
	if( !g_bExplorerExe )
		return CLASS_E_CLASSNOTAVAILABLE;
	return _AtlModule.DllGetClassObject(rclsid, riid, ppv);
}


/*SDOC**********************************************************************

	Name:			DllRegisterServer

	Action:		Adds entries to the system registry

***********************************************************************EDOC*/
STDAPI DllRegisterServer()
{
	return _AtlModule.DllRegisterServer();
}


/*SDOC**********************************************************************

	Name:			DllUnregisterServer

	Action:		Removes entries from the system registry

***********************************************************************EDOC*/
STDAPI DllUnregisterServer()
{
	return _AtlModule.DllUnregisterServer();
}


/*SDOC**********************************************************************

	Name:			DllInstall

	Action:		Adds/Removes entries to the system registry per user per machine

***********************************************************************EDOC*/
STDAPI DllInstall(BOOL bInstall, LPCWSTR pszCmdLine)
{
	static const wchar_t szUserSwitch[] = L"user";
	if( pszCmdLine && _wcsnicmp(pszCmdLine, szUserSwitch, _countof(szUserSwitch)) == 0 )
		AtlSetPerUserRegistration(true);

	HRESULT hr = E_FAIL;
	if( bInstall )
		hr = DllRegisterServer();
	if( FAILED(hr) )
		DllUnregisterServer();
	return hr;
}

/*end of file*/
