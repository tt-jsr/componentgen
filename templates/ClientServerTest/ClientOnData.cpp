#include "stdafx.h"
#include "Client.h"

/** Implement the client's inbound messages here */
void Client::OnData(VIAmSession*pSess,
						VIAmSender* sender_, 
                        Streamable& obj_)
{
    switch (obj_.Id().GetCode())
	{	
    
    }
}
