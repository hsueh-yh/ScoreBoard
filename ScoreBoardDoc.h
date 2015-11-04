// ScoreBoardDoc.h : interface of the CScoreBoardDoc class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined ( AFX_SCOREBOARDDOC_H__95CC9382_7D52_47D7_8BB3_F617D9C543CB__INCLUDED_ ) 
#define AFX_SCOREBOARDDOC_H__95CC9382_7D52_47D7_8BB3_F617D9C543CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


class CScoreBoardDoc : public CDocument
{
protected: // create from serialization only
	CScoreBoardDoc (  ) ;
	DECLARE_DYNCREATE ( CScoreBoardDoc ) 

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL ( CScoreBoardDoc ) 
	public:
	virtual BOOL OnNewDocument (  ) ;
	virtual void Serialize ( CArchive& ar ) ;
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CScoreBoardDoc (  ) ;
#ifdef _DEBUG
	virtual void AssertValid (  )  const;
	virtual void Dump ( CDumpContext& dc )  const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG ( CScoreBoardDoc ) 
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP (  ) 
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined ( AFX_SCOREBOARDDOC_H__95CC9382_7D52_47D7_8BB3_F617D9C543CB__INCLUDED_ ) 
