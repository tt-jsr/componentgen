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
 * $Source: Interface/name_Interface.cpp $ 
 * $Date: 2005/06/10 23:05:54CDT $ 
 * $Author: jrichards $ 
 * $Revision: 1.3 $ 	
 ***************************************************************************/
/*
 * This file generated on $(DATE)
 */

#include "pch.h"
#include "../../Common/ServiceInterface.h"
#include "%(INTERFACENAME)interface.h"
#include "%(INTERFACENAME)service.h"
#include "../../Common/Payload.h"
#include <time.h>

using namespace tt_coreframework_ns;
using namespace std;
using namespace tt_core_ns;

namespace tt_%(INTERFACENAME)_ns {

rqstid_t $(INTERFACENAME)Interface::Ping()
{
    $(INTERFACENAME)Announce ann;
    ann.action = $(INTERFACENAME)Announce::PING;
    return SendRequestTo(ann, GetServerSendTo());
}

void $(INTERFACENAME)Interface::OnResponse(const RspContext& ctx, const CoreClass& data)
{
	switch (data.Id().GetCode()) {
    case $(INTERFACENAME)Announce_cc:
        {
            const $(INTERFACENAME)Announce& ann = static_cast<const $(INTERFACENAME)Announce&>(data);
            if (ann.action == $(INTERFACENAME)Announce::PING)
            {
                OnPing(ctx);
            }
        }
        break;
	default:
		break;
	}
}

void $(INTERFACENAME)Interface::OnNotify(const NotifyContext&, const CoreClass& data)
{
	// TODO: based the type of the notify object, dispatch to the proper callback.
	switch (data.Id().GetCode()) {
    case $(INTERFACENAME)Announce_cc:   // TODO: This class code need to be defined
        {
            const $(INTERFACENAME)Announce& ann = static_cast<const $(INTERFACENAME)Announce&>(data);
            if (ann.action == $(INTERFACENAME)Announce::ANNOUNCE)
            {
                OnServerUp();
            }
            if (ann.action == $(INTERFACENAME)Announce::SHUTDOWN)
            {
                OnServerDown();
            }
        }
        break;
	default:
		break;
	}
}

void $(INTERFACENAME)Interface::OnRequest(RqstContext&, CoreClass& data)
{
	// TODO: based the type of the request object, dispatch to the proper callback.
	//switch (data.Id().GetCode()) {
	//default:
	//	break;
	//}
}


rqstid_t $(INTERFACENAME)Interface::SendRequestTo(const CoreClass& cc, const SendTo *dest, flag_t flags, UserData *userdata)
{
    $(INTERFACENAME)Service *pService = $(INTERFACENAME)Service::GetService();
    if (pService) {
	    return pService->SendRequestTo(cc, dest, flags, userdata);
    }
    return 0;
}

void $(INTERFACENAME)Interface::SendNotifyTo(const CoreClass& cc, const SendTo *dest, flag_t flags)
{
	$(INTERFACENAME)Service *pService = $(INTERFACENAME)Service::GetService();
    if (pService) {
	    pService->SendNotifyTo(cc, dest, flags);
    }
}

rqstid_t $(INTERFACENAME)Interface::BroadcastRequest(const CoreClass& cc, const BroadcastTo *dest, flag_t flags, UserData *userdata)
{
	$(INTERFACENAME)Service *pService = $(INTERFACENAME)Service::GetService();
    if (pService) {
	    return pService->BroadcastRequest(cc, dest, flags, userdata);
    }
    return 0;
}

void $(INTERFACENAME)Interface::BroadcastNotify(const CoreClass& cc, const BroadcastTo *dest, flag_t flags)
{
	$(INTERFACENAME)Service *pService = $(INTERFACENAME)Service::GetService();
    if (pService) {
	    pService->BroadcastNotify(cc, dest, flags);
    }
}

void $(INTERFACENAME)Interface::SendResponseTo(const RqstContext& ctx, const CoreClass& cc, flag_t flags)
{
	$(INTERFACENAME)Service *pService = $(INTERFACENAME)Service::GetService();
    if (pService) {
	    pService->SendResponseTo(ctx, cc, flags);
    }
}

SendTo *$(INTERFACENAME)Interface::GetServerSendTo()
{
	$(INTERFACENAME)Service *pService = $(INTERFACENAME)Service::GetService();
    if (pService) {
	    return pService->GetServerSendTo();
    }
    return NULL;
}
} //namespace tt_%(INTERFACENAME)_ns
