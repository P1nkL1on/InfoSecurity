#include <QCoreApplication>
#include "iostream"
#include "unordered_set"
#include "vector"

using namespace std;



int nextU (const int U, const int M, const int C, const int p){
    return ( U * M + C) % p;
}

int exprimentCoutn (const double delta){
    const double val = .98 / delta;
    return int(val * val);
}

double mean(const unordered_set<double> &set){
    double summ = 0;
    for (double v : set)
        summ += v;
    return summ / set.size();
}

double disp(const unordered_set<double> &set){
    const double m = mean(set);
    double res = 0;
    for (double v : set)
        res += pow(v - m, 2.0);
    return res / set.size();
}

double chiSquare(const unordered_set<double> &set, const int nBins){
    vector<int> bins(nBins);
    double res;
    double expected = double(set.size()) / nBins;
    for (double v : set)
        bins[int(v * nBins)]++;

    for (int observed : bins)
        res += std::pow(observed - expected, 2);

    cout<< endl;//expected << endl;
    return double(res) / expected;
}

unordered_set<double> values;

void generateRandomNumbers(const int U0, const int M, const int C, const int p,
                           int &resSize, double &mmean, double &mdispers, double &chiquad
                           ){
    values.clear();

    int U = U0;//, generateRowMaximumSize = 100;

    while(1){
        U = nextU(U, M, C, p);
        const double generatedValue = U * 1.0 / p;
        // trace new randomed values
        //if was none insert it to set
        if (values.find(generatedValue) != values.end())
            break;
        values.insert(generatedValue);
        // cout << generatedValue << endl;
    }
    // count any params of generation
    //    cout << endl << "Size: " << values.size()  << "    / (p = " << p << ")" << endl
    //                 << "Mean: " << mean(values) <<  endl
    //                 << "Dispers: " << disp(values) << endl
    //                 << "Heesquare: " << chiSquare(values, 100) << endl;
    resSize = values.size();
    mmean = mean(values);
    mdispers = disp(values);
    chiquad = chiSquare(values, 100);
}


vector<int> getSimple(const int size){
    vector<int> res(size);
    int need = 0;
    int nowNumber = 0;

    while (need < size){
        nowNumber++;
        // is accepted
        bool isSimple = true;
        for (int del = 2; del < nowNumber - 1; ++del)
            if (nowNumber % del == 0)
            {isSimple = false; break;}
        if (isSimple){
            res[need] = nowNumber;
            ++need;
        }
    }

    return res;
}

int main(int argc, char *argv[])
{
    //    QCoreApplication a(argc, argv);
    //    return a.exec();
    vector<int> params(4);
    vector<int> bestParams(4);
    params[0] = 13; // U0
    params[1] = 512447; // M
    params[2] = 0;  // C
    params[3] = 1017; // p

    int bestSize = 0, currentSize;
    const int minParam = 10;
    const int maxParam = 100;

    const int total = pow(maxParam, 3);
    int done = 0;
    const auto simples = getSimple(maxParam);

//    for (int Mi = minParam; Mi < maxParam; ++Mi)
//        //for (int Ci = minParam; Ci < maxParam; ++Ci)
//        for (int pi = 10000; pi < 11000; ++pi)
//            for (int U0i = minParam; U0i < maxParam; ++U0i){
//                params = {simples[U0i], simples[Mi], /*Ci*/ 0, pi};
//                generateRandomNumbers(params[0], params[1], params[2], params[3], currentSize);
//                if (currentSize > bestSize){
//                    bestSize = currentSize;
//                    bestParams = params;
//                    cout << bestSize << "!!   " << bestParams[0]  << ", " << bestParams[1] << ", " << bestParams[2] << ", " << bestParams[3] << endl;
//                }
//                else
//                    if (!(done % 10000))
//                        cout << std::round(1000000 * double(done)/total) * .01 << "%   " << done << endl;
//                ++done;
//            }
    int s;
    double m, d, ch;
    for (int mi = 5; mi < maxParam; ++mi)
        for (int pi = 5; pi < maxParam; ++pi)
        {

            for (int u0i = 10; u0i < 200; ++u0i){
                params = {u0i, simples[mi], /*Ci*/ 0, simples[pi]};
                generateRandomNumbers(params[0], params[1], params[2], params[3], s, m, d, ch);
                cout << params[0]  << ", " << params[1] << ", " << params[2] << ", " << params[3]
                     << "  Size: " << s << "  Mean: " << m << "  Dispers: " << d << "  Chi quad: " << ch << endl;
            }
            char x;
            cin >> x;
        }

    //    cout << bestSize << "!!   " << bestParams[0]  << ", " << bestParams[1] << ", " << bestParams[2] << ", " << bestParams[3] << endl;
    return 0;
}
