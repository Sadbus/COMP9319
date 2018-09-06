#include <algorithm>
#include <iostream>
#include <map>
#include <cstring>
#include <sstream>
#include <vector>
#include <queue>

#include "util.h"
#include "huffman.h"

std::map<char, int> freqMap;
std::string header;



void GenerateHeader(std::map<char, int> m)
{
    header.empty();

    std::stringstream ss;
    std::string temp;

    for(const auto& val: m)
    {
        ss << val.first << ":" << val.second << ", ";
    }


    temp = ss.str();
    header = temp.substr(0, temp.length() - 2);
}

void Encode(std::string inputFilePath, std::string outputFilePath)
{

    Util util;
    Huffman huffman;

    freqMap = util.BuildStatistics(inputFilePath);

    GenerateHeader(freqMap);

    std::map<char, std::string> codes = huffman.BuildTree(freqMap);

    util.Encode(inputFilePath, outputFilePath, header, codes);
}

void Decode(std::string inputFilePath, std::string outputFilePath)
{
    Util util;

    freqMap = util.ReadHeader(inputFilePath);

    util.Decode(inputFilePath, outputFilePath, freqMap);
}

void search(std::string s, std::string filePath)
{
    Util util;

    freqMap = util.ReadHeader(filePath);
    std::string searchTerm = s.substr(0, s.size());

    util.Search(searchTerm, filePath, freqMap);
}



int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        std::cout << "Invalid arguments" << std::endl;
        return 0;
    }

    // Program arguments
    std::string option = argv[1];
    std::string arg2 = argv[2];
    std::string arg3 = argv[3];

    if (option == "-e")
        Encode(arg2, arg3);
    else if (option == "-d")
        Decode(arg2, arg3);
    else if (option == "-s")
        search(arg2, arg3);
    else
        std::cout << "Invalid argument." << std::endl;

    return 0;
}