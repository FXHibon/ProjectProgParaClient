#include "ServerChoiceState.hpp"

using namespace std;

void ServerChoiceState::handle(Client client) {
    string serverIp = "127.0.0.1";
    int serverPort = 3000;

    string ipTmp;
    string portTmp;
    cout << endl << "Server IP (127.0.0.1 default):";
    getline(cin, ipTmp);

    cout << endl << "Server port (3000 default):";
    getline(cin, portTmp);
    cout << endl;

    if (!ipTmp.empty()) {
        serverIp = ipTmp;
    }

    if (!portTmp.empty()) {
        /**
        * Converting input string into int
        */
        istringstream stream(portTmp);
        stream >> serverPort;
    }

    client->setPort(serverPort);
    client->setAddress(serverIp);

    client->setCurrentState(new ConnectionState());
}