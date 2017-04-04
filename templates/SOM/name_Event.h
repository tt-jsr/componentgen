#ifndef @(EVENTNAME)_EVENT_H
#define @(EVENTNAME)_EVENT_H

#include "ssapi/inc/SSEvent.h"
#include "include_your_ids.h"
#include "ssapi/inc/EventDefinition.h"
#include "ssapi/inc/EventFields.h"
#include <iostream>

// -- CUT HERE -- 
//!TODO: add this line to the strategy's GetNewSSEvent() method in factories.cpp
case SS_TYPE_@(EVENTNAME)_EVENT:  return new $(EVENTNAME)Event();

//!TODO: Add this to GetEventCatalog() in factories.cpp
eventCatalog.push_back( new $(EVENTNAME)Event() );

//!TODO: Add this to the event id's header file
#define EVENT_NAME_@(EVENTNAME)         "$(EVENTNAME)Event"
#define SSTYPE_@(EVENTNAME)             SSTYPE_TT_0 // adjust as neccessary


// -- CUTE HERE -- 

class $(EVENTNAME)Event : public SSEvent
{
public:
	$(EVENTNAME)Event()
        :SSEvent(SSTYPE_@(EVENTNAME)_EVENT, StrategyHandle(0), SSEvent::REQUEST)
	{
	}

	$(EVENTNAME)Event(StrategyHandle& hOriginatingStrat, unsigned int iUserData=0)
		:SSEvent(SSTYPE_@(EVENTNAME)_EVENT, hOriginatingStrat, SSEvent::REQUEST, iUserData)
	{
	}

	virtual ~$(EVENTNAME)Event() 
	{
	}


public:
	// Implement the SSEvent interface
	virtual const char* GetEventName(void) const 
	{
		return EVENT_NAME_@(EVENTNAME); 
	}
	
	virtual bool InitializeEventDefinitionObject(EventMarshaller::EventDefinition& eventDefn) const  
	{
		//eventDefn.AddField( id, "field_name", EventMarshaller::FIELD_TYPE_U64 );
		return true;
	}

	virtual bool EventToFields(EventMarshaller::EventFields& fields) const 
	{
		//fields.AddU64(id, m_member);
		return true;
	}

private:
	virtual bool FieldToEvent(const EventMarshaller::FIELD_VALUE& value)
	{
		switch ( value.GetFieldID() )
		{
		//case id:		m_member = ((EventMarshaller::FIELD_VALUE_U64&)value).GetValue();			return true;
		default:	return false;
		}
	}

private:
	

};

#endif	// #ifndef @(EVENTNAME)_EVENT_H

