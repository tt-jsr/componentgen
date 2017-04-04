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
* $RCSfile: Server.cpp $ 
* $Date: 2006/07/27 08:14:45CDT $ 
* $Author: jrichards $ 
* $Revision: 1.18.3.2.1.7 $ 
***************************************************************************/ 

#include <stdafx.h>
#include <iostream>
#include "%(INTERFACENAME)/server/%(INTERFACENAME)serverinterface.h"
#include "%(INTERFACENAME)/server/%(INTERFACENAME)serverservice.h"
#include "%(INTERFACENAME)/%(INTERFACENAME)_common/%(INTERFACENAME)_common.h"
#include "coreframework/Common/SessionMgr.h"
#include "ServerSide.h"
#include "ttopenssl/ttopenssl_context.h"
#include "coreframework/cryptoservice/client/CryptoServiceService.h"

#include <string>

    using namespace tt_coreframework_ns;
    using namespace tt_stream_ns;
    using namespace std;
    using namespace tt_coreutils_ns;
    using namespace tt_core_ns;
    using namespace tt_%(INTERFACENAME)_ns;

/*******************************************************************************
 * TODO: Implement your server side callbacks here
 */


/**************************************************************************
 * TODO: Implement menu items here
 */
int Server::Prompt(bool bPrompt)
{
    static char buf[64];
    // We are now ready to send and receive messages
    buf[0] = '\0';
    fflush(stdin);
    if (bPrompt == true) {
        // Add other menu options here
        cout << endl;
        cout << "q.    Quit" << endl << endl;
        cout << "Enter=> ";
    }
    gets(buf);
    fflush(stdin);
    switch (buf[0]) {
    case '\n':
    case ' ':
    case '\0':
        return 0;
    case 'q':
    case 'Q':
        return -1;
    default:
        return atoi(buf);
    }
    return 0;
}

void Server::Menu()
{
    int cmd = Prompt(true);

    while (cmd >= 0) {
        switch (cmd) {
        case 0:
            cmd = Prompt(true);
            break;
        default:    
            cmd = Prompt(true);
            break;
        }
    }
}

Server::Server()
:m_pInterface(NULL)
, m_pStatus(NULL)
{

}

Server::~Server()
{
    delete m_pStatus;
}

void Server::Start()
{
    SessionMgr *pSessionMgr = SessionMgr::GetSessionMgr("$(INTERFACENAME)");
    // Start the session manager. This will create a session and call ProcessEvents()
    try {
        pSessionMgr->CreateLocalSession("LOCAL");
        pSessionMgr->StartProcessEvents();
    }
    catch (TTMException& e)
    {
        cout << "Exception: " << e << endl;
        return;
    }
    catch (std::exception& e)
    {
        cout << "Exception: " << e.what() << endl;
    }

    // Initialize ttopenssl for encryption
    tt_openssl_ns::StartCommunications(pSessionMgr->GetSession("LOCAL"));

    // Setup the CreateData structure so we can create the service
    $(INTERFACENAME)ServerService::TTMCreateData cd(pSessionMgr->GetSession("LOCAL"));

    // Create an instance of the service we are testing
    bool b = $(INTERFACENAME)ServerService::Create(cd);

    // Create the interface to implement for testing
    m_pInterface = new $(INTERFACENAME)ServerInterfaceImpl();

    // Register the interface
    $(INTERFACENAME)ServerService::GetService()->RegisterInterface(m_pInterface);

    if (@(INTERFACENAME)_SERVICE_HEARTBEAT != 0)
    {
        m_pStatus = new LSLocalSrvSts(*pSessionMgr->GetSession("LOCAL"));
    }

    // We are now ready to send and receive messages

    Menu();

	// Shutdown ttopenssl
	tt_openssl_ns::Shutdown();

    // Unregister ourinterface
    $(INTERFACENAME)ServerService::GetService()->UnRegisterInterface(m_pInterface);
    delete m_pInterface;
    m_pInterface = NULL;

    // Destroy the service instance
    $(INTERFACENAME)ServerService::GetService()->Destroy();

    // Stop the session manager. This will close the session and
    // ProcessEvents() will return from TTM
    pSessionMgr->CloseSessions();
    pSessionMgr->Destroy();
}


// Handle server status requests here. We are going to heartbeat as a
// xxx server
void LSLocalSrvSts::OnData(VIAmSession*pSess, 
	                    const VIAmSubject& incomingSubj_,
						VIAmSender* sender_, 
                        Streamable& obj_,
						VIAmListener*)
{
    switch (obj_.Id().GetCode())
	{	
		case Header_cc:
		{
			Header header = static_cast<const Header&>(obj_);
			switch(header.trnCode)
			{
	        case TT_SRV_STAT_REQUEST:
		        {
                    SAR_StatusPKT cSsa(1);
			        Reply cReply(cSsa);
			        cReply.header.trnCode    = TT_SRV_STAT_REPLY;
			        cReply.header.nElements  = 1;
                    AEnum_ExchIds exchids;
                    int eid = exchids.AuxStr2Enum("TTGLOBAL");
                    string s = exchids.Enum2AuxStr(eid);
			        cReply.header.exchange   = TT_GLOBAL_EXCH_ID;

			        cReply.u.ssa[0].service  = @(INTERFACENAME)_SERVICE_HEARTBEAT;
			        cReply.u.ssa[0].exchange = TT_GLOBAL_EXCH_ID;
			        cReply.u.ssa[0].status   = static_cast<AEnum_ServerStatusCodes>(TT_SERVER_ACTIVE);
			        cReply.u.ssa[0].priority = 1;
			        cReply.u.ssa[0].load     = 0;
			        cReply.u.ssa[0].pid      = GetLocalPID();
			        cReply.u.ssa[0].srvAddr  = *GetLocalIP();
			        //cReply.u.ssa[0].seq      = TTGetLTime();
                    cReply.u.ssa[0].flags = StatusPKT::FLAG_CRYPTO_CAPABLE;
			        //cReply.u.ssa[0].iLicense = srv.ttLicense;
			        // reply on guardserver's inbox so other servers aren't bothered
			        VIAmSender sndr = pSess->CreateSender(sender_->getSubject().asString());
			        sndr.send(cReply);
			        break;
		        }
            }
        }
    }
}
