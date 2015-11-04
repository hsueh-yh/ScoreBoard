// ScoreBoardView.h : interface of the CScoreBoardView class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined ( AFX_SCOREBOARDVIEW_H__8231633B_0F61_4639_B7F2_B1F86BFA3021__INCLUDED_ ) 
#define AFX_SCOREBOARDVIEW_H__8231633B_0F61_4639_B7F2_B1F86BFA3021__INCLUDED_

#include "Simulator.h"	// Added by ClassView
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



class CScoreBoardView : public CFormView
{
protected: // create from serialization only
	CScoreBoardView (  ) ;
	DECLARE_DYNCREATE ( CScoreBoardView ) 

public:
	//{{AFX_DATA ( CScoreBoardView ) 
	enum { IDD = IDD_SCOREBOARD_FORM };
	CListCtrl	m_cRegList;
	CListCtrl	m_cFunList;
	CListCtrl	m_cInsStaList;
	CListCtrl	m_cProList;
	int		m_nClock;
	//}}AFX_DATA

// Attributes
public:
	CScoreBoardDoc* GetDocument (  ) ;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL ( CScoreBoardView ) 
	public:
	virtual BOOL PreCreateWindow ( CREATESTRUCT& cs ) ;
	protected:
	virtual void DoDataExchange ( CDataExchange* pDX ) ;    // DDX/DDV support
	virtual void OnInitialUpdate (  ) ; // called first time after construct
	virtual BOOL OnPreparePrinting ( CPrintInfo* pInfo ) ;
	virtual void OnBeginPrinting ( CDC* pDC, CPrintInfo* pInfo ) ;
	virtual void OnEndPrinting ( CDC* pDC, CPrintInfo* pInfo ) ;
	virtual void OnPrint ( CDC* pDC, CPrintInfo* pInfo ) ;
	//}}AFX_VIRTUAL

// Implementation
public:
	int m_nTimer;
	int curStep;
	CSimulator *simulate;
	virtual ~CScoreBoardView (  ) ;
#ifdef _DEBUG
	virtual void AssertValid (  )  const;
	virtual void Dump ( CDumpContext& dc )  const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG ( CScoreBoardView ) 
	afx_msg void OnReadPro (  ) ;
	afx_msg void OnClear (  ) ;
	afx_msg void OnRunStep (  ) ;
	afx_msg void OnExcuteButton (  ) ;
	afx_msg void OnTimer ( UINT nIDEvent ) ;
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP (  ) 
};

#ifndef _DEBUG  // debug version in ScoreBoardView.cpp
inline CScoreBoardDoc* CScoreBoardView::GetDocument (  ) 
   { return  ( CScoreBoardDoc* ) m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined ( AFX_SCOREBOARDVIEW_H__8231633B_0F61_4639_B7F2_B1F86BFA3021__INCLUDED_ ) 
