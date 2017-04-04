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
 * $Source: Interface/name_TTMImpl.h $ 
 * $Date: 2005/07/27 08:40:14CDT $ 
 * $Author: ebradnick $ 
 * $Revision: 1.5 $ 	
 ***************************************************************************/
/*
 * This file generated on $(DATE)
 */

#ifndef $(INTERFACENAME)TTMIMPL__H_
#define $(INTERFACENAME)TTMIMPL__H_

#include "%(INTERFACENAME)service.h"
#include "../../Common/Dispatcher.h"
#include <map>

namespace tt_%(INTERFACENAME)_ns {

    class $(INTERFACENAME)TTMImpl;

    // Listener for $(INTERFACENAME) heartbeats
    class LSSrvSts : public tt_stream_ns::VIAmCallback
    {
    public:

	    LSSrvSts($(INTERFACENAME)TTMImpl *pImpl, tt_stream_ns::VIAmSession& sess_,const std::string subj_)
        {   
            m_Lstnr = sess_.CreateListener(subj_,*this);
            m_pImpl = pImpl;
        }
    protected:
        /*virtual*/ void OnData(tt_stream_ns::VIAmSession*, const tt_stream_ns::VIAmSubject& incomingSubj_,
            tt_stream_ns::VIAmSender* sender_, tt_stream_ns::Streamable &obj, tt_stream_ns::VIAmListener*);
    private:
        $(INTERFACENAME)TTMImpl *m_pImpl;
        tt_stream_ns::VIAmListener m_Lstnr;
    };

    // Timer to generate server down if we stop getting heartbeats
    class StatusTimer : public tt_stream_ns::VIAmCallback
    {
    public:
        StatusTimer($(INTERFACENAME)TTMImpl *pImpl, tt_stream_ns::VIAmSession& sess_)
        {
		    m_pTimer = sess_.createTimer(*this, WatchDogIntv, true);
            m_pImpl = pImpl;
        }

	    ~StatusTimer() { delete m_pTimer; }

        /*virtual*/ void  OnTimer(tt_stream_ns::VIAmSession*, tt_stream_ns::VIAmTimer*);
    private:
        $(INTERFACENAME)TTMImpl *m_pImpl;
        tt_stream_ns::VIAmTimer *m_pTimer;
    };

	class $(INTERFACENAME)TTMImpl : public $(INTERFACENAME)Service {
	public:
		$(INTERFACENAME)TTMImpl();		

		virtual tt_coreframework_ns::rqstid_t SendRequestTo(const CoreClass& cc, const tt_coreframework_ns::SendTo *, tt_coreframework_ns::flag_t flags = tt_coreframework_ns::none, tt_coreframework_ns::UserData *userdata = NULL);
		virtual tt_coreframework_ns::rqstid_t BroadcastRequest(const CoreClass& cc, const tt_coreframework_ns::BroadcastTo *, tt_coreframework_ns::flag_t flags = tt_coreframework_ns::none, tt_coreframework_ns::UserData *userdata = NULL);
		virtual void SendNotifyTo(const CoreClass&, const tt_coreframework_ns::SendTo *, tt_coreframework_ns::flag_t flags = tt_coreframework_ns::none);
		virtual void BroadcastNotify(const CoreClass&, const tt_coreframework_ns::BroadcastTo *, tt_coreframework_ns::flag_t flags = tt_coreframework_ns::none);
		virtual void SendResponseTo(const tt_coreframework_ns::RqstContext&, const CoreClass&, tt_coreframework_ns::flag_t flags = tt_coreframework_ns::none);
		virtual tt_coreframework_ns::SendTo *GetServerSendTo();
        virtual tt_coreframework_ns::BroadcastTo *GetBroadcastToClients();
        virtual tt_coreframework_ns::BroadcastTo *GetBroadcastToServers();
		virtual void FireResponse(const tt_coreframework_ns::RspContext&, const CoreClass& rqstData);
        /** Returns true when the XAdmin server has been located */
        virtual bool IsServiceReady() const;

        // Heartbeat listener calls this everytime a heartbeat is received.
        void OnHeartbeat(tt_core_ns::StatusPKT&);
        void OnStatusTimer();
	protected:		
		virtual bool Init(const CreateData&);
		virtual ~$(INTERFACENAME)TTMImpl();

        virtual void OnResponse(const tt_coreframework_ns::RspContext&, const CoreClass& data);
        virtual void OnNotify(const tt_coreframework_ns::NotifyContext&, const CoreClass& data);
        virtual void OnRequest(tt_coreframework_ns::RqstContext&, CoreClass& data);

        void DispatchServiceUp();
        void DispatchServiceDown();
        void SendDiscoverRequest();
	protected:
		tt_stream_ns::VIAmSession *m_pSession;
		tt_coreframework_ns::Dispatcher m_Dispatcher;
    private:
        // Inbox of the $(INTERFACENAME) server
        std::string m_ServerInbox;

        // IP adress of the $(INTERFACENAME) server
        struct in_addr m_ServerIPAddress;

        // rqstid of the Announce::DISCOVER request
        tt_coreframework_ns::rqstid_t m_annrqst; 

        bool m_bServiceReady;
        bool m_bHaveParticipant;
        bool m_bHaveAnnounce;

        // Listener for $(INTERFACENAME) heartbeats
        LSSrvSts *m_pStatusHandler;
        StatusTimer *m_pStatusTimer;
        time_t m_lastStatus;
	};
};	// namespace tt_%(INTERFACENAME)_ns

#endif // $(INTERFACENAME)TTMIMPL__H_

/*
  $Log: Interface/name_TTMImpl.h  $
  Revision 1.5 2005/07/27 08:40:14CDT ebradnick 
  33686: Restore 7.1 to 7.0.2
  Revision 1.3 2005/06/02 23:00:27CDT jrichards 
  Many changes to support RqstContext
  Revision 1.2 2005/05/28 23:22:28CDT jrichards 
  Modified templates to support current framework
  Revision 1.1 2005/05/16 09:57:37CDT jrichards 
  Initial revision
  Member added to project /SAN/mks-si/data1/projectsource/core/api/main/dev/coreframework/templates/templates.pj
 */
