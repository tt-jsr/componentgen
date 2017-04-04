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
#include "Server.h"
#include "ttopenssl/ttopenssl_context.h"

#include <string>

    using namespace tt_stream_ns;
    using namespace std;
    using namespace tt_coreutils_ns;
    using namespace tt_core_ns;

// Receive guardserv status requests through this listener
class ServerListener: public tt_stream_ns::VIAmCallback
{
public:
    ServerListener(Server *pServer)
    {
        m_pServer = pServer;
        m_pLstnr=auto_ptr<tt_stream_ns::VIAmListener>(pServer->m_pLocalSession->createListener(
            SERVER_SUBJ,*this));
    }
protected:
    void OnData(tt_stream_ns::VIAmSession* pSess, 
	                    const tt_stream_ns::VIAmSubject& incomingSubj_,
						tt_stream_ns::VIAmSender* sender_, 
                        tt_stream_ns::Streamable& obj_,
						tt_stream_ns::VIAmListener*)
    {
        m_pServer->OnData(pSess, sender_, obj_);
    }
private:
    auto_ptr<tt_stream_ns::VIAmListener> m_pLstnr;
    Server *m_pServer;
};

Server::Server()
:m_pServerListener(NULL)
,m_pLocalSession(NULL)
,m_bProcessEventsRunning(false)
{

}

Server::~Server()
{
    delete m_pServerListener;
}

void *Server::threadmain(void *pArg)
{
    Server *pServer = static_cast<Server *>(pArg);
    try
    {
        pServer->m_pLocalSession  = new VIAmSession(
				    CoreConfig::Messaging::GetDaemon(CoreConfig::Messaging::Local),
				    CoreConfig::Messaging::GetService(CoreConfig::Messaging::Default),
				    CoreConfig::Messaging::GetNetwork());

        pServer->m_pServerListener = new ServerListener(pServer);
        tt_openssl_ns::StartCommunications(pServer->m_pLocalSession);
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
	sessions.push_back(pServer->m_pLocalSession);
	// This	won't return until all sessions	are	closed
	try	{
        pServer->m_bProcessEventsRunning = true;
		VIAm::processEvents(sessions);
	} catch	(std::exception	 &ex) {
		tt_log::LogInterface  log;
		log	<< tt_log::LOG_ERROR <<	"unexpected std::exception	: "	<< ex.what() <<	tt_log::endlog;
	}

    tt_openssl_ns::Shutdown();

	pServer->m_bProcessEventsRunning = false;
    delete pServer->m_pServerListener;
    pServer->m_pServerListener = NULL;
    delete pServer->m_pLocalSession;
    pServer->m_pLocalSession = NULL;
	return NULL;
}

void Server::Start()
{
    SysThreadCreate(&m_MgrThreadCtx, threadmain, this);

    Menu();
    m_pLocalSession->close();    
}

Server& Server::Instance()
{
    static Server server;
    return server;
}

