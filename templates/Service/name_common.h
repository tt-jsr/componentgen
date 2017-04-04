/**************************************************************************
 *    
 *  Copyright (c) 2006  Trading Technologies International  
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
 * $Source: Common/Payload.h $ 
 * $Date: 2005/12/20 13:33:26CST $ 
 * $Author: jrichards $ 
 * $Revision: 1.24.4.2.1.4 $    
 ***************************************************************************/
#ifndef __@(INTERFACENAME)_COMMON__H
#define __@(INTERFACENAME)_COMMON__H

namespace tt_%(INTERFACENAME)_ns {

// TODO: Uncomment if encryption must be available to become active.
//#define @(INTERFACENAME)_ENCRYPTION_ENABLED

    // These are the default subject for broadcasting to clients and servers
    static const char *@(INTERFACENAME)_SERVER_SUBJ = "TTVIA.@(INTERFACENAME)_SERVER";
    static const char *@(INTERFACENAME)_CLIENT_SUBJ = "TTVIA.@(INTERFACENAME)_CLIENT";

    // If this service requires heartbeating from the server, define this to be the
    // service ID to listen for heartbeats
    static const int @(INTERFACENAME)_SERVICE_HEARTBEAT = 0;

#pragma message( "Must define $(INTERFACENAME)Announce_cc" )
    static const int $(INTERFACENAME)Announce_cc = 0;

    class $(INTERFACENAME)Announce : public CoreClass {
    public:
        $(INTERFACENAME)Announce();
        enum ActionCode {
            ANNOUNCE,
            DISCOVER,
            SHUTDOWN,
            PING
        };
        ActionCode action;

        tt_stream_ns::Stream& Transfer(tt_stream_ns::Stream& s_, Direction dir_);
        tt_stream_ns::VerClsId Id() const;
    };
} // namespace tt_%(INTERFACENAME)_ns

#endif // __@(INTERFACENAME)_COMMON__H
/*
  $Log:  $
 */
