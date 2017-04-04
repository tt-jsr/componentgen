/*************************************************************************** 
* 
*                   Unpublished Work Copyright (c) 2005 
*                 Trading Technologies International, Inc. 
*                     All Rights Reserved Worldwide *
*            * * * S T R I C T L Y  P R O P R I E T A R Y * * * 
*
* WARNING: This program (or document) is unpublished, proprietary property 
* of Trading Technologies International, Inc. and is to be maintained in 
* strict confidence. Unauthorized reproduction, distribution or disclosure 
* of this program (or document), or any program (or document) derived from 
* it is prohibited by State and Federal law, and by local law outside of 
* the U.S. 
* ***************************************************************************/

#ifndef __CLIENTSIDE_H__
#define __CLIENTSIDE_H__

#include "./common.h"

namespace tt_stream_ns {
    class VIAmSession;
};
class ClientListener;

class Client {
public:
	Client();
    ~Client();

	void Start();

	void Menu();

    static Client& Instance();
private:
    void OnData(VIAmSession*pSess, VIAmSender* sender_,Streamable& obj_);
private:
    static void *Client::threadmain(void *pArg);
    ClientListener *m_pClientListener;
    tt_stream_ns::VIAmSession *m_pRemoteSession;
    bool m_bProcessEventsRunning;
    SYSThreadContext m_MgrThreadCtx;
    friend class ClientListener;
};

#endif //__CLIENTSIDE_H__

