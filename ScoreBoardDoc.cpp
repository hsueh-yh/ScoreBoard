// ScoreBoardDoc.cpp : implementation of the CScoreBoardDoc class
//

#include "stdafx.h"
#include "ScoreBoard.h"

#include "ScoreBoardDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScoreBoardDoc

IMPLEMENT_DYNCREATE ( CScoreBoardDoc, CDocument ) 

BEGIN_MESSAGE_MAP ( CScoreBoardDoc, CDocument ) 
	//{{AFX_MSG_MAP ( CScoreBoardDoc ) 
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP (  ) 

/////////////////////////////////////////////////////////////////////////////
// CScoreBoardDoc construction/destruction

CScoreBoardDoc::CScoreBoardDoc (  ) 
{
	// TODO: add one-time construction code here

}

CScoreBoardDoc::~CScoreBoardDoc (  ) 
{
}

BOOL CScoreBoardDoc::OnNewDocument (  ) 
{
	if  ( !CDocument::OnNewDocument (  )  ) 
		return FALSE;

	// TODO: add reinitialization code here
	//  ( SDI documents will reuse this document ) 
	return TRUE;
}



/////////////////////////////////////////////////////////////////////////////
// CScoreBoardDoc serialization

void CScoreBoardDoc::Serialize ( CArchive& ar ) 
{
	if  ( ar.IsStoring (  )  ) 
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CScoreBoardDoc diagnostics

#ifdef _DEBUG
void CScoreBoardDoc::AssertValid (  )  const
{
	CDocument::AssertValid (  ) ;
}

void CScoreBoardDoc::Dump ( CDumpContext& dc )  const
{
	CDocument::Dump ( dc ) ;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScoreBoardDoc commands
