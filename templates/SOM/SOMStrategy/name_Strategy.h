#ifndef @(STRATNAME)_STRATEGY_H
#define @(STRATNAME)_STRATEGY_H

#include "ssapi/inc/Strategy.h"
#include "SOMStrategyLib/inc/SOMStrategy.h"
#include <vector>

class $(STRATNAME)Strategy : public SOMStrategy
{
public:
    $(STRATNAME)Strategy(const std::string& sName, const StrategyConfig& rStrategyConfig);
	virtual ~$(STRATNAME)Strategy();

private:
    int m_configIdx;
    int m_loggerIdx;

    StrategyHandle m_hConfig;
    StrategyHandle m_hLogger;
    StrategyHandle m_hPrice;
    StrategyHandle m_hTimer;

	// Handle incoming events
	virtual void SOMHandleRequestEvent(SSEventHandle& hEvent);
    virtual void SOMHandleResponseEvent(SSEventHandle& hEvent);
    virtual void SOMHandleNotifyEvent(SSEventHandle& hEvent);
    virtual void SOMHandleSystemEvent(SSEventHandle& hEvent);

    virtual void HandleNativeFill(GeneralFillHandle& fill);
    virtual void HandleNativeOrderStatus(GeneralOrderStatus& status);

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

