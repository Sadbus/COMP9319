//
// Created by Olav Markus Sjursoe on 7/09/18.
//

#ifndef BWTENCODE_ENCODER_H
#define BWTENCODE_ENCODER_H


#include <string>

class Encoder
{
public:
    void encode(const char &d, const std::string &folderPath, const char* inputPath, const std::string &outputPath);

};


#endif //BWTENCODE_ENCODER_H
