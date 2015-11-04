; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CScoreBoardView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ScoreBoard.h"
LastPage=0

ClassCount=5
Class1=CScoreBoardApp
Class2=CScoreBoardDoc
Class3=CScoreBoardView
Class4=CMainFrame

ResourceCount=3
Resource1=IDD_ABOUTBOX
Resource2=IDD_SCOREBOARD_FORM
Class5=CAboutDlg
Resource3=IDR_MAINFRAME

[CLS:CScoreBoardApp]
Type=0
HeaderFile=ScoreBoard.h
ImplementationFile=ScoreBoard.cpp
Filter=N

[CLS:CScoreBoardDoc]
Type=0
HeaderFile=ScoreBoardDoc.h
ImplementationFile=ScoreBoardDoc.cpp
Filter=N

[CLS:CScoreBoardView]
Type=0
HeaderFile=ScoreBoardView.h
ImplementationFile=ScoreBoardView.cpp
Filter=D
BaseClass=CFormView
VirtualFilter=VWC
LastObject=IDC_PRO_LIST


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_READ_PRO




[CLS:CAboutDlg]
Type=0
HeaderFile=ScoreBoard.cpp
ImplementationFile=ScoreBoard.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_READ_PRO
Command11=ID_CLEAR
Command12=ID_APP_ABOUT
CommandCount=12

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_SCOREBOARD_FORM]
Type=1
Class=CScoreBoardView
ControlCount=14
Control1=IDC_PRO_LIST,SysListView32,1350631425
Control2=IDC_STATIC,static,1342308352
Control3=IDC_INS_STATUS_LIST,SysListView32,1350631425
Control4=IDC_STATIC,static,1342308352
Control5=IDC_FUNUNIT_STATUS_LIST,SysListView32,1350631425
Control6=IDC_STATIC,static,1342308352
Control7=IDC_REG_LIST,SysListView32,1350631425
Control8=IDC_STATIC,static,1342308352
Control9=IDC_STATIC,static,1342308352
Control10=IDC_CLOCK_EDIT,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_RUN_STEP,button,1342177280
Control14=IDC_EXCUTE_BUTTON,button,1342242816

[TB:IDR_MAINFRAME]
Type=1
Class=?
Command1=IDC_EXCUTE_BUTTON
CommandCount=1

