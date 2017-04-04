/**************************************************************************
 *    
 *  Copyright (c) 2005  Trading Technologies International  
 *                      All Rights Reserved Worldwide
 *
 *         * * *   S T R I C T L Y   P R O P R I E T A R Y   * * *   
 *
 * The following source code, and the ideas, expressions and concepts
 * incorporated therein, as well as the ideas, expressions and concepts
 * of any other material (whether tangible or intangible) disclosed in
 * conjunction with this source code, are the exclusive and proprietary
 * property, and constitutes confidential information, of Trading
 * Technologies International.  Accordingly, the user of this source code
 * agrees that it shall continue to be bound by the terms and conditions
 * of any and all confidentiality agreements executed with Trading 
 * Technologies International concerning the disclosure of the source code
 * and any other materials in conjunction therewith.
 *
 ***************************************************************************
 * $Source: Interface/name_TTMImpl.cpp $ 
 * $Date: 2005/07/27 08:40:16CDT $ 
 * $Author: ebradnick $ 
 * $Revision: 1.6 $ 	
 ***************************************************************************/
/*
 * This file generated on $(DATE)
 */

#include "pch.h"
#include "%(INTERFACENAME)service.h"
#include "%(INTERFACENAME)ttmimpl.h"
#include "%(INTERFACENAME)service.h"
#include "ttopenssl/ttopenssl_context.h"
#include "../%(INTERFACENAME)_common/%(INTERFACENAME)_common.h"
#include <sstream>

using namespace tt_coreframework_ns;
using namespace tt_stream_ns;
using namespace std;
using namespace tt_core_ns;

namespace tt_%(INTERFACENAME)_ns {

$(INTERFACENAME)TTMImpl::$(INTERFACENAME)TTMImpl()
: m_pSession(NULL)
,m_annrqst(0)
,m_bHaveAnnounce(false)
,m_bHaveParticipant(false)
,m_bServiceReady(false)
{

}

$(INTERFACENAME)TTMImpl::~$(INTERFACENAME)TTMImpl()
{
	m_Dispatcher.Shutdown();
	delete m_pSession;
}

bool $(INTERFACENAME)TTMImpl::Init(const CreateData& cd)
{
	const TTMCreateData& tcd = static_cast<const TTMCreateData&>(cd);
	m_pSession = new VIAmSession(*tcd.pSess);

#if !defined(@(INTERFACENAME)_ENCRYPTION_ENABLED)
    m_bHaveParticipant = true;  // Encryption is not necessary for startup
#endif
	try {
		m_Dispatcher.Init(this, *m_pSession, @(INTERFACENAME)_SERVER_SUBJ);

        stringstream subj;
        subj << CoreMessaging::SRV_STS_SUBJ << TT_GLOBAL_EXCH_ID;
        // Start the heartbeat listener, if an exchange id has been defined
        if (BILLING_SERVICE_HEARTBEAT != 0)
        {
            m_pStatusHandler = new LSSrvSts(this, *m_pSession, subj.str());
            m_pStatusTimer = new StatusTimer(this, *m_pSession);
        }

        SendDiscoverRequest();
    }
	catch (CoreFrameworkException&)
	{
		return false;
	}
	return $(INTERFACENAME)Service::Init(cd);
}

// Got a heartbeat, update our status
void $(INTERFACENAME)TTMImpl::OnHeartbeat(StatusPKT& pkt)
{
    time_t now = time(NULL);

    m_lastStatus = now;
    if (m_bServiceReady == false)
    {
        // We now see a ($(INTERFACENAME)) server, start the discovery        
        syslogerror(L_INFO) << "$(INTERFACENAME) server heartbeat seen, sending discovery request" << endsl;
        SendDiscoverRequest();
    }
}

// Check our status
void $(INTERFACENAME)TTMImpl::OnStatusTimer()
{
    time_t now = time(NULL);
    if (m_bServiceReady == true && (now - m_lastStatus) > APPLICATION_TIMEOUT)
    {
        syslogerror(L_ERROR) << "Lost $(INTERFACENAME) server" << endsl;
     
        DispatchServiceDown();
    }
}

void $(INTERFACENAME)TTMImpl::SendDiscoverRequest()
{
    if (false == m_bHaveAnnounce)
    {
        // Send a DISCOVER announcement so we can find our server
        $(INTERFACENAME)Announce ann;
        ann.action = $(INTERFACENAME)Announce::DISCOVER;
        
        sysloginfo << "Sending $(INTERFACENAME)Announce::DISCOVER request" << endsl;
        m_annrqst = BroadcastRequest(ann, GetBroadcastToServers());
    }

    if (false == m_bHaveParticipant && true == m_bHaveAnnounce)
    {
        // Retry the get participant just in case, this will return true if it found it.
        m_bHaveParticipant = tt_openssl_ns::GetParticipant(m_ServerInbox, m_Dispatcher.GetInboxName(), m_pSession);
        DispatchServiceUp();
    }

}

void $(INTERFACENAME)TTMImpl::DispatchServiceUp()
{
    $(INTERFACENAME)Announce ann;

    if (false == m_bHaveParticipant)
    {
        return; // Still need the participant from crypto
    }

    if (false == m_bHaveAnnounce)
    {
        return; // Still need the announce from xadmin
    }

    // Dispatch the OnServerUp message to all the registered interfaces
    m_bServiceReady = true;
    ann.action = $(INTERFACENAME)Announce::ANNOUNCE;
    NotifyContext ctx;
    Service::DispatchNotify(ctx, ann);    

    sysloginfo << "$(INTERFACENAME) server UP" << endsl;
}

void $(INTERFACENAME)TTMImpl::DispatchServiceDown()
{
    if (m_bServiceReady == false)
    {
        // We are already down
        return;
    }

#if defined(@(INTERFACENAME)_ENCRYPTION_ENABLED)
    m_bHaveParticipant = false;
#endif

    m_bHaveAnnounce = false;

    m_bServiceReady = false;
    m_ServerInbox = "";
    m_ServerIPAddress.s_addr = 0;

    sysloginfo << "$(INTERFACENAME) server DOWN" << endsl;

    // Dispatch an OnServerDown through the XAdminInterface
    XAdminAnnounce ann;
    ann.action = XAdminAnnounce::SHUTDOWN;
    NotifyContext ctx;
    Service::DispatchNotify(ctx, ann);
}

bool $(INTERFACENAME)TTMImpl::IsServiceReady() const
{
    return m_bServiceReady;
}

rqstid_t $(INTERFACENAME)TTMImpl::BroadcastRequest(const CoreClass& cc, const BroadcastTo *dest, flag_t flags, UserData *userdata)
{
    const TTMBroadcastTo *st = static_cast<const TTMBroadcastTo *>(dest);
	rqstid_t r = m_Dispatcher.BroadcastRequest(cc, st, flags, userdata);
    delete st;
    return r;
}

SendTo *$(INTERFACENAME)TTMImpl::GetServerSendTo()
{
	return new TTMSendTo(m_ServerInbox.c_str(), m_ServerIPAddress);
}

BroadcastTo *$(INTERFACENAME)TTMImpl::GetBroadcastToClients()
{
    // Subject should be defined in CoreMessaging.h
    return new TTMBroadcastTo(@(INTERFACENAME)_CLIENT_SUBJ);
}

BroadcastTo *$(INTERFACENAME)TTMImpl::GetBroadcastToServers()
{
    // Subject should be defined in CoreMessaging.h
    return new TTMBroadcastTo(@(INTERFACENAME)_SERVER_SUBJ);
}

rqstid_t $(INTERFACENAME)TTMImpl::SendRequestTo(const CoreClass& cc, const SendTo *dest, flag_t flags, UserData *userdata)
{
	const TTMSendTo *st = static_cast<const TTMSendTo *>(dest);
	rqstid_t r = m_Dispatcher.SendRequestTo(cc, st, flags, userdata);
	delete st;
	return r;
}

void $(INTERFACENAME)TTMImpl::SendNotifyTo(const CoreClass& cc, const SendTo *dest, flag_t flags)
{
	const TTMSendTo *st = static_cast<const TTMSendTo *>(dest);
	m_Dispatcher.SendNotifyTo(cc, st, flags);
	delete st;
}

void $(INTERFACENAME)TTMImpl::BroadcastNotify(const CoreClass& cc, const BroadcastTo *dest, flag_t flags)
{
    const TTMBroadcastTo *st = static_cast<const TTMBroadcastTo *>(dest);
	m_Dispatcher.BroadcastNotify(cc, st, flags);
    delete st;
}

void $(INTERFACENAME)TTMImpl::SendResponseTo(const RqstContext& ctx, const CoreClass& cc, flag_t flags)
{
	m_Dispatcher.SendResponseTo(ctx, cc, flags);
}

void $(INTERFACENAME)TTMImpl::FireResponse(const RspContext& ctx, const CoreClass& rqstData)
{
	m_Dispatcher.FireResponse(ctx, rqstData);
}

void $(INTERFACENAME)TTMImpl::OnRequest(RqstContext& ctx, CoreClass& data)
{
    Service::DispatchRequest(ctx, data);
}

void $(INTERFACENAME)TTMImpl::OnResponse(const RspContext& ctx, const CoreClass& data)
{
    switch (data.Id().GetCode()) {
        case $(INTERFACENAME)Announce_cc:
        {
            // We got our discover request
            const $(INTERFACENAME)Announce& ann = static_cast<const $(INTERFACENAME)Announce&>(data);
            if ($(INTERFACENAME)Announce::DISCOVER == ann.action)
            {
                switch (ctx.code) {
                case RSP_SUCCESS:
                    {                    
                        m_ServerInbox = ctx.inbox;
                        m_ServerIPAddress.s_addr = ctx.ipsender;
                        sysloginfo << "$(INTERFACENAME) server ANNOUNCE response, ipaddress: " << inet_ntoa(m_ServerIPAddress) << endsl;

                        m_bHaveAnnounce = true;
                        // Because this is a P2P response to our request, we can assume that the participant
                        // was attached to the response message.
                        m_bHaveParticipant = true;

                        // Dispatch a ServiceReady notification
                        DispatchServiceUp();           
                    }
                    break;
                case RSP_TIMEOUT:
                    syslogerror(L_WARNING) << "$(INTERFACENAME) server not found, RSP_TIMEOUT" << endsl;                
                    break;
                default:
                    syslogerror(L_ERROR) << "$(INTERFACENAME) Announce failed, RSP=" << ctx.responsetext << endsl;
                    break;
                }
            }
        }
        return;
    }
    Service::DispatchResponse(ctx, data);   // Dispatch through the registered interfaces
}

void $(INTERFACENAME)TTMImpl::OnNotify(const NotifyContext& ctx, const CoreClass& data)
{
    switch (data.Id().GetCode()) {
    case SendParticipant_cc:
        {
            // We got our participant
            m_bHaveParticipant = true;
            DispatchServiceUp();
        }
        return; // Don't dispatch to the interfaces

    case $(INTERFACENAME)Announce_cc:
        {
            // An $(INTERFACENAME) server has come up
            const $(INTERFACENAME)Announce& ann = static_cast<const $(INTERFACENAME)Announce&>(data);
            if (ann.action == $(INTERFACENAME)Announce::ANNOUNCE) { 
                if (true == m_bServiceReady)
                {
                    // Different server comming up as primary?
                    DispatchServiceDown();
                }
                m_ServerInbox = ctx.inbox;
                m_ServerIPAddress.s_addr = ctx.ipsender;
                sysloginfo << "Recieved $(INTERFACENAME) server ANNOUNCE notification, $(INTERFACENAME) server ipaddress: " << inet_ntoa(m_ServerIPAddress) << endsl;
                m_bHaveAnnounce = true;
                DispatchServiceUp();

                // Because this was a broadcast from XAdmin, we need to call GetPartipant
                // to get encryption working
                tt_openssl_ns::GetParticipant(ctx.inbox, m_Dispatcher.GetInboxName(), m_pSession);
            }
            if (ann.action == $(INTERFACENAME)Announce::SHUTDOWN) {                 
                sysloginfo << "Recieved $(INTERFACENAME) server SHUTDOWN notification, $(INTERFACENAME) server ipaddress: " << inet_ntoa(m_ServerIPAddress) << endsl;
                DispatchServiceDown();
            }
        }
        return;
    }
    Service::DispatchNotify(ctx, data);
}


/************************************************************************************************/
// Listen for heartbeats
void LSSrvSts::OnData(VIAmSession *, const VIAmSubject&, VIAmSender *, Streamable& obj, VIAmListener *)
{
    switch (obj.Id().GetCode())
    {
        case Reply_cc:
        {
            Reply *pReply = static_cast<Reply*>(&obj);
            switch(pReply->header.trnCode)
            {
                case TT_SRV_STAT_REPLY: 
                {
                    SAR_StatusPKT ssa(pReply->header.nElements) ;
                    ssa = static_cast<SAR_StatusPKT &>(pReply->GetPayload());

                    for (int iIdx = 0; iIdx < pReply->header.nElements; iIdx++)
                    {
                        StatusPKT& pkt = ssa[iIdx];
                        if (pkt.service == @(INTERFACENAME)_SERVICE_HEARTBEAT && pkt.status == TT_SERVER_ACTIVE)
                        {
                            m_pImpl->OnHeartbeat(pkt);
                        }
                    }
                }
            }
        }
    }
}

void  StatusTimer::OnTimer(VIAmSession*, VIAmTimer*)
{
    m_pImpl->OnStatusTimer();
}

} //namespace tt_%(INTERFACENAME)_ns

/*
  $Log: Interface/name_TTMImpl.cpp  $
  Revision 1.6 2005/07/27 08:40:16CDT ebradnick 
  33686: Restore 7.1 to 7.0.2
  Revision 1.4 2005/06/10 23:05:59CDT jrichards 
  Modifications to allow exporting from CPPClient
  Revision 1.3 2005/06/02 23:00:26CDT jrichards 
  Many changes to support RqstContext
  Revision 1.2 2005/05/28 23:22:58CDT jrichards 
  Modified templates to support current framework
  Revision 1.1 2005/05/16 09:57:36CDT jrichards 
  Initial revision
  Member added to project /SAN/mks-si/data1/projectsource/core/api/main/dev/coreframework/templates/templates.pj
 */
