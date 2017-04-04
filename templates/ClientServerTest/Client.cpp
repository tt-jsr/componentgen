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
* ***************************************************************************/


#include <stdafx.h>
#include <iostream>
#include <string>
#include "Client.h"
#include "ttopenssl/ttopenssl_context.h"

using namespace tt_core_ns;
using namespace std;
using namespace tt_coreutils_ns;
using namespace tt_stream_ns;

class ClientListener: public tt_stream_ns::VIAmCallback
{
public:
    ClientListener(Client *pClient)
    {
        m_pClient = pClient;
        m_pLstnr=auto_ptr<tt_stream_ns::VIAmListener>(pClient->m_pRemoteSession->createListener(
            CLIENT_SUBJ,*this));
    }
protected:
    void OnData(tt_stream_ns::VIAmSession* pSess, 
	                    const tt_stream_ns::VIAmSubject& incomingSubj_,
						tt_stream_ns::VIAmSender* sender_, 
                        tt_stream_ns::Streamable& obj_,
						tt_stream_ns::VIAmListener*)
    {
        m_pClient->OnData(pSess, sender_, obj_);
    }
private:
    auto_ptr<tt_stream_ns::VIAmListener> m_pLstnr;
    Client *m_pClient;
};


Client::Client()
:m_pRemoteSession(NULL)
,m_bProcessEventsRunning(false)
,m_pClientListener(NULL)
{
   
}

Client::~Client() 
{

}

void *Client::threadmain(void *pArg)
{
    Client *pClient = static_cast<Client *>(pArg);
    try
    {
	    pClient->m_pRemoteSession  = new VIAmSession(
				    CoreConfig::Messaging::GetDaemon(CoreConfig::Messaging::Remote),
				    CoreConfig::Messaging::GetService(CoreConfig::Messaging::Default),
				    CoreConfig::Messaging::GetNetwork());

        pClient->m_pClientListener = new ClientListener(pClient);
        tt_openssl_ns::StartCommunications(pClient->m_pRemoteSession);
    }
    catch (TTMException& e)
    {
        syslogerror(L_ERROR) << "TTMException: " << e << endsl;
        return NULL;
    }
    catch (std::exception& e)
    {
        syslogerror(L_ERROR) << "std::exception: " << e.what() << endsl;
        return NULL;
    }

	// Copy all session into a vector so we can call processEvents()
	vector<VIAmSession *> sessions;
	sessions.push_back(pClient->m_pRemoteSession);
	// This	won't return until all sessions	are	closed
	try	{
        pClient->m_bProcessEventsRunning = true;
		VIAm::processEvents(sessions);
	} catch	(std::exception	 &ex) {
		tt_log::LogInterface  log;
		log	<< tt_log::LOG_ERROR <<	"unexpected std::exception	: "	<< ex.what() <<	tt_log::endlog;
	}

    tt_openssl_ns::Shutdown();

	pClient->m_bProcessEventsRunning = false;
    delete pClient->m_pClientListener;
    pClient->m_pClientListener = NULL;
    delete pClient->m_pRemoteSession;
    pClient->m_pRemoteSession = NULL;
	return NULL;
}

void Client::Start()
{
    SysThreadCreate(&m_MgrThreadCtx, threadmain, this);

    Menu();
    m_pRemoteSession->close();
}

Client& Client::Instance()
{
    static Client client;
    return client;
}


