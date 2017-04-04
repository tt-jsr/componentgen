Client/Server test.

This application allowes the user to start a "client" and a "server" for testing purposes.

The client and server both have a listener started to receive messages. common.h defines the subjects used by each.

Each side also has a menu that can be implemented for testing.


ClientMenu.cpp contains the menu for the client side, ServerMenu.cpp contains the server side menu.

ClientOnData.cpp and ServerOnData.cpp contain the OnData() callbacks for the client and server inbound messages.
