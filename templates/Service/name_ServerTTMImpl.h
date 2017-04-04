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
 * $Source: Interface/name_ServerTTMImpl.h $ 
 * $Date: 2005/07/27 08:40:33CDT $ 
 * $Author: ebradnick $ 
 * $Revision: 1.5 $ 	
 ***************************************************************************/
/*
 * This file generated on $(DATE)
 */

#ifndef $(INTERFACENAME)SERVERTTMIMPL__H_
#define $(INTERFACENAME)SERVERTTMIMPL__H_

#include "%(INTERFACENAME)serverservice.h"
#include "../../Common/Dispatcher.h"
#include <map>

namespace tt_%(INTERFACENAME)_ns {

	class $(INTERFACENAME)ServerTTMImpl : public $(INTERFACENAME)ServerService {
	public:
		$(INTERFACENAME)ServerTTMImpl();		

		virtual tt_coreframework_ns::rqstid_t BroadcastRequest(const CoreClass& cc, const tt_coreframework_ns::BroadcastTo *, tt_coreframework_ns::flag_t flags = tt_coreframework_ns::none, tt_coreframework_ns::UserData *userdata = NULL);
		virtual tt_coreframework_ns::rqstid_t SendRequestTo(const CoreClass& cc, const tt_coreframework_ns::SendTo *, tt_coreframework_ns::flag_t flags = tt_coreframework_ns::none, tt_coreframework_ns::UserData *userdata = NULL);
		virtual void SendNotifyTo(const CoreClass&, const tt_coreframework_ns::SendTo *, tt_coreframework_ns::flag_t flags = tt_coreframework_ns::none);
		virtual void BroadcastNotify(const CoreClass&, const tt_coreframework_ns::BroadcastTo *, tt_coreframework_ns::flag_t flags = tt_coreframework_ns::none);
		virtual void SendResponseTo(const tt_coreframework_ns::RqstContext&, const CoreClass&, tt_coreframework_ns::flag_t flags = tt_coreframework_ns::none);
		virtual tt_coreframework_ns::SendTo *GetSendTo(tt_coreframework_ns::rqstid_t);
        virtual tt_coreframework_ns::BroadcastTo *GetBroadcastToClients();
        virtual tt_coreframework_ns::BroadcastTo *GetBroadcastToServers();
		virtual void FireResponse(const tt_coreframework_ns::RspContext&, const CoreClass& rqstData);
	protected:		
		virtual bool Init(const CreateData&);
		virtual ~$(INTERFACENAME)ServerTTMImpl();
        virtual string GetInboxName();
        virtual void OnResponse(const tt_coreframework_ns::RspContext&, const CoreClass& data);
        virtual void OnNotify(const tt_coreframework_ns::NotifyContext&, const CoreClass& data);
        virtual void OnRequest(tt_coreframework_ns::RqstContext&, CoreClass& data);
	protected:
		tt_stream_ns::VIAmSession *m_pSession;
		tt_coreframework_ns::Dispatcher m_Dispatcher;
	};
};	// namespace tt_%(INTERFACENAME)_ns

#endif // $(INTERFACENAME)SERVERTTMIMPL__H_

/*
  $Log: Interface/name_ServerTTMImpl.h  $
  Revision 1.5 2005/07/27 08:40:33CDT ebradnick 
  33686: Restore 7.1 to 7.0.2
  Revision 1.3 2005/06/02 23:00:22CDT jrichards 
  Many changes to support RqstContext
  Revision 1.2 2005/05/28 23:22:55CDT jrichards 
  Modified templates to support current framework
  Revision 1.1 2005/05/16 09:57:33CDT jrichards 
  Initial revision
  Member added to project /SAN/mks-si/data1/projectsource/core/api/main/dev/coreframework/templates/templates.pj
 */
