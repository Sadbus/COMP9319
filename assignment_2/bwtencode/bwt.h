//
// Created by Olav Markus Sjursoe on 7/09/18.
//

#ifndef BWTENCODE_BWT_H
#define BWTENCODE_BWT_H


#include <string>

class BWT
{
public:
    std::vector<int> compute_suffix_array(const std::string &s);

protected:
    void bucket_sort(int a[], int n);
};


#endif //BWTENCODE_BWT_H
