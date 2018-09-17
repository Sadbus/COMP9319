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
    Search(const std::string &input_file)
    {
        Util util;
        L = util.get_file_contents(input_file);

        create_c_table();
    }


    void num_substring_matches(const char d, const std::string &index_folder, const std::string &query);
    void num_record_matches(const char d, const std::string &index_folder, const std::string &query);
    void print_identifiers(const char d, const std::string &index_folder, const std::string &query);
    void print_records(const char d, const std::string &index_folder, const std::string &query);

protected:
    int backward_search(const std::string query);
    int rank(const char c, const unsigned int n);
    void create_c_table();

    // dictionary containing mappings from characters to number
    // of characters alphabetically smaller
    std::map<char, unsigned int> c_table;

    // Last column of bwt transform
    std::string L;
};


#endif //BWTSEARCH_SEARCH_H
