/*************************************************************************** 
* 
*                   Unpublished Work Copyright (c) 2005 
*                 Trading Technologies International, Inc. 
*                     All Rights Reserved Worldwide *
*            * * * S T R I C T L Y  P R O P R I E T A R Y * * * 
*
* WARNING: This program (or document) is unpublished, proprietary property 
* of Trading Technologies International, Inc. and is to be maintained in 
* strict confidence. Unauthorized reproduction, distribution or disclosure 
* of this program (or document), or any program (or document) derived from 
* it is prohibited by State and Federal law, and by local law outside of 
* the U.S. 
* ***************************************************************************/


#include <stdafx.h>
#include <iostream>
#include "Server.h"
#include "Client.h"
#include "coreutils/Process.h"

using namespace tt_core_ns;
using namespace tt_coreutils_ns;
using namespace std;

char csmenu()
{
	char buf[64];
	buf[0] = '\0';
	while (true)
	{
		cout << "c.    Client" << endl;
		cout << "s.    Server" << endl;
		cout << "q.    Quit" << endl << endl;
		cout << "Enter=> ";
		cin >> buf;
		switch (buf[0])
		{
		case 'c':
		case 'C':
			return 'c';
			break;
		case 's':
		case 'S':
			return 's';
			break;
		case 'q':
		case 'Q':
			return 'q';
			break;
		}
	}
}

int _tmain(int argc, _TCHAR* argv[])
{
	switch (csmenu())
	{
	case 'c':
		{
            TT::Context corecontext("$(name)Client");  // finalizes on leaving scope
	        SysNameServerProcess("TT", "$(name)Client");
			SysInitDatedInfoLogFile("$(name)Client");
            Client::Instance().Start();
			break;
		}
	case 's':
		{
            TT::Context corecontext("$(name)Server");  // finalizes on leaving scope
	        SysNameServerProcess("TT", "$(name)Server");
			SysInitDatedInfoLogFile("$(name)Server");
            Server::Instance().Start();
			break;
		}
	case 'q':
		break;
	}
	return 0;
}


