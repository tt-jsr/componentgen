#ifndef @(STRATNAME)_STRATEGY_H
#define @(STRATNAME)_STRATEGY_H

#include "ssapi/inc/Strategy.h"
#include <vector>

class $(STRATNAME)Strategy : public Strategy
{
public:
    $(STRATNAME)Strategy(const std::string& sName, const StrategyConfig& rStrategyConfig);
	virtual ~$(STRATNAME)Strategy();

private:
    int m_configIdx;
    int m_loggerIdx;

    StrategyHandle m_hConfig;
    StrategyHandle m_hLogger;

	// Handle incoming events
	virtual void HandleRequestEvent(unsigned long iThreadID, SSEventHandle& hEvent);
    virtual void HandleResponseEvent(unsigned long iThreadID, SSEventHandle& hEvent);
    virtual void HandleNotifyEvent(unsigned long iThreadID, SSEventHandle& hEvent);
    virtual void HandleSystemEvent(unsigned long iThreadID, SSEventHandle& hEvent);

    void HandleStrategyShutdown(SSEventHandle& hEvent);
    void HandleStrategyStartup(SSEventHandle& hEvent);
    void HandleGetInfoRsp(SSEventHandle& hEvent);
    void HandleLogfileOpenRsp(SSEventHandle& hEvent);
    void HandleConfigOpenRsp(SSEventHandle& hEvent);

    void log(stringstream&);
    void log(const char *);
private:
    void OpenLogfile();
    void OpenConfig();
};

#endif	// #ifndef @(STRATNAME)_STRATEGY_H

