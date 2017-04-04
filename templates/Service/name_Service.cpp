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
 * $Source: Interface/name_Service.cpp $ 
 * $Date: 2005/07/27 08:40:25CDT $ 
 * $Author: ebradnick $ 
 * $Revision: 1.6 $ 	
 ***************************************************************************/
/*
 * This file generated on $(DATE)
 */

#include "pch.h"
#include "%(INTERFACENAME)service.h"
#include "%(INTERFACENAME)ttmimpl.h"

using namespace tt_coreframework_ns;
using namespace std;
using namespace tt_coreutils_ns;
using namespace tt_stream_ns;

namespace tt_%(INTERFACENAME)_ns {

$(INTERFACENAME)Service *$(INTERFACENAME)Service::theObject = NULL;

$(INTERFACENAME)Service::CreateData::CreateData(Implementation i) 
: imp(i)
{

}

$(INTERFACENAME)Service::TTMCreateData::TTMCreateData(VIAmSession *p) 
: CreateData(I_TTM), pSess(p)
{

}

$(INTERFACENAME)Service::$(INTERFACENAME)Service()
{

}

$(INTERFACENAME)Service::~$(INTERFACENAME)Service()
{

}

// Create a client interface with the given implementation.
bool $(INTERFACENAME)Service::Create(const CreateData& cd)
{
	if (theObject)
		return false;

	switch(cd.imp) {
	case I_TTM:
		theObject = new $(INTERFACENAME)TTMImpl();
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
void $(INTERFACENAME)Service::Destroy()
{
	delete theObject;
	theObject = NULL;
}

bool $(INTERFACENAME)Service::Init(const CreateData& cd)
{
	const TTMCreateData& tcd = static_cast<const TTMCreateData&>(cd);
	
	return true;
}

// Get a pointer to the Service. It is not necessary to maintain a reference
// to this interface for the callbacks to operate.
// Returns: NULL if Create() was not called or construction failed.
$(INTERFACENAME)Service *$(INTERFACENAME)Service::GetService()
{
	return theObject;
}

void $(INTERFACENAME)Service::OnResponse(const RspContext& ctx, const CoreClass& data)
{
	Service::DispatchResponse(ctx, data);
}

void $(INTERFACENAME)Service::OnNotify(const NotifyContext& ctx, const CoreClass& data)
{
	Service::DispatchNotify(ctx, data);
}

void $(INTERFACENAME)Service::OnRequest(RqstContext& ctx, CoreClass& data)
{
	Service::DispatchRequest(ctx, data);
}

} // namespace tt_%(INTERFACENAME)_ns

/*
  $Log: Interface/name_Service.cpp  $
  Revision 1.6 2005/07/27 08:40:25CDT ebradnick 
  33686: Restore 7.1 to 7.0.2
  Revision 1.4 2005/06/10 23:05:58CDT jrichards 
  Modifications to allow exporting from CPPClient
  Revision 1.3 2005/06/02 23:00:23CDT jrichards 
  Many changes to support RqstContext
  Revision 1.2 2005/05/28 23:22:54CDT jrichards 
  Modified templates to support current framework
  Revision 1.1 2005/05/16 09:57:34CDT jrichards 
  Initial revision
  Member added to project /SAN/mks-si/data1/projectsource/core/api/main/dev/coreframework/templates/templates.pj
 */
