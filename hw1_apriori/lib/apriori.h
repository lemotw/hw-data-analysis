#ifndef _APRIORI_H
#define _APRIORI_H

#include "freqitem_reader.h"
#include <unordered_map>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

struct vector_hash
{
	template <class T>
	std::size_t operator() (const std::vector<T> &v) const
	{
        int sum = 0;
        for(auto it=v.begin(); it!=v.end() ;++it)
            sum += *it;
        return sum;
	}
};

class Apriori {

    public:
        Apriori(int support, const char* filename):support(support), reader(filename), lsize_count(0) {
        }

        ~Apriori() {
        }

        int size();
        void generateC2();

        void scan(int);
        void filiter();
        void filiterAndCombine();
        
        unsigned int lsize_count;
        unsigned int round1_candidate_count;
        unsigned int per_round_lcount;
        unsigned int per_round_candidate_count;
        std::unordered_map<std::vector<int>, std::unordered_map<int, int>, vector_hash> table;

    private:
        int support;
        FreqItemReader reader;
};



#endif