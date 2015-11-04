// ScoreBoardView.cpp : implementation of the CScoreBoardView class
//

#include "stdafx.h"
#include "ScoreBoard.h"
#include "ScoreBoardDoc.h"
#include "ScoreBoardView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CScoreBoardView

IMPLEMENT_DYNCREATE ( CScoreBoardView, CFormView ) 

BEGIN_MESSAGE_MAP ( CScoreBoardView, CFormView ) 
	//{{AFX_MSG_MAP ( CScoreBoardView ) 
	ON_COMMAND ( ID_READ_PRO, OnReadPro ) 
	ON_COMMAND ( ID_CLEAR, OnClear ) 
	ON_BN_CLICKED ( IDC_RUN_STEP, OnRunStep ) 
	ON_BN_CLICKED ( IDC_EXCUTE_BUTTON, OnExcuteButton ) 
	ON_WM_TIMER (  ) 
	//}}AFX_MSG_MAP
	// Standard printing commands
	ON_COMMAND ( ID_FILE_PRINT, CFormView::OnFilePrint ) 
	ON_COMMAND ( ID_FILE_PRINT_DIRECT, CFormView::OnFilePrint ) 
	ON_COMMAND ( ID_FILE_PRINT_PREVIEW, CFormView::OnFilePrintPreview ) 
END_MESSAGE_MAP (  ) 

/////////////////////////////////////////////////////////////////////////////
// CScoreBoardView construction/destruction

CScoreBoardView::CScoreBoardView (  ) 
	: CFormView ( CScoreBoardView::IDD ) 
{
	//{{AFX_DATA_INIT ( CScoreBoardView ) 
	m_nClock = 0;
	//}}AFX_DATA_INIT
	// TODO: add construction code here

}

CScoreBoardView::~CScoreBoardView (  ) 
{
}

void CScoreBoardView::DoDataExchange ( CDataExchange* pDX ) 
{
	CFormView::DoDataExchange ( pDX ) ;
	//{{AFX_DATA_MAP ( CScoreBoardView ) 
	DDX_Control ( pDX, IDC_REG_LIST, m_cRegList ) ;
	DDX_Control ( pDX, IDC_FUNUNIT_STATUS_LIST, m_cFunList ) ;
	DDX_Control ( pDX, IDC_INS_STATUS_LIST, m_cInsStaList ) ;
	DDX_Control ( pDX, IDC_PRO_LIST, m_cProList ) ;
	DDX_Text ( pDX, IDC_CLOCK_EDIT, m_nClock ) ;
	//}}AFX_DATA_MAP
}

BOOL CScoreBoardView::PreCreateWindow ( CREATESTRUCT& cs ) 
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CFormView::PreCreateWindow ( cs ) ;
}

void CScoreBoardView::OnInitialUpdate (  ) 
{
	CFormView::OnInitialUpdate (  ) ;
	GetParentFrame (  ) ->RecalcLayout (  ) ;
	ResizeParentToFit (  ) ;
	
	//初始化程序list
	m_cProList.InsertColumn ( 0, "指令", LVCFMT_LEFT, 60 ) ;
	m_cProList.InsertColumn ( 1, "目的地址", LVCFMT_LEFT, 80 ) ;
	m_cProList.InsertColumn ( 2, "源地址", LVCFMT_LEFT, 60 ) ;
	m_cProList.InsertColumn ( 3, "源地址", LVCFMT_LEFT, 60 ) ;
	m_cProList.SetExtendedStyle ( LVS_EX_FULLROWSELECT||LVS_EX_GRIDLINES ) ;

	//初始化指令执行状态的list
		m_cInsStaList.InsertColumn ( 0, "status", LVCFMT_LEFT, 60 ) ;
	m_cInsStaList.InsertColumn ( 1, "Issue", LVCFMT_LEFT, 60 ) ;
	m_cInsStaList.InsertColumn ( 2, "Read operands", LVCFMT_LEFT, 95 ) ;
	m_cInsStaList.InsertColumn ( 3, "Excution done", LVCFMT_LEFT, 95 ) ;
	m_cInsStaList.InsertColumn ( 4, "Write result", LVCFMT_LEFT, 95 ) ;
	m_cInsStaList.SetExtendedStyle ( LVS_EX_FULLROWSELECT||LVS_EX_GRIDLINES ) ;

	//初始化功能单元部件状态的list
	m_cFunList.InsertColumn ( 0, "Name", LVCFMT_LEFT, 60 ) ;
	m_cFunList.InsertColumn ( 1, "Busy", LVCFMT_LEFT, 60 ) ;
	m_cFunList.InsertColumn ( 2, "Op", LVCFMT_LEFT, 60 ) ;
	m_cFunList.InsertColumn ( 3, "Fi", LVCFMT_LEFT, 60 ) ;
	m_cFunList.InsertColumn ( 4, "Fj", LVCFMT_LEFT, 60 ) ;
	m_cFunList.InsertColumn ( 5, "Fk", LVCFMT_LEFT, 60 ) ;
	m_cFunList.InsertColumn ( 6, "Qj", LVCFMT_LEFT, 60 ) ;
	m_cFunList.InsertColumn ( 7, "Qk", LVCFMT_LEFT, 60 ) ;
	m_cFunList.InsertColumn ( 8, "Rj", LVCFMT_LEFT, 60 ) ;
	m_cFunList.InsertColumn ( 9, "Rk", LVCFMT_LEFT, 60 ) ;
	m_cFunList.SetExtendedStyle ( LVS_EX_FULLROWSELECT||LVS_EX_GRIDLINES ) ;

	//初始化寄存器内容状态的list
	CString str;
	m_cRegList.InsertColumn ( 0, "Register", LVCFMT_LEFT, 60 ) ;
	for ( int i=0; i<31; i++ ) 
	{
		str.Format ( "F%d",i ) ;
		m_cRegList.InsertColumn ( i+1, _T ( str ) , LVCFMT_LEFT, 60 ) ;
	}
	m_cRegList.SetExtendedStyle ( LVS_EX_FULLROWSELECT||LVS_EX_GRIDLINES ) ;

	curStep=0;
}

/////////////////////////////////////////////////////////////////////////////
// CScoreBoardView printing

BOOL CScoreBoardView::OnPreparePrinting ( CPrintInfo* pInfo ) 
{
	// default preparation
	return DoPreparePrinting ( pInfo ) ;
}

void CScoreBoardView::OnBeginPrinting ( CDC* /*pDC*/, CPrintInfo* /*pInfo*/ ) 
{
	// TODO: add extra initialization before printing
}

void CScoreBoardView::OnEndPrinting ( CDC* /*pDC*/, CPrintInfo* /*pInfo*/ ) 
{
	// TODO: add cleanup after printing
}

void CScoreBoardView::OnPrint ( CDC* pDC, CPrintInfo* /*pInfo*/ ) 
{
	// TODO: add customized printing code here
}

/////////////////////////////////////////////////////////////////////////////
// CScoreBoardView diagnostics

#ifdef _DEBUG
void CScoreBoardView::AssertValid (  )  const
{
	CFormView::AssertValid (  ) ;
}

void CScoreBoardView::Dump ( CDumpContext& dc )  const
{
	CFormView::Dump ( dc ) ;
}

CScoreBoardDoc* CScoreBoardView::GetDocument (  )  // non-debug version is inline
{
	ASSERT ( m_pDocument->IsKindOf ( RUNTIME_CLASS ( CScoreBoardDoc )  )  ) ;
	return  ( CScoreBoardDoc* ) m_pDocument;
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CScoreBoardView message handlers

void CScoreBoardView::OnReadPro (  )  
{
	// TODO: Add your command handler code here
	CString filePath;
	CFileDialog dialog ( TRUE,"txt","*.txt" ) ;
	if ( dialog.DoModal (  )  != IDOK ) 
	{
		AfxMessageBox ( "Open File Failed!" ) ;
		return;
	}
	filePath=dialog.GetFileName (  ) ;
	simulate=new CSimulator ( &m_cProList, &m_cInsStaList, &m_cFunList, &m_cRegList ) ;
	simulate->initial ( filePath ) ;
}

void CScoreBoardView::OnClear (  )  
{
	// TODO: Add your command handler code here
	m_cProList.DeleteAllItems (  ) ;
	m_cInsStaList.DeleteAllItems (  ) ;
	m_cFunList.DeleteAllItems (  ) ;
	m_cRegList.DeleteAllItems (  ) ;
	
	curStep=0;
}

/*单步运行按钮消息映射*/
void CScoreBoardView::OnRunStep (  )  
{
	// TODO: Add your control notification handler code here
	curStep++;
	m_nClock=curStep;
	UpdateData ( FALSE ) ;
	/*CString str;
	str.Format ( "%d", curStep ) ;
	AfxMessageBox ( str ) ;*/
	if ( simulate->RunStep ( curStep )  )	
		AfxMessageBox ( "Done!" ) ;
}

/*连续运行按钮消息映射*/
void CScoreBoardView::OnExcuteButton (  )  
{
	// TODO: Add your control notification handler code here
	m_nTimer=SetTimer ( 1,1000,0 ) ;
}



void CScoreBoardView::OnTimer ( UINT nIDEvent )  
{
	// TODO: Add your message handler code here and/or call default
	//AfxMessageBox ( "ok" ) ;
	//CFormView::OnTimer ( nIDEvent ) ;
	curStep++;
	m_nClock=curStep;
	UpdateData ( FALSE ) ;
	if ( simulate->RunStep ( curStep )  ) 
	{
		KillTimer ( m_nTimer ) ;
		AfxMessageBox ( "Done!" ) ;
	}
}
