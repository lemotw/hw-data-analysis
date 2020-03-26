#include "apriori.h"

void Apriori::filiterAndCombine() {
    // filiter and count lsize
    this->filiter();
    this->lsize_count += this->per_round_lcount;
    // copy table escape recombine
    auto map(this->table);

    // combining
    for(auto it=map.begin(); it!=map.end() ;++it) {
        for(auto pre_it=it->second.begin(); pre_it!=it->second.end(); pre_it++) {
            // build key
            std::vector<int> key(it->first);
            key.push_back(pre_it->first);

            // inner iterate to combine same key item
            for(auto post_it=pre_it; post_it!=it->second.end() ;post_it++) {
                if(post_it == pre_it)
                    continue;
                this->table[key][post_it->first] = 0;
            }
        }

        // erase from local table
        this->table.erase(it->first);
    }
}

void Apriori::generateC2() {
    // generateC1
    int* item_temp = this->reader.getFreqItem();
    std::vector<int> empty_v;

    while(item_temp != 0) {
        std::sort(item_temp+1, item_temp+item_temp[0]+1);

        for(int i=0; i<item_temp[0] ;++i)
            this->table[empty_v][item_temp[i+1]]++;

        free(item_temp);
        item_temp = this->reader.getFreqItem();
    }
    this->reader.resetFilePointer();
    this->round1_candidate_count = this->size();

    // filiter frequent
    this->filiter();
    this->lsize_count += this->per_round_lcount;

    // combine to generateC2
    for(auto it=this->table[empty_v].begin(); it!=this->table[empty_v].end() ;) {
        // construct vector key for per round
        std::vector<int> key = {it->first};

        for(auto it_inner = ++it; it_inner!=this->table[empty_v].end() ;++it_inner)
            this->table[key][it_inner->first] = 0;
    }

    this->table.erase(empty_v);
    this->per_round_candidate_count = this->size();
}

void Apriori::scan(int level) {
    int*item_temp = this->reader.getFreqItem();
    int key_size(level-1);

    while(item_temp != 0) {
        for(auto it=this->table.begin(); it!=this->table.end() ;++it) {
            std::vector<int> key = it->first;
            int flag = 1;

            for(auto key_it=key.begin(); key_it!=key.end() ;key_it++)
                if(std::find(item_temp+1, item_temp+item_temp[0]+1, *key_it) == item_temp+item_temp[0]+1)
                    flag = 0;

            if(flag) {
                // scan key_set
                for(auto inner=it->second.begin(); inner!=it->second.end() ;++inner) {
                    if(std::find(item_temp+1, item_temp+item_temp[0]+1, inner->first) != item_temp+item_temp[0]+1)
                        inner->second++;
                }
            }
        }

        free(item_temp);
        item_temp = this->reader.getFreqItem();
    }
    this->reader.resetFilePointer();
    this->per_round_candidate_count = this->size();
}

void Apriori::filiter() {
    // iterate all category of fornt label
    for(auto it=this->table.begin(); it!=this->table.end() ;) {
        // iterate inner hash
        for(auto group_it=it->second.begin(); group_it!=it->second.end() ;) {
            
            if(group_it->second < this->support) {
                auto deleted = group_it++;
                it->second.erase(deleted);
                continue;
            }
            group_it++;
        }

        if(it->second.empty()) {
            auto deleted = it++;
            this->table.erase(deleted);
            continue;
        }

        it++;
    }

    this->per_round_lcount = this->size();
}



int Apriori::size() {
    int sum = 0;
    for(auto it=this->table.begin(); it!=this->table.end() ;++it)
        sum += it->second.size();

    return sum;
}