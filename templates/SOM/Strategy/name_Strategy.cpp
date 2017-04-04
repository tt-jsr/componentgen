#include "$(STRATNAME)Strategy.h"
#include "ssutils/inc/ConfigOpenEvent.h"
#include "ssutils/inc/ConfigGetInfoEvent.h"
#include "ssutils/inc/LoggerOpenEvent.h"
#include "ssutils/inc/LoggerLogEvent.h"
#include "ssapi/inc/StrategyArguments.h"
#include <sstream>

using namespace std;

enum {
    RQSTID_LOGFILE_OPEN = 1,
    RQSTID_CONFIG_OPEN,
    RQSTID_CONFIG_GETINFO,
};

$(STRATNAME)Strategy::$(STRATNAME)Strategy(const std::string& sName, 
											   const StrategyConfig& rStrategyConfig)
   :Strategy(sName, rStrategyConfig)
    , m_configIdx(0)
    , m_loggerIdx(0)
{
   	StrategyArguments args;
    args.Parse(this->GetArguments().c_str());
    // TODO: Parse any strategy arguments here
}

$(STRATNAME)Strategy::~$(STRATNAME)Strategy()
{
}

void $(STRATNAME)Strategy::HandleStrategyShutdown(SSEventHandle& hEvent)
{
    
}

void $(STRATNAME)Strategy::HandleStrategyStartup(SSEventHandle& hEvent)
{
    m_hLogger = GetStrategy(STRATEGY_NAME_LOGGER_STRATEGY);
    TTASSERT(m_hLogger);    
    m_hLogger->QueueEvent( SSEventHandle(new LoggerOpenEvent(GetThisHandle(), "StrategyEngine.log", 0, 1024, RQSTID_LOGFILE_OPEN)) );

    m_hConfig = GetStrategy(STRATEGY_NAME_CONFIG_STRATEGY);
    TTASSERT(m_hConfig);
}

/* Handle system events */
void $(STRATNAME)Strategy::HandleSystemEvent(unsigned long iThreadID, SSEventHandle& hEvent)
{
    switch(hEvent->GetEventType())
    {
    case SSTYPE_SYSSHUTDOWN:
        HandleStrategyShutdown(hEvent);
        break;
    case SSTYPE_SYSSTARTUP:
        HandleStrategyStartup(hEvent);
        break;
    }
}

/* Handle requests */
void $(STRATNAME)Strategy::HandleRequestEvent(unsigned long iThreadID, SSEventHandle& hEvent)
{
    // Look at the request
	switch ( hEvent->GetEventType() )
	{
	default:
		return;	// Unknown
	}
}

/* Handle response event here */
void $(STRATNAME)Strategy::HandleResponseEvent(unsigned long iThreadID, SSEventHandle& hEvent)
{
    switch (hEvent->GetUserData())
    {
    case RQSTID_LOGFILE_OPEN:
        HandleLogfileOpenRsp(hEvent);
        break;
    case RQSTID_CONFIG_OPEN:
        HandleConfigOpenRsp(hEvent);
        break;
    case RQSTID_CONFIG_GETINFO:
        HandleGetInfoRsp(hEvent);
        break;
    }
}

/* Handle notification events here */
void $(STRATNAME)Strategy::HandleNotifyEvent(unsigned long iThreadID, SSEventHandle& hEvent)
{
    return;
}

// A response to opening a logfile
void $(STRATNAME)Strategy::HandleLogfileOpenRsp(SSEventHandle& hEvent)
{
    if ( hEvent->GetResponseCode() == SSRESP_SUCCESS )
	{
		m_loggerIdx = ((LoggerOpenEvent*)hEvent.GetObj())->GetLoggerIndex();
        m_hConfig->QueueEvent(SSEventHandle(new ConfigOpenEvent(GetThisHandle(), "", RQSTID_CONFIG_OPEN)));        
	}
	return;
}

// A response to opening the config strategy
void $(STRATNAME)Strategy::HandleConfigOpenRsp(SSEventHandle& hEvent)
{
    if ( hEvent->GetResponseCode() == SSRESP_SUCCESS )
	{
		m_configIdx = ((ConfigOpenEvent*)hEvent.GetObj())->GetConfigIndex();
        // TODO: Get any configuration info here
        // m_hConfig->QueueEvent(SSEventHandle(new ConfigGetInfoEvent(GetThisHandle(), m_configIdx, place_your_data_key_here, RQSTID_CONFIG_GETINFO)));
	}
    else
    {
        log("Could not open default config file\n");
    }
	return;
}

// Handle a response to a config getinfo request
void $(STRATNAME)Strategy::HandleGetInfoRsp(SSEventHandle& hEvent)
{
    if ( hEvent->GetResponseCode() == SSRESP_SUCCESS )
    {
        ;
    }
    else
    {
        log("Unable to get list of strategies to load\n");
    }
    return;
}

// Log a message
void $(STRATNAME)Strategy::log(stringstream& strm)
{
    log(strm.str().c_str());
}

// Log a message
void $(STRATNAME)Strategy::log(const char *p)
{
    m_hLogger->QueueEvent( SSEventHandle(new LoggerLogEvent(m_loggerIdx, p, GetThisHandle())) );
}


