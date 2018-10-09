//
// Created by Olav Markus Sjursoe on 27/09/18.
//

#ifndef BWTENCODE_UTIL_H
#define BWTENCODE_UTIL_H


#include <string>
#include <vector>

class Util {
public:
    void write_encoded_file(const std::string &path, const std::string &s);
    void write_pos_info(const std::string &outputPath, const std::vector<int> &pos);
    std::string get_file_contents(const char * filename);

protected:

};


#endif //BWTENCODE_UTIL_H
