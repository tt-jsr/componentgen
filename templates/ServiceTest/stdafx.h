/**************************************************************************
 *    
 *  Copyright (c) 2005  Trading Technologies International  
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
 * $Source: stdafx.h $ 
 * $Date: 2005/11/30 07:07:56CST $ 
 * $Author: rtaylor $ 
 * $Revision: 1.1.3.2 $ 	
 ***************************************************************************/
// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "afx.h"
#include "boost/regex.hpp"


#pragma warning( disable : 4786 )
#include <stdlib.h>
#pragma warning( disable : 4786 )
#include <yvals.h>
#pragma warning( disable : 4786 )
#pragma warning( disable : 4231 )

#include "common/CoreConfig.h"
#include "common/world.h"

#include "common/tt_globals.h"
#include "common/internal.h"

#include "common/CoreMessaging.h"

#include "coreutils/logging.h"
#include "coreutils/network.h"
#include "coreutils/thread.h"
#include "coreutils/ttprocessnt.h"
#include "coreutils/system.h"

#include "stream/VIAMessaging.h"
#include "coreutils/TTCriticalSection.h"


/*
  $Log: stdafx.h  $
  Revision 1.1.3.2 2005/11/30 07:07:56CST rtaylor 
  
  Revision 1.1.3.1 2005/05/18 07:51:12CDT rtaylor 
  Duplicate revision
  Revision 1.1 2005/05/16 09:57:48CDT jrichards 
  Initial revision
  Member added to project /SAN/mks-si/data1/projectsource/core/api/main/dev/coreframework/templates/templates.pj
 */
