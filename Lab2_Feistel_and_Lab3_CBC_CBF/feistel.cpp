#include "feistel.h"
#include <vector>
#include <ctime>
#include <cstdlib>
using namespace std;



void Feistel::test()
{

    //    cout << sizeof(unsigned long long) * 8 << endl;
    //    cout << sizeof(unsigned int) * 8 << endl;
    string msg;
    cin >> msg;

    cout << "Msg: " << msg << endl;
    const int
            charinlonglong = sizeof(long long) / sizeof(char),
            l = msg.length(),
            l2 = !(l % charinlonglong)? l : ((l/charinlonglong+1) * charinlonglong);

    string incomeMessage = msg;
    for (int i = l; i < l2; ++i)
        incomeMessage += '\0';

    unsigned long long blocks[l2/ charinlonglong];

    for (int i = 0; i < l2/ charinlonglong; ++i){
        unsigned long long block = 0;
        for (int j = 0; j < charinlonglong - 1; ++j){
            block += incomeMessage[i * charinlonglong + j];
            block = block << charinlonglong;
        }
        blocks[i] = block + incomeMessage[(i+1) * charinlonglong - 1];
    }

    //    const unsigned short nRounds = 10;
    const unsigned long long key0 = randomKey64();
    //cout << "key0: "; trace(key0);

    //cout << "Byte buffer: " << endl;


    const int nRounds = 10;
    unsigned long long resultBlocks[l2/ charinlonglong];
    int resultIndex = 0;

    const int sizeblock = sizeof(unsigned long long) * 8;
    const int halfblock = sizeblock / 2;

    for (unsigned long long c : blocks){
        cout << "LR:\t";
        trace<unsigned long long>(c);
        unsigned int left = 0;
        unsigned int right = 0;

        left = c >> halfblock;
        right = c;

        cout << endl; trace(left);
        trace(right);
        for (int iteration = 0; iteration < nRounds; ++iteration){
            //            cout << "==== iteration " << iteration << endl;
            //            cout << "L:\t " ;
            //            trace<int>(left);
            //            cout << "R:\t " ;
            //            trace<int>(right);

            //            cout << endl << "L -> F(K0): ";
            //            unsigned int funcd = F(left, nextKey(key0, iteration));
            //            trace(funcd);

            const unsigned int lefttmp = left;
            left = F(left, nextKey(key0, iteration)) ^ right;
            right = lefttmp;

            //            cout << endl;
        }
        unsigned long long newC = (right << halfblock) + left;
        cout << "new c: "; trace(newC);
        resultBlocks[resultIndex++] = newC;
    }

    string res = "";
    for (int i = 0; i < l2/ charinlonglong; ++i){
        unsigned long long block = resultBlocks[i];
        for (int j = charinlonglong - 1; j >= 0 ; --j)
            res += char(block >> 8 * j);
    }
    cout << endl << endl << res << endl;
}

unsigned char Feistel::F8(const unsigned char L, const unsigned char key)
{
    unsigned char res = leftShift(L, 9) | (~(rightShift(key, 11) & L));
    res = res << 4;
    return res >> 4;
}

unsigned int Feistel::F(const unsigned int L, const unsigned int key)
{
    return leftShift(L, 9) | (~(rightShift(key, 11) & L));
}

unsigned long long Feistel::nextKey(const unsigned long long key0, const int iteration)
{
    return rightShift(key0, iteration * 8);
}

unsigned long long Feistel::randomKey64()
{
    //srand(time(0));
    long long res;
    for (int i = 0; i <= 10; ++i){
        res = res << 8;
        res |= rand();
    }
    return res;
}

string Feistel::code8(const string &message, const long long key0, const int nSteps)
{
    unsigned char incomeBytesBuffer[message.length()];
    copy(message.begin(), message.end(), incomeBytesBuffer);

    string finalMsg = "";
    for (unsigned char c : incomeBytesBuffer){
        unsigned char left = 0;
        unsigned char right = 0;

        left = c >> 4;
        right = c << 4;
        right = right >> 4;
        for (int iteration = 0; iteration < nSteps; ++iteration){
            const unsigned char lefttmp = left;
            left = F8(left, nextKey(key0, iteration)) ^ right;
            right = lefttmp;
        }
        unsigned char newC = (right << 4) + left;
        finalMsg += newC;
    }
    return finalMsg;
}

string Feistel::decode8(const string &cryptedMessage, const long long key0, const int nSteps)
{
    unsigned char incomeBytesBuffer[cryptedMessage.length()];
    copy(cryptedMessage.begin(), cryptedMessage.end(), incomeBytesBuffer);

    string finalMsg = "";
    for (unsigned char c : incomeBytesBuffer){
        unsigned char left = 0;
        unsigned char right = 0;

        left = c >> 4;
        right = c << 4;
        right = right >> 4;
        for (int iteration = 0; iteration < nSteps; ++iteration){
            const unsigned char lefttmp = left;
            left = F8(left, nextKey(key0, nSteps - 1 - iteration)) ^ right;
            right = lefttmp;
        }
        unsigned char newC = (right << 4) + left;
        finalMsg += newC;
    }
    return finalMsg;
}


string Feistel::code64(const string &message, const long long key0, const int nSteps)
{
    const int
            charinlonglong = sizeof(long long) / sizeof(char),
            l = message.length(),
            l2 = !(l % charinlonglong)? l : ((l/charinlonglong+1) * charinlonglong);

    string incomeMessage = message;
    for (int i = l; i < l2; ++i)
        incomeMessage += '\0';

    unsigned long long blocks[l2/ charinlonglong];

    for (int i = 0; i < l2/ charinlonglong; ++i){
        unsigned long long block = 0;
        for (int j = 0; j < charinlonglong - 1; ++j){
            block += (unsigned char)incomeMessage[i * charinlonglong + j];
            block = block << charinlonglong;
        }
        blocks[i] = block + (unsigned char)incomeMessage[(i+1) * charinlonglong - 1];
    }

    unsigned long long resultBlocks[l2/ charinlonglong];
    int resultIndex = 0;

    const int sizeblock = sizeof(unsigned long long) * 8;
    const int halfblock = sizeblock / 2;

    for (unsigned long long c : blocks){
        unsigned int left = 0;
        unsigned int right = 0;

        left = c >> halfblock;
        right = c;

//        cout << "block0:  "; trace(c);
//        cout << "   L0:  "; trace(left);
//        cout << "   R0:  "; trace(right);

        for (int iteration = 0; iteration < nSteps; ++iteration){
            const unsigned int lefttmp = left;
            left = F(left, nextKey(key0, iteration)) ^ right;
            right = lefttmp;
//            cout << "   L" << iteration << ":  "; trace(left);
//            cout << "   R" << iteration << ":  "; trace(right);
        }
        unsigned long long newC = ((unsigned long long)(right) << halfblock) + left;
//        cout << "block res:  "; trace(newC);
        resultBlocks[resultIndex++] = newC;
    }

    string res = "";
    for (int i = 0; i < l2/ charinlonglong; ++i){
        unsigned long long block = resultBlocks[i];
        for (int j = charinlonglong - 1; j >= 0 ; --j){
//            trace((unsigned char)(block >> (8 * j)));
            res += (unsigned char)(block >> (8 * j));
        }
    }
    return res;
}

string Feistel::decode64(const string &message, const long long key0, const int nSteps)
{
    const int
            charinlonglong = sizeof(long long) / sizeof(char),
            l = message.length(),
            l2 = !(l % charinlonglong)? l : ((l/charinlonglong+1) * charinlonglong);

    string incomeMessage = message;
    for (int i = l; i < l2; ++i)
        incomeMessage += '\0';

    unsigned long long blocks[l2/ charinlonglong];

    for (int i = 0; i < l2/ charinlonglong; ++i){
        unsigned long long block = 0;
        for (int j = 0; j < charinlonglong - 1; ++j){
            block += (unsigned char)incomeMessage[i * charinlonglong + j];
            block = block << charinlonglong;
//            trace(incomeMessage[i * charinlonglong + j]);
        }
        blocks[i] = block + (unsigned char)incomeMessage[(i+1) * charinlonglong - 1];
    }

    unsigned long long resultBlocks[l2/ charinlonglong];
    int resultIndex = 0;

    const int sizeblock = sizeof(unsigned long long) * 8;
    const int halfblock = sizeblock / 2;

    for (unsigned long long c : blocks){
        unsigned int left = 0;
        unsigned int right = 0;

        left = c >> halfblock;
        right = c;

//        cout << "block0:  "; trace(c);
//        cout << "   L0:  "; trace(left);
//        cout << "   R0:  "; trace(right);

        for (int iteration = 0; iteration < nSteps; ++iteration){
            const unsigned int lefttmp = left;
            left = F(left, nextKey(key0, nSteps - 1 - iteration)) ^ right;
            right = lefttmp;
//            cout << "   L" << iteration << ":  "; trace(left);
//            cout << "   R" << iteration << ":  "; trace(right);
        }
        unsigned long long newC = ((unsigned long long)(right) << halfblock) + left;
//        cout << "block res:  "; trace(newC);
        resultBlocks[resultIndex++] = newC;
    }

    string res = "";
    for (int i = 0; i < l2/ charinlonglong; ++i){
        unsigned long long block = resultBlocks[i];
        for (int j = charinlonglong - 1; j >= 0 ; --j)
            res += char(block >> 8 * j);
    }
    return res;
}

string Feistel::code64CBC(const std::string &message, const long long key0, const int nSteps, const long long IV)
{
    const int
        charinlonglong = sizeof(long long) / sizeof(char),
        l = message.length(),
        l2 = !(l % charinlonglong)? l : ((l/charinlonglong+1) * charinlonglong);

    string incomeMessage = message;
    for (int i = l; i < l2; ++i)
        incomeMessage += '\0';

    unsigned long long blocks[l2/ charinlonglong];
    for (int i = 0; i < l2/ charinlonglong; ++i){
        unsigned long long block = 0;
        for (int j = 0; j < charinlonglong - 1; ++j){
            block += (unsigned char)incomeMessage[i * charinlonglong + j];
            block = block << charinlonglong;
        }
        blocks[i] = block + (unsigned char)incomeMessage[(i+1) * charinlonglong - 1];
    }

    unsigned long long resultBlocks[l2/ charinlonglong];
    int resultIndex = 0;

    const int sizeblock = sizeof(unsigned long long) * 8;
    const int halfblock = sizeblock / 2;

    int blockNumber = 0;
    for (unsigned long long c : blocks){
        ++blockNumber;
        unsigned int left = 0;
        unsigned int right = 0;

        left = c >> halfblock;
        right = c;

        // adding a previous blocking
//        trace(left);
//        trace(right);
        if (blockNumber == 1){
//            cout << "+ IV = "; trace(IV);
            left ^= (unsigned int)(IV >> halfblock);
            right ^= (unsigned int)IV;
        }else{
//            cout << "+ res = "; trace(resultBlocks[resultIndex-1]);
            left ^= (unsigned int)(resultBlocks[resultIndex-1] >> halfblock);
            right ^= (unsigned int)resultBlocks[resultIndex-1];
        }
//        trace(left);
//        trace(right);
//        cout << "___" << endl;
        // ==========================

        for (int iteration = 0; iteration < nSteps; ++iteration){
            const unsigned int lefttmp = left;
            left = F(left, nextKey(key0, iteration)) ^ right;
            right = lefttmp;
        }
        unsigned long long newC = ((unsigned long long)(right) << halfblock) + left;
        resultBlocks[resultIndex++] = newC;
    }

    string res = "";
    for (int i = 0; i < l2/ charinlonglong; ++i)
        for (int j = charinlonglong - 1; j >= 0 ; --j)
            res += (unsigned char)(resultBlocks[i] >> (8 * j));

    return res;
}

string Feistel::decode64CBC(const string &message, const long long key0, const int nSteps, const long long IV)
{
    const int
            charinlonglong = sizeof(long long) / sizeof(char),
            l = message.length(),
            l2 = !(l % charinlonglong)? l : ((l/charinlonglong+1) * charinlonglong);

    string incomeMessage = message;
    for (int i = l; i < l2; ++i)
        incomeMessage += '\0';

    unsigned long long blocks[l2/ charinlonglong];

    for (int i = 0; i < l2/ charinlonglong; ++i){
        unsigned long long block = 0;
        for (int j = 0; j < charinlonglong - 1; ++j){
            block += (unsigned char)incomeMessage[i * charinlonglong + j];
            block = block << charinlonglong;
        }
        blocks[i] = block + (unsigned char)incomeMessage[(i+1) * charinlonglong - 1];
    }

    unsigned long long resultBlocks[l2/ charinlonglong];
    int resultIndex = 0;

    const int sizeblock = sizeof(unsigned long long) * 8;
    const int halfblock = sizeblock / 2;

    int blockNumber = 0;
    for (unsigned long long c : blocks){
        ++blockNumber;
        unsigned int left = 0;
        unsigned int right = 0;

        left = c >> halfblock;
        right = c;

        for (int iteration = 0; iteration < nSteps; ++iteration){
            const unsigned int lefttmp = left;
            left = F(left, nextKey(key0, nSteps - 1 - iteration)) ^ right;
            right = lefttmp;
        }

        // new addition
//        trace(left);
//        trace(right);
        if (blockNumber == 1){
//            cout << "+ IV = "; trace(IV);
            right ^= (unsigned int)(IV >> halfblock);
            left ^= (unsigned int)IV;
        }else{
//            cout << "+ res = "; trace(blocks[resultIndex-1]);
            right ^= (unsigned int)(blocks[resultIndex-1] >> halfblock);
            left ^= (unsigned int)blocks[resultIndex-1];
        }
//        trace(left);
//        trace(right);
//        cout << "___" << endl;
        // ============

        unsigned long long newC = ((unsigned long long)(right) << halfblock) + left;
        resultBlocks[resultIndex++] = newC;
    }

    string res = "";
    for (int i = 0; i < l2/ charinlonglong; ++i){
        unsigned long long block = resultBlocks[i];
        for (int j = charinlonglong - 1; j >= 0 ; --j)
            res += char(block >> 8 * j);
    }
    return res;
}

string Feistel::code64CFB(const std::string &message, const long long key0, const int nSteps, const long long IV)
{
    const int
        charinlonglong = sizeof(long long) / sizeof(char),
        l = message.length(),
        l2 = !(l % charinlonglong)? l : ((l/charinlonglong+1) * charinlonglong);

    string incomeMessage = message;
    for (int i = l; i < l2; ++i)
        incomeMessage += '\0';

    unsigned long long blocks[l2/ charinlonglong];
    for (int i = 0; i < l2/ charinlonglong; ++i){
        unsigned long long block = 0;
        for (int j = 0; j < charinlonglong - 1; ++j){
            block += (unsigned char)incomeMessage[i * charinlonglong + j];
            block = block << charinlonglong;
        }
        blocks[i] = block + (unsigned char)incomeMessage[(i+1) * charinlonglong - 1];
    }

    unsigned long long resultBlocks[l2/ charinlonglong];
    int resultIndex = 0;

    const int sizeblock = sizeof(unsigned long long) * 8;
    const int halfblock = sizeblock / 2;

    int blockNumber = 0;
    for (unsigned long long c : blocks){
        const unsigned long long IVt = !blockNumber? IV : resultBlocks[blockNumber - 1];
//        cout << blockNumber << "->  "; trace(IVt);
        ++blockNumber;
        unsigned int left = 0;
        unsigned int right = 0;

        left = IVt >> halfblock;
        right = IVt;

        for (int iteration = 0; iteration < nSteps; ++iteration){
            const unsigned int lefttmp = left;
            left = F(left, nextKey(key0, iteration)) ^ right;
            right = lefttmp;
        }
        unsigned long long newIVt = ((unsigned long long)(right) << halfblock) + left;
        resultBlocks[resultIndex++] = newIVt ^ c;
    }

    string res = "";
    for (int i = 0; i < l2/ charinlonglong; ++i)
        for (int j = charinlonglong - 1; j >= 0 ; --j)
            res += (unsigned char)(resultBlocks[i] >> (8 * j));

    return res;
}

string Feistel::decode64CFB(const string &message, const long long key0, const int nSteps, const long long IV)
{
    const int
            charinlonglong = sizeof(long long) / sizeof(char),
            l = message.length(),
            l2 = !(l % charinlonglong)? l : ((l/charinlonglong+1) * charinlonglong);

    string incomeMessage = message;
    for (int i = l; i < l2; ++i)
        incomeMessage += '\0';

    unsigned long long blocks[l2/ charinlonglong];

    for (int i = 0; i < l2/ charinlonglong; ++i){
        unsigned long long block = 0;
        for (int j = 0; j < charinlonglong - 1; ++j){
            block += (unsigned char)incomeMessage[i * charinlonglong + j];
            block = block << charinlonglong;
        }
        blocks[i] = block + (unsigned char)incomeMessage[(i+1) * charinlonglong - 1];
    }

    unsigned long long resultBlocks[l2/ charinlonglong];
    int resultIndex = 0;

    const int sizeblock = sizeof(unsigned long long) * 8;
    const int halfblock = sizeblock / 2;

    int blockNumber = 0;
    for (unsigned long long c : blocks){
        const unsigned long long IVt = !blockNumber? IV : blocks[blockNumber - 1];
//        cout << blockNumber << "->  "; trace(IVt);

        ++blockNumber;
        unsigned int left = 0;
        unsigned int right = 0;

        left = IVt >> halfblock;
        right = IVt;

        for (int iteration = 0; iteration < nSteps; ++iteration){
            const unsigned int lefttmp = left;
            left = F(left, nextKey(key0, iteration)) ^ right;
            right = lefttmp;
        }

        unsigned long long newIVt = ((unsigned long long)(right) << halfblock) + left;
        resultBlocks[resultIndex++] = newIVt ^ c;
    }

    string res = "";
    for (int i = 0; i < l2/ charinlonglong; ++i){
        unsigned long long block = resultBlocks[i];
        for (int j = charinlonglong - 1; j >= 0 ; --j)
            res += char(block >> 8 * j);
    }
    return res;
}
