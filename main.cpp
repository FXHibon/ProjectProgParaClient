#include <iostream>
#include "Client.cpp"

using namespace std;

int main() {
    Client client = Client("127.0.0.1", 3000);
    client.connectClient();
    cout << "connected" << endl;
    string i = "";
    char buffer[10];
    while (i != "exit") {
        client.sendMessage(i);
        cin >> i;
    }
    client.sendMessage("exit");
    client.close();
    return 0;
}