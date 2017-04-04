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
 * $Source: Interface/name_ServerService.cpp $ 
 * $Date: 2005/07/27 08:40:15CDT $ 
 * $Author: ebradnick $ 
 * $Revision: 1.6 $ 	
 ***************************************************************************/
/*
 * This file generated on $(DATE)
 */

#include "pch.h"
#include "%(INTERFACENAME)serverinterface.h"
#include "%(INTERFACENAME)serverttmimpl.h"

using namespace tt_coreframework_ns;
using namespace std;
using namespace tt_coreutils_ns;

namespace tt_%(INTERFACENAME)_ns {

$(INTERFACENAME)ServerService *$(INTERFACENAME)ServerService::theObject = NULL;

$(INTERFACENAME)ServerService::CreateData::CreateData(Implementation i) 
: imp(i)
{

}

$(INTERFACENAME)ServerService::$(INTERFACENAME)ServerService()
{

}

$(INTERFACENAME)ServerService::~$(INTERFACENAME)ServerService()
{

}

// Create a client interface with the given implementation.
bool $(INTERFACENAME)ServerService::Create(const CreateData& cd)
{
	if (theObject)
		return false;

	switch(cd.imp) {
	case I_TTM:
		theObject = new $(INTERFACENAME)ServerTTMImpl();
		break;
	}
	
	if (NULL == theObject)
		return false;
	bool r = theObject->Init(cd);
	if (false == r) {
		delete theObject;
		theObject = NULL;
		return false;
	}
	return true;
}

// Destroy the client interface.
void $(INTERFACENAME)ServerService::Destroy()
{
	delete theObject;
	theObject = NULL;
}

bool $(INTERFACENAME)ServerService::Init(const CreateData& cd)
{
	const TTMCreateData& tcd = static_cast<const TTMCreateData&>(cd);
	
	return true;
}

// Get a pointer to the interface. It is not necessary to maintain a reference
// to this interface for the callbacks to operate.
// Returns: NULL if Create() was not called or construction failed.
$(INTERFACENAME)ServerService *$(INTERFACENAME)ServerService::GetService()
{
	return theObject;
}

void $(INTERFACENAME)ServerService::OnResponse(const RspContext& ctx, const CoreClass& data)
{
	Service::DispatchResponse(ctx, data);
}

void $(INTERFACENAME)ServerService::OnNotify(const NotifyContext& ctx, const CoreClass& data)
{
	Service::DispatchNotify(ctx, data);
}

void $(INTERFACENAME)ServerService::OnRequest(RqstContext& ctx, CoreClass& data)
{
	Service::DispatchRequest(ctx, data);
}

} //namespace tt_%(INTERFACENAME)_ns
/*
  $Log: Interface/name_ServerService.cpp  $
  Revision 1.6 2005/07/27 08:40:15CDT ebradnick 
  33686: Restore 7.1 to 7.0.2
  Revision 1.4 2005/06/10 23:05:56CDT jrichards 
  Modifications to allow exporting from CPPClient
  Revision 1.3 2005/06/02 23:00:19CDT jrichards 
  Many changes to support RqstContext
  Revision 1.2 2005/05/28 23:22:22CDT jrichards 
  Modified templates to support current framework
  Revision 1.1 2005/05/16 09:57:29CDT jrichards 
  Initial revision
  Member added to project /SAN/mks-si/data1/projectsource/core/api/main/dev/coreframework/templates/templates.pj
 */
