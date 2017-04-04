#ifndef __SERVERSIDE_H__
#define __SERVERSIDE_H__

#include "%(INTERFACENAME)/server/%(INTERFACENAME)serverinterface.h"

// Receive guardserv status requests through this listener
class LSLocalSrvSts: public tt_stream_ns::VIAmCallback
{
public:
    LSLocalSrvSts(tt_stream_ns::VIAmSession& sess_)
    {
        m_pLstnr=auto_ptr<tt_stream_ns::VIAmListener>(sess_.createListener(
            CoreMessaging::LOCAL_SRV_STS_SUBJ,*this));
    }
protected:
/*virtual*/ void OnData(tt_stream_ns::VIAmSession*, 
	                    const tt_stream_ns::VIAmSubject& incomingSubj_,
						tt_stream_ns::VIAmSender* sender_, 
                        tt_stream_ns::Streamable& obj_,
						tt_stream_ns::VIAmListener*);
private:
    auto_ptr<tt_stream_ns::VIAmListener> m_pLstnr;
};

class $(INTERFACENAME)ServerInterfaceImpl : public tt_%(INTERFACENAME)_ns::$(INTERFACENAME)ServerInterface {
public:
	
};

class Server {
public:
	Server();
    ~Server();

	void Start();

	void Menu();
    int Prompt(bool bPrompt);

    static HANDLE m_cnd;

	$(INTERFACENAME)ServerInterfaceImpl *m_pInterface;
    LSLocalSrvSts *m_pStatus;
};

#endif // __SERVERSIDE_H__
