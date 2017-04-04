/*************************************************************************** 
* 
*                   Unpublished Work Copyright (c) 2005 
*                 Trading Technologies International, Inc. 
*                     All Rights Reserved Worldwide *
*            * * * S T R I C T L Y  P R O P R I E T A R Y * * * 
*
* WARNING: This program (or document) is unpublished, proprietary property 
* of Trading Technologies International, Inc. and is to be maintained in 
* strict confidence. Unauthorized reproduction, distribution or disclosure 
* of this program (or document), or any program (or document) derived from 
* it is prohibited by State and Federal law, and by local law outside of 
* the U.S. 
* *************************************************************************** 
* $RCSfile: ClientSide.h $ 
* $Date: 2006/01/26 10:00:24CST $ 
* $Author: jrichards $ 
* $Revision: 1.8.2.4 $ 
***************************************************************************/ 

#ifndef __CLIENTSIDE_H__
#define __CLIENTSIDE_H__

#include "%(INTERFACENAME)/client/%(INTERFACENAME)interface.h"

class $(INTERFACENAME)InterfaceImpl : public tt_%(INTERFACENAME)_ns::$(INTERFACENAME)Interface {
public:
    void OnPing(const tt_coreframework_ns::RspContext&);
    void OnServerUp();
    void OnServerDown();
};

class Client {
public:
	Client();
    ~Client();

	void Start();

	void Menu();
    int Prompt(bool bPrompt);

	$(INTERFACENAME)InterfaceImpl *m_pInterface;
};

#endif //__CLIENTSIDE_H__


/***********************************************************************************
* $Log: ClientSide.h  $
* Revision 1.8.2.4 2006/01/26 10:00:24CST jrichards 
* XAdminSim now heartbeats as a login server
* Revision 1.8.2.3 2005/12/07 16:49:47CST rtaylor 
* Updated after Code Review
***********************************************************************************/
