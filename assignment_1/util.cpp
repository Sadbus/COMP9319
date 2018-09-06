//
// Created by Olav Markus Sjursoe on 9/08/18.
//

#include <cstring>
#include <algorithm>
#include "util.h"
#include "huffman.h"


size_t Util::GetFileSize(const std::string &filename)
{
    struct stat stat_buf{};
    int rc = stat(filename.c_str(), &stat_buf);
    return static_cast<size_t>(rc == 0 ? stat_buf.st_size : -1);
}

int Util::countSubstring(const std::string& str, const std::string& sub)
{
    if (sub.length() == 0) return 0;
    int count = 0;
    for (size_t offset = str.find(sub); offset != std::string::npos;
         offset = str.find(sub, offset + 1))
    {
        ++count;
    }
    return count;
}

void Util::WriteBinary(unsigned char i, std::ofstream &outfile)
{
    static int bit_pos = 0;
    static unsigned char c = '\0';

    if(i < 2)
    {
        if(i == 1)
            c = c | (i << (7 - bit_pos));
        else
            c = c & static_cast<unsigned char>(255 - (1 << (7 - bit_pos)));

        ++bit_pos;
        bit_pos %= 8;

        if(bit_pos == 0)
        {
            outfile.put(c);
            c = '\0';
        }
    }
    else
        outfile.put(c);
}

unsigned char Util::ReadBinary(std::ifstream &infile)
{
    static int bit_pos = 0;
    static unsigned char c = static_cast<unsigned char>(infile.get());

    unsigned char i;

    i = static_cast<unsigned char>((c >> (7 - bit_pos)) % 2);
    ++bit_pos;
    bit_pos %= 8;

    if(bit_pos == 0)
    {
        if(!infile.eof())
            c = static_cast<unsigned char>(infile.get());
        else
            i = 2;
    }

    return i;
}

std::map<char, int> Util::ReadHeader(std::string path)
{
    std::ifstream file(path);
    char buffer[HEADER_SIZE];

    std::map<char, int> map;
    map.clear();

    file.read(buffer, HEADER_SIZE);

    for (int i = 0; i < HEADER_SIZE; i++)
    {
        if (buffer[i] == '#')
            break;
        else if (buffer[i] == ':')
        {
            std::string freqStr;
            int j = i + 1;
            while(isdigit(buffer[j]))
            {
                freqStr += buffer[j];
                j++;
            }
            int freq = std::stoi(freqStr);
            map[buffer[i-1]] = freq;
        }

    }

    file.close();

    return map;
}

std::map<char, int> Util::BuildStatistics(std::string path)
{
    std::ifstream file(path);
    constexpr size_t bufferSize = 1024 * 1024;
    char buff[bufferSize];
    memset(buff, 0, strlen(buff));

    std::map<char, int> map;
    map.clear();

    while (file)
    {
        file.read(buff, bufferSize);

        for (char &c : buff)
        {
            if (c == NULL)
                break;
            else if(map.find(c) == map.end())
                map[c] = 1;
            else
                map[c]++;
        }
    }

    file.close();

    return map;
}

void
Util::Encode(const std::string &inputFile, const std::string &outputFile, const std::string &header, std::map<char, std::string> codes)
{
    std::ifstream inFile(inputFile, std::ios::in | std::ios::binary);
    std::ofstream outFile(outputFile, std::ifstream::binary);
    std::string in = "", s = "";

    if (inFile.fail())
        std::cerr << "file: " << inputFile << " failed to open" << std::endl;

    if (outFile.fail())
        std::cerr << "file: " << outputFile << " failed to open" << std::endl;

    std::string padding;
    int paddingLength = HEADER_SIZE - header.length();
    padding.insert(padding.begin(), paddingLength, '#');
    outFile << header << padding;

    char c;
    unsigned char ch;
    unsigned char ch2;
    while(inFile.get(c))
    {
        //outFile << codes[c];
        ch = c;

        for (unsigned int i = 0; i<codes[ch].size(); i++)
        {
            if (codes[ch].at(i) == '0')
                ch2 = 0;
            if (codes[ch].at(i) == '1')
                ch2 = 1;

            WriteBinary(ch2, outFile);
        }
    }
    ch2 = 2;
    WriteBinary(ch2, outFile);

    inFile.close();
    outFile.close();
}

void Util::Decode(const std::string &inputFile, const std::string &outputFile, std::map<char, int> freqMap)
{
    std::ifstream inFile(inputFile, std::ifstream::binary);
    std::ofstream outFile(outputFile);

    Huffman huffman;

    char temp;
    for (int i = 0; i < 1024; i++)
        inFile.get(temp);

    huffman.BuildTree(freqMap);

    if (inFile.fail())
        std::cerr << "file: " << inputFile << " failed to open" << std::endl;
    if (outFile.fail())
        std::cerr << "file: " << outputFile << " failed to open" << std::endl;

    std::string st;
    unsigned char ch;
    unsigned char ch2;

    unsigned int totalChar = huffman.getTotFreq();

    while (totalChar > 0)
    {
        st = "";
        do
        {
            ch = ReadBinary(inFile);
            if (ch == 0)
                st = st + '0';
            if (ch == 1)
                st = st + '1';
        }
        while (!huffman.Decode(st, ch2));

        outFile.put(static_cast<char>(ch2));

        totalChar--;
    }

    inFile.close();
    outFile.close();
}

void Util::Search(const std::string &searchTerm, const std::string &path, std::map<char, int> freqMap)
{
    std::ifstream file(path, std::ifstream::binary);

    Huffman huffman;

    char temp;
    for (int i = 0; i < 1024; i++)
        file.get(temp);

    huffman.BuildTree(freqMap);

    if (file.fail())
        std::cerr << "file: " << path << " failed to open" << std::endl;

    std::string st;
    unsigned char ch;
    unsigned char ch2;

    unsigned int totalChar = huffman.getTotFreq();

    std::string chunk = "";
    int numMatches = 0;

    while (totalChar > 0)
    {
        st = "";
        do
        {
            ch = ReadBinary(file);
            if (ch == 0)
                st = st + '0';
            if (ch == 1)
                st = st + '1';
        }
        while (!huffman.Decode(st, ch2));

        chunk += ch2;

        if (chunk.size() > 1024)
        {
            numMatches += countSubstring(chunk, searchTerm);
            chunk = "";
        }

        totalChar--;
    }

    numMatches += countSubstring(chunk, searchTerm);

    std::cout << numMatches;

    file.close();

}

