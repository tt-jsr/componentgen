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
 * $Source: Common/Payload.cpp $ 
 * $Date: 2005/12/09 14:00:43CST $ 
 * $Author: rtaylor $ 
 * $Revision: 1.23.3.5 $ 	
 ***************************************************************************/
#include <pch.h>
#include "Stream/Stream.h"
#include "coreutils/tt_assert.h"
#include "../%(INTERFACENAME)_common/%(INTERFACENAME)_common.h"
#include <time.h>

using namespace std;

namespace tt_%(INTERFACENAME)_ns {

/**************************************************************************/
TT_VIA_CLASS_DEF($(INTERFACENAME)Announce, $(INTERFACENAME)Announce_cc);

$(INTERFACENAME)Announce::$(INTERFACENAME)Announce()
:action(DISCOVER)
{

}

tt_stream_ns::Stream& $(INTERFACENAME)Announce::Transfer(tt_stream_ns::Stream& s_, Direction dir_)
{
	CoreClass::Transfer(s_,dir_);   // always call base first
	TT_XFER_BEGIN(s_, dir_);
	{
		TT_XFER_VAR(action);
	}
	TT_XFER_END;
	return s_;
}

} // namespace tt_%(INTERFACENAME)_ns

/*
 $Log: $
 
 */
