//
// Created by Olav Markus Sjursoe on 15/09/18.
//

#ifndef BWTSEARCH_SEARCH_H
#define BWTSEARCH_SEARCH_H

#include <iostream>
#include <cstring>
#include <map>
#include "util.h"


class Search {
public:
    Search(const std::string &input_file, const std::string &index_folder, const char d);

    void num_substring_matches(char d, const std::string &index_folder, const std::string &query);
    void num_record_matches(char d, const std::string &index_folder, const std::string &query);
    void print_identifiers(char d, const std::string &index_folder, const std::string &query);
    void print_records(char d, const std::string &index_folder, const std::string &query);

protected:
    int backward_search(std::string query);
    int locate(unsigned int lpos);
    int rank(char c, unsigned int n);
    void create_c_table();

    // dictionary containing mappings from characters to number
    // of characters alphabetically smaller
    std::map<char, unsigned int> c_table;
    std::map<char, std::map<int, int>> occ_table;
    std::vector<int> pos;

    // Last column of bwt transform
    //std::string L;
    std::string filename;

    Util util;
};


#endif //BWTSEARCH_SEARCH_H
