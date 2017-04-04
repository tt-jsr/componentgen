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
 * $Source: Interface/name_ServerTTMImpl.cpp $ 
 * $Date: 2005/07/27 08:40:34CDT $ 
 * $Author: ebradnick $ 
 * $Revision: 1.6 $ 	
 ***************************************************************************/
/*
 * This file generated on $(DATE)
 */

#include "pch.h"
#include "%(INTERFACENAME)serverservice.h"
#include "%(INTERFACENAME)serverttmimpl.h"
#include "../%(INTERFACENAME)_common/%(INTERFACENAME)_common.h"

using namespace tt_coreframework_ns;
using namespace tt_stream_ns;

namespace tt_%(INTERFACENAME)_ns {

$(INTERFACENAME)ServerService::TTMCreateData::TTMCreateData(VIAmSession *p) 
: CreateData(I_TTM), pSess(p)
{

}

$(INTERFACENAME)ServerTTMImpl::$(INTERFACENAME)ServerTTMImpl()
: m_pSession(NULL)
{

}

$(INTERFACENAME)ServerTTMImpl::~$(INTERFACENAME)ServerTTMImpl()
{
	m_Dispatcher.Shutdown();
	delete m_pSession;
}

bool $(INTERFACENAME)ServerTTMImpl::Init(const CreateData& cd)
{
	const TTMCreateData& tcd = static_cast<const TTMCreateData&>(cd);
	m_pSession = new VIAmSession(*tcd.pSess);
	try {
		m_Dispatcher.Init(this, *m_pSession, @(INTERFACENAME)_SERVER_SUBJ);
	}
	catch (CoreFrameworkException&)
	{
		return false;
	}
	return $(INTERFACENAME)ServerService::Init(cd);
}

void $(INTERFACENAME)ServerTTMImpl::OnRequest(RqstContext& ctx, CoreClass& data)
{
    if (data.Id().GetCode() == $(INTERFACENAME)Announce_cc) {
        $(INTERFACENAME)Announce& ann = static_cast<$(INTERFACENAME)Announce&>(data);
        if (ann.action == $(INTERFACENAME)Announce::DISCOVER) {
            ctx.code = RSP_SUCCESS;
            sysloginfo << "Received $(INTERFACENAME)Announce::DISCOVER request" << endsl;
            SendResponseTo(ctx, ann);
        }
        if (ann.action == $(INTERFACENAME)Announce::PING) {
            ctx.code = RSP_SUCCESS;
            sysloginfo << "Received $(INTERFACENAME)Announce::PING request" << endsl;
            SendResponseTo(ctx, ann);
        }
        return;
    }
    Service::DispatchRequest(ctx, data);
}

void $(INTERFACENAME)ServerTTMImpl::OnNotify(const NotifyContext& ctx, const CoreClass& data)
{
    Service::DispatchNotify(ctx, data);
}

void $(INTERFACENAME)ServerTTMImpl::OnResponse(const RspContext& ctx, const CoreClass& data)
{
    Service::DispatchResponse(ctx, data);
}

SendTo *$(INTERFACENAME)ServerTTMImpl::GetSendTo(rqstid_t rqstid)
{
    return m_Dispatcher.GetSendToFromRqstid(rqstid);
}

string $(INTERFACENAME)ServerTTMImpl::GetInboxName()
{
    return m_Dispatcher.GetInboxName();
}

BroadcastTo *$(INTERFACENAME)ServerTTMImpl::GetBroadcastToClients()
{
    return new TTMBroadcastTo(@(INTERFACENAME)_CLIENT_SUBJ);
}

BroadcastTo *$(INTERFACENAME)ServerTTMImpl::GetBroadcastToServers()
{
    return new TTMBroadcastTo(@(INTERFACENAME)_SERVER_SUBJ);
}

rqstid_t $(INTERFACENAME)ServerTTMImpl::SendRequestTo(const CoreClass& cc, const SendTo *dest, flag_t flags, UserData *userdata)
{
	const TTMSendTo *st = static_cast<const TTMSendTo *>(dest);
	rqstid_t r = m_Dispatcher.SendRequestTo(cc, st, flags, userdata);
	delete st;
	return r;
}

void $(INTERFACENAME)ServerTTMImpl::SendNotifyTo(const CoreClass& cc, const SendTo *dest, flag_t flags)
{
	const TTMSendTo *st = static_cast<const TTMSendTo *>(dest);
	m_Dispatcher.SendNotifyTo(cc, st, flags);
	delete st;
}

rqstid_t $(INTERFACENAME)ServerTTMImpl::BroadcastRequest(const CoreClass& cc, const BroadcastTo *dest, flag_t flags, UserData *userdata)
{
    const TTMBroadcastTo *st = static_cast<const TTMBroadcastTo *>(dest);
	rqstid_t r = m_Dispatcher.BroadcastRequest(cc, st, flags, userdata);
    delete st;
    return r;
}

void $(INTERFACENAME)ServerTTMImpl::BroadcastNotify(const CoreClass& cc, const BroadcastTo *dest, flag_t flags)
{
    const TTMBroadcastTo *st = static_cast<const TTMBroadcastTo *>(dest);
	m_Dispatcher.BroadcastNotify(cc, st, flags);
    delete st;
}

void $(INTERFACENAME)ServerTTMImpl::SendResponseTo(const RqstContext& ctx, const CoreClass& cc, flag_t flags)
{
	m_Dispatcher.SendResponseTo(ctx, cc, flags);
}

void $(INTERFACENAME)ServerTTMImpl::FireResponse(const RspContext& ctx, const CoreClass& rqstData)
{
	m_Dispatcher.FireResponse(ctx, rqstData);
}

} // namespace tt_%(INTERFACENAME)_ns

/*
  $Log: Interface/name_ServerTTMImpl.cpp  $
  Revision 1.6 2005/07/27 08:40:34CDT ebradnick 
  33686: Restore 7.1 to 7.0.2
  Revision 1.4 2005/06/10 23:05:57CDT jrichards 
  Modifications to allow exporting from CPPClient
  Revision 1.3 2005/06/02 23:00:21CDT jrichards 
  Many changes to support RqstContext
  Revision 1.2 2005/05/28 23:22:32CDT jrichards 
  Modified templates to support current framework
  Revision 1.1 2005/05/16 09:57:31CDT jrichards 
  Initial revision
  Member added to project /SAN/mks-si/data1/projectsource/core/api/main/dev/coreframework/templates/templates.pj
 */
