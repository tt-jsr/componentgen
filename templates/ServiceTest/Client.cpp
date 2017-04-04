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
* $RCSfile: Client.cpp $ 
* $Date: 2006/02/06 16:35:29CST $ 
* $Author: cpatel $ 
* $Revision: 1.15.2.2.1.6 $ 
***************************************************************************/ 


#include <stdafx.h>
#include <iostream>
#include "%(INTERFACENAME)/client/%(INTERFACENAME)interface.h"
#include "%(INTERFACENAME)/client/%(INTERFACENAME)service.h"
#include "Coreframework/Common/SessionMgr.h"
#include "ClientSide.h"
#include "CoreFramework/Common/CoreFrameworkException.h"
#include "ttopenssl/ttopenssl_context.h"
#include "coreframework/cryptoservice/client/CryptoServiceService.h"

using namespace tt_%(INTERFACENAME)_ns;
using namespace tt_coreframework_ns;
using namespace std;
using namespace tt_coreutils_ns;

/*******************************************************************************
 * TODO: Implement your client side callbacks here
 */

void $(INTERFACENAME)InterfaceImpl::OnPing(const RspContext& ctx)
{
    switch (ctx.code)
    {
    case RSP_SUCCESS:    
        {
            cout << "ping reply" << endl;
        }
        break;
    case RSP_TIMEOUT:   
        {
            cout << "ping timeout" << endl;
        }
        break;
    default:
        cout << ctx.responsetext.c_str() << endl;
        break;
    }
    
}

void $(INTERFACENAME)InterfaceImpl::OnServerUp()
{
    cout << "$(INTERFACENAME) server is UP" << endl;
}

void $(INTERFACENAME)InterfaceImpl::OnServerDown()
{
    cout << "$(INTERFACENAME) server is DOWN" << endl;
}

int Client::Prompt(bool bPrompt)
{
    static char buf[64];
    // We are now ready to send and receive messages
    buf[0] = '\0';
    fflush(stdin);
    if (bPrompt == true) {
        // Add other menu options here
        cout << "1: Ping server" << endl;
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

void Client::Menu()
{
    int cmd = Prompt(true);

    while (cmd >= 0) {
        switch (cmd) {
        case 0:
            cmd = Prompt(true);
            break;
        case 1:
            {
                m_pInterface->Ping();
                cmd = Prompt(true);
            }
            break;
        default:    
            cmd = Prompt(true);
            break;
        }
    }
}

Client::Client()
:m_pInterface(NULL)
{
    
}

Client::~Client() 
{
    
}

void Client::Start()
{
    SessionMgr *pSessionMgr = SessionMgr::GetSessionMgr("$(INTERFACENAME)");

    try {
        pSessionMgr->CreateRemoteSession("REMOTE");
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

    // Start the session manager. This will create a session and call ProcessEvents()
    try {
        pSessionMgr->CreateRemoteSession("REMOTE");
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

    // TTOpenSSL (aka encryption) client interface setup...
    try {
        tt_openssl_ns::StartCommunications(pSessionMgr->GetSession("REMOTE"));
    } catch (tt_openssl_ns::InitError &ex) {
        tt_log::LogInterface  log;
        log << tt_log::LOG_ERROR << ex.what() << tt_log::endlog;
        throw;
    }
    CryptoServiceService::TTMCreateData cdcrypto(pSessionMgr->GetSession("REMOTE"));
    bool bcrypto = CryptoServiceService::GetService()->Create(cdcrypto);


    // Setup the CreateData structure so we can create the service
    $(INTERFACENAME)Service::TTMCreateData cd(pSessionMgr->GetSession("REMOTE"));

    // Create an instance of the service we are testing
    bool b = $(INTERFACENAME)Service::Create(cd);

    // Create the interface to implement for testing
    m_pInterface = new $(INTERFACENAME)InterfaceImpl();

    // Register the interface
    $(INTERFACENAME)Service::GetService()->RegisterInterface(m_pInterface);

    // We are now ready to send and receive messages

    Menu();

    // Unregister ourinterface
    $(INTERFACENAME)Service::GetService()->UnRegisterInterface(m_pInterface);

    delete m_pInterface;
    m_pInterface = NULL;

    // Destroy the service instance
    $(INTERFACENAME)Service::GetService()->Destroy(); 

    // Stop the session manager. This will close the session and
    // ProcessEvents() will return from TTM
    pSessionMgr->CloseSessions();

    pSessionMgr->Destroy();
}

