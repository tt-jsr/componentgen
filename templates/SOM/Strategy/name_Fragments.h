
//! TODO: Place these definition in the header file that defines id's
#define STRATEGY_NAME_@(STRATNAME)_STRATEGY         "$(STRATNAME)Strategy"


//!TODO: Place this in the CreatePluginCatalog() function
pCatalog->AddPlugIn(new $(STRATNAME)StrategyFactory() );



//!TODO: Place these in Factories.h
class $(STRATNAME)EventFactory : public SSEventFactory
{
public:
	$(STRATNAME)EventFactory();
	virtual ~$(STRATNAME)EventFactory();
	virtual SSEvent* GetNewSSEvent(unsigned int iEventID);
	virtual void GetEventCatalog(std::list<SSEvent*>& eventCatalog);
};

class $(STRATNAME)StrategyFactory : public StrategyFactory
{
public:
	$(STRATNAME)StrategyFactory();
	virtual ~$(STRATNAME)StrategyFactory();
	virtual Strategy* GetNewStrategy(const std::string& sAlias, 
				const StrategyConfig& rStrategyConfig);
	virtual SSEventFactory* GetNewSSEventFactory(void);
};

