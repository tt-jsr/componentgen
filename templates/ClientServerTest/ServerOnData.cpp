#include "stdafx.h"
#include "Server.h"

/** Implement the server's inbound messages here */
void Server::OnData(VIAmSession*pSess,
						VIAmSender* sender_, 
                        Streamable& obj_)
{
    switch (obj_.Id().GetCode())
	{	
    
    }
}
