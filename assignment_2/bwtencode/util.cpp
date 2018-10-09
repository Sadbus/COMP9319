//
// Created by Olav Markus Sjursoe on 27/09/18.
//

#include <fstream>
#include <vector>

#include "util.h"


void Util::write_encoded_file(const std::string &path, const std::string &s)
{
    std::fstream file(path, std::ios::out | std::ios::binary);
    file << s;
    file.close();
}

void Util::write_pos_info(const std::string &outputPath, const std::vector<int> &pos)
{
    std::string filepath = outputPath + ".aux";

    std::fstream file(filepath, std::ios::out | std::ios::binary);

    for (int i : pos)
    {
        file << i << ",";
    }
}

std::string Util::get_file_contents(const char *filename)
{
    std::FILE *fp = std::fopen(filename, "rb");
    if (fp)
    {
        std::string contents;
        std::fseek(fp, 0, SEEK_END);
        contents.resize(std::ftell(fp));
        std::rewind(fp);
        if (std::fread(&contents[0], 1, contents.size(), fp))
        {
            std::fclose(fp);
            return(contents);
        }
    }
    throw(errno);
}
