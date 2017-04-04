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
 * $Source: Interface/name_ServerInterface.cpp $ 
 * $Date: 2005/06/10 23:05:55CDT $ 
 * $Author: jrichards $ 
 * $Revision: 1.3 $ 	
 ***************************************************************************/
/*
 * This file generated on $(DATE)
 */

#include "pch.h"
#include "../../Common/ServiceInterface.h"
#include "%(INTERFACENAME)serverinterface.h"
#include "%(INTERFACENAME)serverservice.h"
#include "../../Common/Payload.h"
#include <time.h>

using namespace tt_coreframework_ns;
using namespace std;
using namespace tt_core_ns;

namespace tt_%(INTERFACENAME)_ns {

void $(INTERFACENAME)ServerInterface::OnResponse(const RspContext& ctx, const CoreClass& data)
{
	// TODO: based the type of the response object, dispatch to the proper callback.
	//switch (data.Id().GetCode()) {
	//default:
	//	break;
	//}
}

void $(INTERFACENAME)ServerInterface::OnNotify(const NotifyContext&, const CoreClass& data)
{
	// TODO: based the type of the notify object, dispatch to the proper callback.
	//switch (data.Id().GetCode()) {	
	//default:
	//	break;
	//}
}

void $(INTERFACENAME)ServerInterface::OnRequest(RqstContext&, CoreClass& data)
{
	// TODO: based the type of the request object, dispatch to the proper callback.
	//switch (data.Id().GetCode()) {		
	//default:
	//	break;
	//}
}

rqstid_t $(INTERFACENAME)ServerInterface::SendRequestTo(const CoreClass& cc, const SendTo *dest, flag_t flags, UserData *userdata)
{
    $(INTERFACENAME)ServerService *pService = $(INTERFACENAME)ServerService::GetService();
    if (pService) {
	    return pService->SendRequestTo(cc, dest, flags, userdata);
    }
    return 0;
}

void $(INTERFACENAME)ServerInterface::SendNotifyTo(const CoreClass& cc, const SendTo *dest, flag_t flags)
{
	$(INTERFACENAME)ServerService *pService = $(INTERFACENAME)ServerService::GetService();
    if (pService) {
	    pService->SendNotifyTo(cc, dest, flags);
    }
}

rqstid_t $(INTERFACENAME)ServerInterface::BroadcastRequest(const CoreClass& cc, const BroadcastTo *dest, flag_t flags, UserData *userdata)
{
	$(INTERFACENAME)ServerService *pService = $(INTERFACENAME)ServerService::GetService();
    if (pService) {
	    return pService->BroadcastRequest(cc, dest, flags, userdata);
    }
    return 0;
}

void $(INTERFACENAME)ServerInterface::BroadcastNotify(const CoreClass& cc, const BroadcastTo *dest, flag_t flags)
{
	$(INTERFACENAME)ServerService *pService = $(INTERFACENAME)ServerService::GetService();
    if (pService) {
	    pService->BroadcastNotify(cc, dest, flags);
    }
}

void $(INTERFACENAME)ServerInterface::SendResponseTo(const RqstContext& ctx, const CoreClass& cc, flag_t flags)
{
	$(INTERFACENAME)ServerService *pService = $(INTERFACENAME)ServerService::GetService();
    if (pService) {
	    pService->SendResponseTo(ctx, cc, flags);
    }
}

BroadcastTo *$(INTERFACENAME)ServerInterface::GetBroadcastToClients()
{
    $(INTERFACENAME)ServerService *pService = $(INTERFACENAME)ServerService::GetService();
    if (pService) {
        return pService->GetBroadcastToClients();
    }
    return NULL;
}

SendTo *$(INTERFACENAME)ServerInterface::GetSendTo(rqstid_t r)
{
    $(INTERFACENAME)ServerService *pService = $(INTERFACENAME)ServerService::GetService();
    if (pService) {
        return pService->GetSendTo(r);
    }
    return NULL;
}

} // namespace tt_%(INTERFACENAME)_ns