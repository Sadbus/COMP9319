//
// Created by Olav Markus Sjursoe on 7/09/18.
//

#ifndef BWTENCODE_ENCODER_H
#define BWTENCODE_ENCODER_H


#include <string>
#include <map>

class Encoder
{
public:
    void encode(const char &d, const std::string &folderPath, const char* inputPath, const std::string &outputPath);

protected:
    void write_encoded_file(const std::string &path, const std::string &s);
    std::string get_file_contents(const char *filename);
    std::map<char, unsigned int> construct_c_table(const std::string &s);
    void write_pos_info(const std::string &folder_path, const std::string &s, const char &d);

};


#endif //BWTENCODE_ENCODER_H
