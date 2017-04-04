// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once


#include <iostream>
#include <tchar.h>

// TODO: reference additional headers your program requires here
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
