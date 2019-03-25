#include <QCoreApplication>
#include "feistel.h"

using namespace std;

int main()
{
    const int nSteps = 12;
    while(1){
        const auto key = Feistel::randomKey64();
        const auto IV = Feistel::randomKey64();
        string msg;
        cin >> msg;

        const string msgF = Feistel::code64(msg, key, nSteps);
        cout << "Encoded: " << msgF << endl;

        const string msgB = Feistel::decode64(msgF, key, nSteps);
        cout << "Decoded: " << msgB << endl;

        const string msgF_cbc = Feistel::code64CBC(msg, key, nSteps, IV);
        cout << "Encoded CBC: " << msgF_cbc << endl;

        const string msgB_cbc = Feistel::decode64CBC(msgF_cbc, key, nSteps, IV);
        cout << "Decoded CBC: " << msgB_cbc << endl;

        const string msgF_cbf = Feistel::code64CFB(msg, key, nSteps, IV);
        cout << "Encoded CFB: " << msgF_cbf << endl;

        const string msgB_cbf = Feistel::decode64CFB(msgF_cbf, key, nSteps, IV);
        cout << "Decoded CFB: " << msgB_cbf << endl;
    }
    return 0;
}
