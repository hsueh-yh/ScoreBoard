// Simulator.h: interface for the CSimulator class.
//
//////////////////////////////////////////////////////////////////////

#if !defined ( AFX_SIMULATOR_H__412C4E79_BEC2_4562_9916_5897A4E04D03__INCLUDED_ ) 
#define AFX_SIMULATOR_H__412C4E79_BEC2_4562_9916_5897A4E04D03__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//typedef enum {LD, MULT, SUBD, DIVD, ADDD} Operation;
typedef enum {BUSY, OP, FI, FJ, FK, QJ, QK, RJ, RK} UiSta;	//function unit status
typedef enum {WAIT_ISSUE, WAIT_READ,WAIT_EXCUTE, WAIT_WRITE, FINISHED} WaitSta;	// instruction wait status
typedef enum {ISSUE, READ, EXCUTE, WRITE,NOTHING} RunType;	//instruction run status
enum {INTEGER, MULT1, MULT2,ADD, DIVIDE};	//function units

/*
 *	function unit  ( include registers ) 
 */
struct FunUnit{
	char *Name;	//unit name
	bool Busy;	//is this unit busy
	char *Op;	//the option of instruction running on this unit
	char *Fi;	//dest register
	char *Fj;	//src register1
	char *Fk;	//src register2
	FunUnit *Qj;	//the other unit use the register1
	FunUnit *Qk;
	bool Rj;	
	bool Rk;	
};

/*
 *	instruction struct
 */
struct Instruction {
	char op[6];
	char destReg[4];
	char srcOperand1[4];
	char srcOperand2[4];
	FunUnit *unitUsed;
	WaitSta waitSta;
	int ExcuteTime;
};

class CSimulator  
{
public:
	Instruction *curPro;	//array of all instructions
	int insNum;		//the number of instructions
	FunUnit *funUnit;
	FunUnit *Register[31];

	/*
	 *	
	 */
	CListCtrl *pProList;	//the list of all instructions
	CListCtrl *pInsList;	//instruction list
	CListCtrl *pFunList;	//function unit list
	CListCtrl *pRegList;	//register list

public:
	int * numItem;
	RunType GetRunType ( Instruction *ins, int num ) ;
	int GetIndex ( char *RegName ) ;
	
	void UpdateList (  ) ;
	bool RunStep ( int curStep ) ;
	bool WriteResult ( Instruction *ins ) ;
	bool ExcuteInstruction ( Instruction *ins ) ;
	bool ReadOperand ( Instruction *ins ) ;
	bool Issue ( Instruction *ins ) ;
	int GetPeriods ( Instruction ins ) ;
	FunUnit * GetFunUnit ( Instruction *ins ) ;
	void initial ( CString filePath ) ;

	CSimulator ( CListCtrl *m_cProList, CListCtrl *m_cInsStaList, CListCtrl * m_cFunList, CListCtrl *m_cRegList ) ;
	virtual ~CSimulator (  ) ;

};

#endif // !defined ( AFX_SIMULATOR_H__412C4E79_BEC2_4562_9916_5897A4E04D03__INCLUDED_ ) 
