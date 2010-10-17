/*SDOC**********************************************************************

	Module:				Explorer7Fixes.cpp

	Copyright (C) 2010 Ian Prest

	Description:	BHO implementation

***********************************************************************EDOC*/
#include "stdafx.h"
#include "Explorer7Fixes_h.h"

//**************************************************************************
//*************************** CExplorerBHO Class ***************************
//**************************************************************************
class ATL_NO_VTABLE CExplorerBHO :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CExplorerBHO, &CLSID_Explorer7FixesBHO>,
	public IObjectWithSiteImpl<CExplorerBHO>,
	public IDispatchImpl<IExplorer7FixesBHO, &IID_IExplorer7FixesBHO, &LIBID_Explorer7FixesLib, /*wMajor =*/ 1, /*wMinor =*/ 2>,
	public IDispEventImpl<1,CExplorerBHO,&DIID_DWebBrowserEvents2,&LIBID_SHDocVw,1,1>
{
public:
	CExplorerBHO() {}

	DECLARE_REGISTRY_RESOURCEID( IDR_BHO )

	BEGIN_COM_MAP( CExplorerBHO )
		COM_INTERFACE_ENTRY( IExplorer7FixesBHO )
		COM_INTERFACE_ENTRY( IObjectWithSite )
		COM_INTERFACE_ENTRY( IDispatch )
	END_COM_MAP()

	BEGIN_SINK_MAP( CExplorerBHO )
		SINK_ENTRY_EX( 1, DIID_DWebBrowserEvents2, DISPID_NAVIGATECOMPLETE2, OnNavigateComplete )
		SINK_ENTRY_EX( 1, DIID_DWebBrowserEvents2, DISPID_ONQUIT, OnQuit )
	END_SINK_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct() { return S_OK; }
	void FinalRelease() {}

	// IObjectWithSite interface
	STDMETHOD(SetSite)( IUnknown *pUnkSite );

	// DWebBrowserEvents2 interface
	STDMETHOD(OnNavigateComplete)( IDispatch *pDisp, VARIANT *URL );
	STDMETHOD(OnQuit)();

private:
	CComPtr<IShellBrowser> m_pBrowser;
	CComPtr<IWebBrowser2> m_pWebBrowser;
	static LRESULT CALLBACK HookExplorer( int code, WPARAM wParam, LPARAM lParam );
};

OBJECT_ENTRY_AUTO( __uuidof(Explorer7FixesBHO), CExplorerBHO )


/*SDOC**********************************************************************

	Name:			CExplorerBHO::SetSite

	Action:		Attach to Explorer

***********************************************************************EDOC*/
HRESULT STDMETHODCALLTYPE CExplorerBHO::SetSite( IUnknown *pUnkSite )
{
	IObjectWithSiteImpl<CExplorerBHO>::SetSite( pUnkSite );

	// hook
	if(pUnkSite)
	{
		CComQIPtr<IServiceProvider> pProvider = pUnkSite;
		if( pProvider )
		{
			pProvider->QueryService( SID_SWebBrowserApp, IID_IWebBrowser2, (void**)&m_pWebBrowser );
			if( m_pWebBrowser )
			{
				if( m_dwEventCookie == 0xFEFEFEFE ) // ATL's event cookie is 0xFEFEFEFE when the sink is not advised
					DispEventAdvise( m_pWebBrowser, &DIID_DWebBrowserEvents2 );
			}
			pProvider->QueryService( SID_SShellBrowser, IID_IShellBrowser, (void**)&m_pBrowser );
		}
	}

	// unhook
	else
	{
		m_pBrowser = NULL;
		if( m_pWebBrowser && m_dwEventCookie != 0xFEFEFEFE )
			DispEventUnadvise( m_pWebBrowser, &DIID_DWebBrowserEvents2 );
		m_pWebBrowser=NULL;
	}
	return S_OK;
}


/*SDOC**********************************************************************

	Name:			CExplorerBHO::OnNavigateComplete

	Action:		Called when changing directories

***********************************************************************EDOC*/
STDMETHODIMP CExplorerBHO::OnNavigateComplete( IDispatch *pDisp, VARIANT *URL )
{
	if( m_pBrowser )
	{
		CComPtr<IShellView> pShellView;
		m_pBrowser->QueryActiveShellView( &pShellView );
		if( pShellView )
		{
			CComPtr<IFolderView2> pFolderView;
			pShellView->QueryInterface( &pFolderView );
			if( pFolderView )
			{
				// Turn on the sort header!
				pFolderView->SetCurrentFolderFlags( FWF_NOHEADERINALLVIEWS, 0 );

        // It seems the ItemsView doesn't respect the FWF_NOHEADERINALLVIEWS flag
        // until the view has been refreshed.  Rather than call Refresh, we just
				// briefly change the view mode and change it back.
				FOLDERVIEWMODE uViewMode;
				int nItemSize = 0;
				pFolderView->GetViewModeAndIconSize( &uViewMode, &nItemSize );
        if( uViewMode != FVM_DETAILS )
				{
					pFolderView->SetViewModeAndIconSize( uViewMode == FVM_LIST ? FVM_SMALLICON : FVM_LIST, nItemSize );
					pFolderView->SetViewModeAndIconSize( uViewMode, nItemSize );
				}
			}
		}
	}
	return S_OK;
}


/*SDOC**********************************************************************

	Name:			CExplorerBHO::OnQuit

	Action:

***********************************************************************EDOC*/
STDMETHODIMP CExplorerBHO::OnQuit( void )
{
	if( m_pWebBrowser && m_dwEventCookie != 0xFEFEFEFE ) // ATL's event cookie is 0xFEFEFEFE, when the sink is not advised
		return DispEventUnadvise( m_pWebBrowser, &DIID_DWebBrowserEvents2 );
	return S_OK;
}

/*end of file*/
