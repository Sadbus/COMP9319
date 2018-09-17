//
// Created by Olav Markus Sjursoe on 15/09/18.
//

#ifndef BWTSEARCH_UTIL_H
#define BWTSEARCH_UTIL_H


class Util {
public:
    static void print_usage(char* argv[]);
    std::string get_file_contents(const std::string &filename);
    std::string get_file_contents(const std::string &filename, const std::string &path);

};


#endif //BWTSEARCH_UTIL_H
