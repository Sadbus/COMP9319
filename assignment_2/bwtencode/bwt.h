//
// Created by Olav Markus Sjursoe on 7/09/18.
//

#ifndef BWTENCODE_BWT_H
#define BWTENCODE_BWT_H


#include <string>
#include <vector>

class BWT
{
public:
    std::vector<int> build_suffix_array(const std::string &str);

protected:
    void sort_characters(const char *s, const size_t n, std::vector<int> &order);
    void compute_char_classes(const char *s, const size_t n, const std::vector<int> &order, std::vector<int> &classes);
    std::vector<int> sort_doubled(const char *S, const size_t n, const std::vector<int> &order, const std::vector<int> &classes, int L);
    std::vector<int> update_classes(const std::vector<int> &newOrder, const std::vector<int> &classes, const int l);
};


#endif //BWTENCODE_BWT_H
