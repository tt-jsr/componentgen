#include "stdafx.h"
#include "Server.h"

/** Implement the server's menu here */
void Server::Menu()
{
    char buf[64];
    buf[0] = '\0';

    while (buf[0] != 'q') {
        Sleep(1000);
        // Add other menu options here
        cout << endl;
        cout << "q.    Quit" << endl << endl;
        cout << "Enter=> ";
        gets(buf);
        switch (buf[0]) {
        case 'q':
        case 'Q':
            buf[0] = 'q';
            break;
        }
    }
}