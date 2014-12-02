#include <iostream>
#include "Client.cpp"

using namespace std;

int main() {
    Client client = Client("127.0.0.1", 3000);
    client.connectClient();
    cout << "connected" << endl;
    int i = 1;
    while (i != 0) {
        cout << "0 pour quitter" << endl;
        cin >> i;
    }
    client.close();
    return 0;
}