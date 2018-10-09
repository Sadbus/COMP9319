//
// Created by Olav Markus Sjursoe on 15/09/18.
//

#ifndef BWTSEARCH_UTIL_H
#define BWTSEARCH_UTIL_H

#include <iostream>
#include <vector>
#include <map>

class Util {
public:
    static void print_usage(char* argv[]);
    std::string get_file_contents(const std::string &filename);
    std::string get_file_contents(const std::string &filename, const std::string &path);
    char get_char_at_pos(const std::string &filename, unsigned int pos);
    std::string get_file_substring(const std::string &filename, unsigned int i, unsigned int j);

    std::map<char, unsigned int> construct_c_table(const std::string &filename, const std::string &c_table_path);
    std::map<char, unsigned int> read_c_table(const std::string &c_table_path);

    std::map<char, std::map<int, int>> construct_occ_array(const std::string &filename, const int alphabet_size);


    int rank(const std::string &filename, char c, unsigned int n);

    bool exists(const std::string &filename);
    bool exists_2 (const std::string& name);
    size_t get_file_size(const std::string &filename);

    void write_encoded_file(const std::string &path, const std::string &s);
    void write_pos_info(const std::string &outputPath, const std::vector<int> &delim_pos);
    void read_pos_info(const std::string &filepath, std::vector<int> &pos);
};


#endif //BWTSEARCH_UTIL_H
