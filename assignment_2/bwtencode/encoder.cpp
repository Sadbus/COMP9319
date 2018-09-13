//
// Created by Olav Markus Sjursoe on 7/09/18.
//

#include <fstream>
#include <iostream>
#include <vector>
#include <cstring>
#include <sstream>
#include "encoder.h"
#include "bwt.h"

void Encoder::write_encoded_file(const std::string &path, const std::string &s)
{
    std::fstream file(path, std::ios::out | std::ios::binary);
    file << s;
    file.close();
}

void Encoder::write_pos_info(const std::string &folder_path, const std::string &s, const char &d)
{
    // TODO: Change this to input filename +.aux
    std::string filename = "pos.aux";
    std::string filepath = folder_path + "/" + filename;

    std::fstream file(filepath, std::ios::out | std::ios::binary);

    int index = 0;
    int prev = 0;
    for (char c : s)
    {
        if (c == d)
        {
            file << prev+index << ",";
            prev += index;
            index = 0;
        }

        index++;
    }
}

std::string Encoder::get_file_contents(const char *filename)
{
    std::FILE *fp = std::fopen(filename, "rb");
    if (fp)
    {
        std::string contents;
        std::fseek(fp, 0, SEEK_END);
        contents.resize(std::ftell(fp));
        std::rewind(fp);
        std::fread(&contents[0], 1, contents.size(), fp);
        std::fclose(fp);
        return(contents);
    }
    throw(errno);
}

void Encoder::encode(const char &d, const std::string &folderPath,
                     const char *inputPath, const std::string &outputPath)
{
    // Read the entire input file
    std::string s = get_file_contents(inputPath);
    const unsigned int n = s.size();


    BWT bwt;

    // Encode
    std::vector<int> suffixArray = bwt.compute_suffix_array(s);


    std::string encoded;

    for (int i = 0; i < n; ++i)
    {
        int bwtIndex = suffixArray[i] - 1;

        if (bwtIndex < 0)
            bwtIndex = n -1;

        encoded.append(s.substr(bwtIndex, 1));
    }

    write_encoded_file(outputPath, encoded);

    write_pos_info(folderPath, s, d);
}


