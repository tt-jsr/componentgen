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
 * $Source: Interface/name_ServerService.h $ 
 * $Date: 2005/07/27 08:40:35CDT $ 
 * $Author: ebradnick $ 
 * $Revision: 1.7 $ 	
 ***************************************************************************/
/*
 * This file generated on $(DATE)
 */

#ifndef __$(INTERFACENAME)ServerService__H
#define __$(INTERFACENAME)ServerService__H

#include <string>
#include <vector>
#include "%(INTERFACENAME)serverinterface.h"
#include "../../Common/Service.h"

namespace tt_stream_ns {
	class VIAmSession;
};

namespace tt_%(INTERFACENAME)_ns {
/***************************************************************************************
 * Interface for $(INTERFACENAME)ServiceService.
 */

	class $(INTERFACENAME)ServerService : public tt_coreframework_ns::Service {
	public:
		enum Implementation {
			I_TTM,
		};

		class CreateData {
		public:
			CreateData(Implementation i);
			Implementation imp;
		};

		// Initialization data for creating a TTM implementation of this interface
		class TTMCreateData : public CreateData {
		public:
			TTMCreateData(tt_stream_ns::VIAmSession *p);
			tt_stream_ns::VIAmSession *pSess;
		};

		// Create a client interface with the given implementation.
		// Will fail if Create() has already been called
		static bool Create(const CreateData&);

		// Destroy the client interface.
		static void Destroy();

		// Get a pointer to the service. It is not necessary to maintain a reference
		// to this interface for the callbacks to operate.
		// Returns: NULL if Create() was not called or construction failed.
		static $(INTERFACENAME)ServerService *GetService();

		// Returns the service name. This is used for logging mostly
		const char *GetServiceName() const { return "$(INTERFACENAME)ServerService";}

        // Get the SendTo from a request being processed
        virtual tt_coreframework_ns::SendTo *GetSendTo(tt_coreframework_ns::rqstid_t) = 0;

        // Methods similar to this can be used to get broadcast destinations
        // Example:
        //     GetBroadcastToClients(), GetBroadcastToOrderServers() etc...
        virtual tt_coreframework_ns::BroadcastTo *GetBroadcastToClients() = 0;
        virtual tt_coreframework_ns::BroadcastTo *GetBroadcastToServers() = 0;
	protected:
		$(INTERFACENAME)ServerService();
		virtual ~$(INTERFACENAME)ServerService();

		virtual void OnResponse(const tt_coreframework_ns::RspContext&, const CoreClass& data);
		virtual void OnNotify(const tt_coreframework_ns::NotifyContext&, const CoreClass& data);
		virtual void OnRequest(tt_coreframework_ns::RqstContext&, CoreClass& data);

		// Perform needed initialization from the supplied data
		// Return false to abort creation
		virtual bool Init(const CreateData&) = 0;
	private:	
		static $(INTERFACENAME)ServerService *theObject;		
	};

}; // namespace tt_%(INTERFACENAME)_ns

#endif	// __$(INTERFACENAME)ServerService__H

/*
  $Log: Interface/name_ServerService.h  $
  Revision 1.7 2005/07/27 08:40:35CDT ebradnick 
  33686: Restore 7.1 to 7.0.2
  Revision 1.4 2005/06/07 15:20:57CDT jrichards 
  Remodev TT_LINK_DLL macros
  Revision 1.3 2005/06/02 23:00:20CDT jrichards 
  Many changes to support RqstContext
  Revision 1.2 2005/05/28 23:22:31CDT jrichards 
  Modified templates to support current framework
  Revision 1.1 2005/05/16 09:57:30CDT jrichards 
  Initial revision
  Member added to project /SAN/mks-si/data1/projectsource/core/api/main/dev/coreframework/templates/templates.pj
 */
