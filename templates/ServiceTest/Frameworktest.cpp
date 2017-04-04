// $(INTERFACENAME)Sim.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "ServerSide.h"
#include "ClientSide.h"
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
            TT::Context corecontext("$(INTERFACENAME)SimClient");  // finalizes on leaving scope
	        SysNameServerProcess("TT", "$(INTERFACENAME)SimClient");
			SysInitDatedInfoLogFile("$(INTERFACENAME)SimClient");
			Client client;
			client.Start();
			break;
		}
	case 's':
		{
            TT::Context corecontext("$(INTERFACENAME)SimServer");  // finalizes on leaving scope
	        SysNameServerProcess("TT", "$(INTERFACENAME)SimServer");
			SysInitDatedInfoLogFile("$(INTERFACENAME)SimServer");
			Server server;
			server.Start();
			break;
		}
	case 'q':
		break;
	}
	return 0;
}
