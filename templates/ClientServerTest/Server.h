#ifndef __SERVERSIDE_H__
#define __SERVERSIDE_H__

#include "./common.h"

class ServerListener;

namespace tt_stream_ns {
    class VIAmSession;
};

class Server {
public:
	Server();
    ~Server();

	void Start();

	void Menu();
    
    static Server& Instance();
private:
    void OnData(VIAmSession*pSess, VIAmSender* sender_,Streamable& obj_);
private:
    static void *threadmain(void *pArg);
    ServerListener *m_pServerListener;
    tt_stream_ns::VIAmSession *m_pLocalSession;
    bool m_bProcessEventsRunning;
    SYSThreadContext m_MgrThreadCtx;
    friend class ServerListener;
};

#endif // __SERVERSIDE_H__
