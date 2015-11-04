// Simulator.cpp: implementation of the CSimulator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ScoreBoard.h"
#include "Simulator.h"
#include <string.h>
#include <stdio.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSimulator::CSimulator  (  CListCtrl *m_cProList, CListCtrl *m_cInsStaList, CListCtrl * m_cFunList, CListCtrl *m_cRegList ) 
{
	this->pProList=m_cProList;
	this->pInsList=m_cInsStaList;
	this->pFunList=m_cFunList;
	this->pRegList=m_cRegList;
}

CSimulator::~CSimulator  (   ) 
{
	
}

/*
 *	read source file and initial units
 */
void CSimulator::initial  (  CString filePath ) 
{
	//读入程序，并初始化指令
	int i;
	FILE *file;
	file=fopen ( filePath, "r" ) ;
	if ( file == NULL ) 
	{
		AfxMessageBox ( "open file failed!" ) ;
		return;
	}
	//the first line in the file is the number of instructions 
	fscanf ( file,"%d", &insNum ) ;
	curPro=new Instruction[insNum];
	
	for ( i=0; i<insNum; i++ ) 
	{
		fscanf ( file,"%s %s %s %s",curPro[i].op, curPro[i].destReg, curPro[i].srcOperand1, curPro[i].srcOperand2 ) ;
		curPro[i].ExcuteTime=GetPeriods ( curPro[i] ) ;	//set the excute time 
		curPro[i].waitSta=WAIT_ISSUE;	//change wait status
		curPro[i].unitUsed=NULL;
	}
	
	//add all instructions to the pProList
	for ( i=0; i<insNum; i++ ) 
	{
		int nitem=pProList->InsertItem ( i, curPro[i].op ) ;
		pProList->SetItemText ( nitem, 1, curPro[i].destReg ) ;
		pProList->SetItemText ( nitem, 2, curPro[i].srcOperand1 ) ;
		pProList->SetItemText ( nitem, 3, curPro[i].srcOperand2 ) ;
	}

	/*
	 *	initial function units
	 */
	funUnit=new FunUnit[5];
	funUnit[0].Name="Integer";
	funUnit[1].Name="Mult1";
	funUnit[2].Name="Mult2";
	funUnit[3].Name="Add";
	funUnit[4].Name="Divide";

	for ( i=0; i<5; i++ ) 
	{
		funUnit[i].Busy=false;
		funUnit[i].Op="";
		funUnit[i].Fi="";
		funUnit[i].Fj="";
		funUnit[i].Fk="";
		funUnit[i].Qj=NULL;
		funUnit[i].Qk=NULL;
		funUnit[i].Rj=false;
		funUnit[i].Rk=false;
	}

	/*
	 *	initial registers
	 */
	for ( i=0;i<31;i++ ) 
		Register[i]=NULL;

	numItem=new int[insNum];
	
	for ( i=0; i<insNum; i++ ) 
	{
		numItem[i]=pInsList->InsertItem ( i, "clock:" ) ;	
	}
}


/*
 *	check the function unit and return the address of this unit if not busy
 */
FunUnit * CSimulator::GetFunUnit ( Instruction *ins ) 
{
	if ( strcmp ( ins->op, "LD" )  == 0 ) 
	{
		if ( !funUnit[INTEGER].Busy ) 
		{
			return &funUnit[INTEGER];
		}
		else
			return NULL;
	}

	if ( strcmp ( ins->op, "MULTD" )  == 0 ) 
	{
		if ( !funUnit[MULT1].Busy ) 
		{
			return &funUnit[MULT1];
		}
		else if ( !funUnit[MULT2].Busy ) 
		{
			return &funUnit[MULT2];
		}
		else
			return NULL;
	}

	if ( strcmp ( ins->op, "SUBD" )  == 0||strcmp ( ins->op, "ADDD" )  == 0 ) 
	{
		if ( !funUnit[ADD].Busy ) 
		{
			return &funUnit[ADD];
		}
		else
			return NULL;
	}

	if ( strcmp ( ins->op, "DIVD" )  == 0 ) 
	{
		if ( !funUnit[DIVIDE].Busy ) 
		{
			return &funUnit[DIVIDE];
		}
		else
			return NULL;
	}
	
	return NULL;
}


/*
 *	provide period of each instruction  ( fixed ) 
 */
int CSimulator::GetPeriods ( Instruction ins ) 
{
	if ( strcmp ( ins.op, "LD" )  == 0 ) 
	{
		return 1;
	}
	
	if ( strcmp ( ins.op, "MULTD" )  == 0 ) 
	{
		return 10;
	}
	
	if ( strcmp ( ins.op, "SUBD" )  == 0 ) 
	{
		return 2;
	}
	
	if ( strcmp ( ins.op, "ADDD" )  == 0 ) 
	{
		return 2;
	}
	if ( strcmp ( ins.op, "DIVD" )  == 0 ) 
	{
		return 40;
	}

	return 0;
}


/*
 *	issue a instruction
 *	update function units , registers , wait status of this instruction.
 */
bool CSimulator::Issue ( Instruction *ins ) 
{
	int index;

	/*
	 *	update function unit the instruction used
	 */
	ins->unitUsed->Busy=true;
	ins->unitUsed->Op=ins->op;
	ins->unitUsed->Fi=ins->destReg;
	ins->unitUsed->Fj=ins->srcOperand1;
	ins->unitUsed->Fk=ins->srcOperand2;
	
	/*
	 *	update registers
	 */
	index=GetIndex ( ins->destReg ) ;
	Register[index]=ins->unitUsed;

	index=GetIndex ( ins->srcOperand1 ) ;

	if ( index == -1||index == -2 ) 
	{
		ins->unitUsed->Qj=NULL;
	}
	else
	{
		ins->unitUsed->Qj=Register[index];
	}

	index=GetIndex ( ins->srcOperand2 ) ;
	if ( index == -1||index == -2 ) 
	{
		ins->unitUsed->Qk=NULL;
	}
	else
	{
		ins->unitUsed->Qk=Register[index];
	}

	if ( ins->unitUsed->Qj == NULL ) 
		ins->unitUsed->Rj=true;
	else
		ins->unitUsed->Rj=false;

	if ( ins->unitUsed->Qk == NULL ) 
		ins->unitUsed->Rk=true;
	else
		ins->unitUsed->Rk=false;

	ins->waitSta=WAIT_READ;	//change status of the instruction

	return true;
}


/*
 *	change wait status of this instruction.
 */
bool CSimulator::ReadOperand ( Instruction *ins ) 
{
	ins->waitSta=WAIT_EXCUTE;
	return true;
}


/*
 *	change excute time and return ture if excute completed, false else
 */
bool CSimulator::ExcuteInstruction ( Instruction *ins ) 
{
	ins->ExcuteTime--;
	if ( ins->ExcuteTime == 0 ) 
	{
		ins->waitSta=WAIT_WRITE;
		return true;
	}

	return false;
}

bool CSimulator::WriteResult ( Instruction *ins ) 
{
	int i;
	for ( i=INTEGER; i<=DIVIDE; i++ ) 
	{
		//the unit to write to register j is exactly this instruction used.
		if ( funUnit[i].Qj == ins->unitUsed ) 
		{
			funUnit[i].Qj=NULL;
			funUnit[i].Rj=true;
		}

		if ( funUnit[i].Qk == ins->unitUsed ) 
		{
			funUnit[i].Qk=NULL;
			funUnit[i].Rk=true;
		}
	}
	
	int index=GetIndex ( ins->destReg ) ;
	Register[index]=NULL;
	ins->unitUsed->Busy=false;
	ins->unitUsed->Op="";
	ins->unitUsed->Fi="";
	ins->unitUsed->Fj="";
	ins->unitUsed->Fk="";
	ins->unitUsed->Qj=NULL;
	ins->unitUsed->Qk=NULL;
	ins->unitUsed->Rj=false;
	ins->unitUsed->Rk=false;
	ins->waitSta=FINISHED;
	return true;
}


/*
 *	run to next clock
 */
bool CSimulator::RunStep ( int curStep ) 
{
	int i;
	bool finished=true;
	RunType *temp=new RunType[insNum];
	CString str;

	/*
	 *	if all of instructions were finished , the clock will stop
	 */
	for ( i=0; i<insNum; i++ ) 
	{
		if ( curPro[i].waitSta != FINISHED ) 
			finished=false;
	}
	if ( finished ) 
		return true;

	//get running state for each instrction	
	for ( i=0; i<insNum; i++ ) 
	{
		temp[i]=GetRunType ( &curPro[i], i ) ;
	}
	//processing every instruction
	for ( i=0; i<insNum; i++ ) 
	{
		switch ( temp[i] )  
		{
			case ISSUE:
				if ( Issue ( &curPro[i] )  ) 
				{
					str.Format ( "%d", curStep ) ;
					pInsList->SetItemText ( numItem[i], 1, str ) ;
				}
				break;
			case READ:
				if ( ReadOperand ( &curPro[i] )  ) 
				{
					str.Format ( "%d", curStep ) ;
					pInsList->SetItemText ( numItem[i], 2, str ) ;
				}
				break;
			case EXCUTE:
				if ( ExcuteInstruction ( &curPro[i] )  ) 
				{
					str.Format ( "%d", curStep ) ;
					pInsList->SetItemText ( numItem[i], 3, str ) ;
				}
				break;
			case WRITE:
				if ( WriteResult ( &curPro[i] )  ) 
				{
					str.Format ( "%d", curStep ) ;
					pInsList->SetItemText ( numItem[i], 4, str ) ;
				}
				break;
			case NOTHING:
				break;
			default:
				;
		}
	}
	
	UpdateList (  ) ;
	return false;
}


/*
 *	update all tables
 */
void CSimulator::UpdateList (  ) 
{
	int i, nitem;
	pFunList->DeleteAllItems (  ) ;
	pRegList->DeleteAllItems (  ) ;

	for ( i=INTEGER; i<=DIVIDE; i++ ) 
	{	
		nitem=pFunList->InsertItem ( i, funUnit[i].Name ) ;
		if ( funUnit[i].Busy ) 
		{
			pFunList->SetItemText ( nitem, 1, "Yes" ) ;
		}
		else
			pFunList->SetItemText ( nitem, 1, "No" ) ;

		if ( funUnit[i].Op != "" ) 
		{
			pFunList->SetItemText ( nitem, 2, funUnit[i].Op ) ;
		}
		
		if ( funUnit[i].Fi != "" ) 
		{
			pFunList->SetItemText ( nitem, 3, funUnit[i].Fi ) ;
		}

		if ( funUnit[i].Fj != "" ) 
		{
			pFunList->SetItemText ( nitem, 4, funUnit[i].Fj ) ;
		}
		if ( funUnit[i].Fk != "" ) 
		{
			pFunList->SetItemText ( nitem, 5, funUnit[i].Fk ) ;
		}

		if ( funUnit[i].Qj != NULL ) 
		{
			pFunList->SetItemText ( nitem, 6, funUnit[i].Qj->Name ) ;
		}

		if ( funUnit[i].Qk != NULL ) 
		{
			pFunList->SetItemText ( nitem, 7, funUnit[i].Qk->Name ) ;
		}

		if ( funUnit[i].Rj ) 
			pFunList->SetItemText ( nitem, 8, "Yes" ) ;
		else
			pFunList->SetItemText ( nitem, 8, "No" ) ;
		
		if ( funUnit[i].Rk ) 
			pFunList->SetItemText ( nitem, 9, "Yes" ) ;
		else
			pFunList->SetItemText ( nitem, 9, "No" ) ;
	}
	
	nitem=pRegList->InsertItem ( 0, "status" ) ;
	for ( i=0; i<31; i++ ) 
	{
		if ( Register[i] != NULL ) 
			pRegList->SetItemText ( nitem, i+1, Register[i]->Name ) ;
	}
}


/*
 *	return the index of register
 */
int CSimulator::GetIndex ( char *RegName ) 
{
	char* str;
	if ( RegName[0] != 'F'&&RegName[0] != 'R' ) 
		return -2;
	else if  ( RegName[0] == 'R' )  
	{
		return -1;
	}
	else 
	{
		str=&RegName[1];
		return atoi ( str ) ;
	}
}


/*
 *	description:	get run state of instruction
 *
 *	parameter:		ins: pointer of instruction
 *					num: the number of this instruction in process
 *
 *	return:			run state of ins
 */
RunType CSimulator::GetRunType ( Instruction *ins, int num ) 
{
	int i;
	FunUnit *temp;
	bool WARConfilct=false, OrderConflict=false;
	int index=GetIndex ( ins->destReg ) ;

	switch ( ins->waitSta ) 
	{
		case WAIT_ISSUE:

			//if this instruction is the first one or the previous instruction is waitting for issue
			if ( num  !=  0 && curPro[num-1].waitSta  ==  WAIT_ISSUE ) 
				OrderConflict=true;

			temp = GetFunUnit ( ins ) ;

			// function unit not busy && register is not to be write && issue in order
			if ( temp  !=  NULL && Register[index]  ==  NULL && !OrderConflict ) 
			{
				ins->unitUsed=temp;
				return ISSUE;
			}
			break;

		case WAIT_READ:
			// src operands Rj Rk are ready
			if ( ins->unitUsed->Rj && ins->unitUsed->Rk ) 
				return READ;
			break;

		case WAIT_EXCUTE:
			return EXCUTE;
			break;

		case WAIT_WRITE:

			//check every instruction before this one.( 'num' is the number of this instruction )
			for ( i = 0; i < num; i++ ) 
			{
				if (	curPro[i].waitSta == WAIT_READ	 //there is one instruction waitting for read

						//the previous instruction's src register is the very one this instruction will write back
					&&	(	strcmp ( funUnit[i].Fj, ins->destReg )  == 0	//src register Fj
						||	strcmp ( funUnit[i].Fk, ins->destReg )  == 0	//src register Fk
						)  
					) 
				{
					WARConfilct=true;
				}
			}
			
			//if ( !WARConfilct ) 
			if ( !WARConfilct && ins->unitUsed->Rj && ins->unitUsed->Rk ) 
				return WRITE;
			break;
		default:
			return NOTHING;
	}
	
	return NOTHING;
}
