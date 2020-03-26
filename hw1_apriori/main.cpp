#include <iostream>
#include <string>

#include <chrono> 
#include "apriori.h"

using namespace std;
using namespace std::chrono;

int main(void) {
    int support = 0;
    string filepath;

    cout << "請輸入 support: ";
    cin >> support;
    cout << "請輸入測資檔案位置: ";
    cin >> filepath;

    Apriori apriori(support, filepath.c_str());

    auto start = high_resolution_clock::now();
    apriori.generateC2();
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<microseconds>(stop - start); 
    cout << "C2 產生所花費時間: " << (double)(duration.count()/1000000.0) << "秒" << endl;
    cout << "C2: C size: " << apriori.round1_candidate_count << " L size:" << apriori.per_round_lcount << endl;
    cout << "-----------------------------------------------" << endl;

    while(apriori.size() != 0) {
        start = high_resolution_clock::now();
        apriori.scan(2);
        apriori.filiterAndCombine();
        stop = high_resolution_clock::now();
        duration = duration_cast<microseconds>(stop - start); 
        cout << "這一回合所花費時間: " << (double)(duration.count()/1000000.0) << "秒" << endl;
        cout << "this round: C size: " << apriori.per_round_candidate_count << " L size:" << apriori.per_round_lcount << endl;

        cout << "-----------------------------------------------" << endl;
    }

    return 0;
}