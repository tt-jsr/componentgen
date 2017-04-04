#include "stdafx.h"
#include "Client.h"

/* Implement the client's menu here */
void Client::Menu()
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