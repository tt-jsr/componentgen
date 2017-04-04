//! TODO: Place this code into factories.cpp

// -------------------------------------------------------------------------------
$(STRATNAME)StrategyFactory::$(STRATNAME)StrategyFactory()
	:StrategyFactory(STRATEGY_NAME_@(STRATNAME)_STRATEGY)
{}

$(STRATNAME)StrategyFactory::~$(STRATNAME)StrategyFactory()
{}

Strategy* $(STRATNAME)StrategyFactory::GetNewStrategy(const std::string& sAlias,
														const StrategyConfig& rStrategyConfig)
{ return new $(STRATNAME)Strategy(sAlias, rStrategyConfig); }

SSEventFactory* $(STRATNAME)StrategyFactory::GetNewSSEventFactory(void)
{ return new $(STRATNAME)EventFactory(); }

// -------------------------------------------------------------------------------

$(STRATNAME)EventFactory::$(STRATNAME)EventFactory()
	:SSEventFactory(STRATEGY_NAME_@(STRATNAME)_STRATEGY)
{}

$(STRATNAME)EventFactory::~$(STRATNAME)EventFactory()
{}

SSEvent* $(STRATNAME)EventFactory::GetNewSSEvent(unsigned int iEventID)
{
	switch ( iEventID )
	{
	//case SSTYPE_@(STRATNAME)_SOMEEVENT:		return new $(STRATNAME)SomeEvent();
	default:							return 0;
	}
}

void $(STRATNAME)EventFactory::GetEventCatalog(std::list<SSEvent*>& eventCatalog)
{
	//eventCatalog.push_back( new $(STRATNAME)SomeEvent() );
}
