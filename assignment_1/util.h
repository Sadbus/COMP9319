//
// Created by Olav Markus Sjursoe on 9/08/18.
//

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <map>

#ifndef ASSIGNMENT_1_UTIL_H
#define ASSIGNMENT_1_UTIL_H

#define HEADER_SIZE 1024

class Util
{
public:
    std::map<char, int> ReadHeader(std::string path);
    std::map<char, int> BuildStatistics(std::string path);
    void WriteBinary(unsigned char i, std::ofstream &outfile);
    unsigned char ReadBinary(std::ifstream &infile);

    void Encode(const std::string &inputFile, const std::string &outputFile, const std::string &header, std::map<char, std::string> codes);
    void Decode(const std::string &inputFile, const std::string &outputFile, std::map<char, int> freqMap);
    void Search(const std::string &searchTerm, const std::string &path, std::map<char, int> freqMa);


protected:
    size_t GetFileSize(const std::string &filename);
    int countSubstring(const std::string& str, const std::string& sub);

};

#endif //ASSIGNMENT_1_UTIL_H
