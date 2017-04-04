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
 * $Source: Interface/name_ServerInterface.h $ 
 * $Date: 2005/07/27 08:40:12CDT $ 
 * $Author: ebradnick $ 
 * $Revision: 1.6 $ 	
 ***************************************************************************/
/*
 * This file generated on $(DATE)
 */

#ifndef __$(INTERFACENAME)ServerInterface__H
#define __$(INTERFACENAME)ServerInterface__H

#include <string>
#include <vector>
#include "../../Common/ServiceInterface.h"
#include "../%(INTERFACENAME)_common/%(INTERFACENAME)_common.h"

namespace tt_%(INTERFACENAME)_ns {
	/** 
	$(INTERFACENAME) server interface

	<P>To use this interface derive from this class and implement the overrides. It is not necessary 
	to implement all overrides in the same derived class, the framework is designed to allow 
	implementation into distinct classes so the application can separate functionality if needed.

	Call $(INTERFACENAME)ServerService::GetServer()->RegisterInterface() to register a derived class to receive callbacks.

	The RqstContext contains the following when a request is received:
		rqstid_t rqstid;			// The request id from the client
		RspCode code;				// After processing the request, set the response code here
		string responsetext;		// Set any desired text here that could be used to display information to the user about the error

	The RspContext is returned when a response is received. it contains the following data:
		rqstid_t rqstid;			// The request id of the original request
		RspCode code;				// The response or return code
		string responsetext;		// A string may also be provided containing text about the response
		CoreClass *pRequestData;	// The original request data
		void *userdata;				// Opaque data that was passed in with the original request

	The framework also allows the local instantiation of an interface class for the purposes of
	sending data. e.g.

	void foo()
	{
		$(INTERFACENAME)Interface intfc;

		intfc.MyMethod("arg1", arg2);
	}
	*/
	class $(INTERFACENAME)ServerInterface : public tt_coreframework_ns::ServiceInterface {
	public:

		virtual void OnSampleRsp () {}

	public:
		/**********************************************************************
		* Broadcast an asynchronous request.
		*       cc: The data to be sent
        *     dest: The broadcast subject
        *    flags: Various flags, see Payload.h
		* userdata: This is caller defined opaque data that will be returned to the
		*           caller when the response either times out or is received.
		* Returns:  A request id. When the response is received, this request id can
		*           be used to associate the request with the response.
		*           The request id will be zero on error.
		* Throws a CoreFrameworkException
		*/
		tt_coreframework_ns::rqstid_t BroadcastRequest(const CoreClass& cc, const tt_coreframework_ns::BroadcastTo *dest, tt_coreframework_ns::flag_t flags, tt_coreframework_ns::UserData *userdata = NULL);

		/**********************************************************************
		* Send an asynchronous request to the specified destination
		*       cc: The data to be sent
		*     dest: The destination of the request
        *    flags: Various flags, see Payload.h
		* userdata: This is caller defined opaque data that will be returned to the
		*           caller when the response either times out or is received.
		* Returns:  A request id. When the response is received, this request id can
		*           be used to associate the request with the response.
		*           The request id will be zero on error.
		* Throws a CoreFrameworkException
		*/
		tt_coreframework_ns::rqstid_t SendRequestTo(const CoreClass& cc, const tt_coreframework_ns::SendTo *dest, tt_coreframework_ns::flag_t flags, tt_coreframework_ns::UserData *userdata = NULL);

		/**********************************************************************
		* Broadcast a notification. No response will be received
        *       cc: The data to be sent
        *     dest: The broadcast subject
        *    flags: Various flags, see Payload.h
		* Throws a CoreFrameworkException
		*/
		void BroadcastNotify(const CoreClass& cc, const tt_coreframework_ns::BroadcastTo *dest, tt_coreframework_ns::flag_t flags);

		/**********************************************************************
		* Send a notification to the the spcified destination. No response will be received
        *       cc: The data to be sent
		*     dest: The destination of the request
        *    flags: Various flags, see Payload.h
		* Throws a CoreFrameworkException
		*/
		void SendNotifyTo(const CoreClass& cc, const tt_coreframework_ns::SendTo *dest, tt_coreframework_ns::flag_t flags);

		/************************************************************************
		* Send a response to a previous request.
		* RqstContext: The request id received in the request.
		*     cc: The response data
        *  flags: Various flags, see Payload.h
		* 
		* The RqstContext is used as a key to retrieve the requestors inbox. It must be the
		* correct context to send a response.
		* Throws a CoreFrameworkException
		*/
		void SendResponseTo(const tt_coreframework_ns::RqstContext&, const CoreClass&, tt_coreframework_ns::flag_t flags);

		/**********************************************************************
         * Get the subject to broadcast to the clients
         */
        tt_coreframework_ns::BroadcastTo *GetBroadcastToClients();

        tt_coreframework_ns::SendTo *GetSendTo(tt_coreframework_ns::rqstid_t);
	private:
		// Implementation. Do not call
		virtual void OnResponse(const tt_coreframework_ns::RspContext&, const CoreClass& data);
		virtual void OnNotify(const tt_coreframework_ns::NotifyContext&, const CoreClass& data);
		virtual void OnRequest(tt_coreframework_ns::RqstContext&, CoreClass& data);
	};

}; // namespace tt_%(INTERFACENAME)_ns

#endif	// __$(INTERFACENAME)ServerInterface__H

/*
  $Log: Interface/name_ServerInterface.h  $
  Revision 1.6 2005/07/27 08:40:12CDT ebradnick 
  33686: Restore 7.1 to 7.0.2
  Revision 1.4 2005/06/07 15:21:01CDT jrichards 
  Remodev TT_LINK_DLL macros
  Revision 1.3 2005/06/02 23:00:18CDT jrichards 
  Many changes to support RqstContext
  Revision 1.2 2005/05/28 23:22:33CDT jrichards 
  Modified templates to support current framework
  Revision 1.1 2005/05/16 09:57:28CDT jrichards 
  Initial revision
  Member added to project /SAN/mks-si/data1/projectsource/core/api/main/dev/coreframework/templates/templates.pj
 */
