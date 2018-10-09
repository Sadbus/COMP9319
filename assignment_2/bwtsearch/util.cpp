//
// Created by Olav Markus Sjursoe on 15/09/18.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <sys/stat.h>
#include <math.h>
#include <unistd.h>
#include "util.h"

/**
 *
 * @param path
 * @param s
 */
void Util::write_encoded_file(const std::string &path, const std::string &s)
{
    std::fstream file(path, std::ios::out | std::ios::binary);
    file << s;
    file.close();
}

/**
 *
 * @param folder_path
 * @param s
 */
void Util::write_pos_info(const std::string &outputPath, const std::vector<int> &delim_pos)
{
    std::string filepath = outputPath + ".aux";

    std::fstream file(filepath, std::ios::out | std::ios::binary);

    for (int i : delim_pos)
    {
        file << i << ",";
    }
}

/**
 * Utility function to print instructions in case of invalid arguments.
 *
 * @param argv program arguments
 */
void Util::print_usage(char **argv)
{
    std::cerr << "Usage: " << argv[0] << std::endl
              << "\t" << " 'delimiter' encoded_file index_folder -m 'query_string' (matching substrings)" << std::endl
              << "\t" << " 'delimiter' encoded_file index_folder -n 'query_string' (number of unique matching records)" << std::endl
              << "\t" << " 'delimiter' encoded_file index_folder -a 'query_string' (listing all identifiers)" << std::endl
              << "\t" << " 'delimiter' encoded_file index_folder -i 'record_id' (diplay contents of record)" << std::endl;
}

/**
 * This function takes a filename, reads the contents of the file
 * and returns its content as string.
 *
 * @param filename filename to read into memory
 * @return contents of the file
 */
std::string Util::get_file_contents(const std::string &filename)
{
    std::FILE *fp = std::fopen(filename.c_str(), "rb");
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

/**
* Function overload to allow addditional parameter
*
* @param filename of file
* @param path path to folder containing file
* @return
*/
std::string Util::get_file_contents(const std::string &filename, const std::string &path)
{
    std::string filepath = path + "/" + filename;
    return get_file_contents(filepath);
}

/**
 * Reads a substring from file.
 *
 * @param filename file to read
 * @param i start index
 * @param j end index
 * @return substring of file
 */
std::string Util::get_file_substring(const std::string &filename, unsigned int i, unsigned int j)
{
    std::ifstream file(filename);
    std::string s;

    if (file.is_open())
    {
        file.seekg(i);
        s.resize(j - i);
        file.read(&s[0], j - i);
    }

    //std::cout << "Read " << j-i << "bytes" << std::endl;

    return s;
}

char Util::get_char_at_pos(const std::string &filename, unsigned int pos)
{
    std::ifstream file(filename);
    char c = '\0';

    if (file.is_open())
    {
        file.seekg(pos);
        file.read(&c, 1);
    }

    return c;
}



std::map<char, unsigned int> Util::construct_c_table(const std::string &filename, const std::string &c_table_path)
{
    std::ifstream file(filename, std::fstream::in);
    char ch = '\0';

    std::map<char, unsigned int> freq;
    std::map<char, unsigned int> c_table;

    while (file >> std::noskipws >> ch)
    {
        freq[ch]++;
    }

    for (auto itr = std::next(freq.begin()); itr != freq.end(); itr++)
        itr->second += std::prev(itr)->second;

    for (auto itr = std::next(freq.begin()); itr != freq.end(); itr++)
        c_table[itr->first] = std::prev(itr)->second;

    // Write c_table to file

    std::fstream outFile(c_table_path, std::ios::out | std::ios::binary);

    for (auto itr = c_table.begin(); itr != c_table.end(); itr++)
    {
        outFile << itr->first << " " << itr->second << std::endl;
    }

    return c_table;
}


std::map<char, unsigned int> Util::read_c_table(const std::string &c_table_path)
{
    std::ifstream file(c_table_path);
    std::map<char, unsigned int> c_table;

    char first;
    int second = 0;

    while (file >> first >> second)
        c_table[first] = second;

    return c_table;
}

std::map<char, std::map<int, int>> Util::construct_occ_array(const std::string &filename, const int alphabet_size)
{
    const int chunk_size = 1000;
    size_t total_size = get_file_size(filename);
    size_t num_chunks = total_size/chunk_size;

    std::ifstream file(filename, std::ifstream::binary);

    std::map<char, std::map<int, int>> occ;

    for (size_t chunk = 0; chunk < num_chunks; chunk++)
    {

        std::vector<char> chunk_data(chunk_size);
        file.read(&chunk_data[0], chunk_size);

        std::map<char, int> freq;

        for (const char ch : chunk_data)
            occ[ch][0] = 0;
    }

    file.seekg(0);

    for (size_t chunk = 0; chunk < num_chunks; chunk++)
    {
        std::vector<char> chunk_data(chunk_size);
        file.read(&chunk_data[0], chunk_size);

        std::map<char, int> freq;

        for (const char ch : chunk_data)
            occ[ch][chunk]++;
    }

    for (auto itr1 = occ.begin(); itr1 != occ.end(); itr1++)
    {
        // itr = bokstav
        // itr->second map<int, int>

        for (auto itr2 = std::next(itr1->second.begin()); itr2 != itr1->second.end(); itr2++)
        {

            itr2->second += std::prev(itr2)->second;
        }
    }

    std::cout << "Size of occ table: "
              << sizeof(occ) + occ.size() * (sizeof(decltype(occ)::key_type)
                                          + sizeof(decltype(occ)::mapped_type))
              << " byte"
              << std::endl;


    return occ;
}

int Util::rank(const std::string &filename, const char c, unsigned int n)
{
    const int chunk_size = 16 * 1024;
    size_t num_chunks = n/chunk_size;
    size_t last_chunk_size = n % chunk_size;
    int occ = 0;


    if (last_chunk_size != 0)
        num_chunks++;
    else
        last_chunk_size = chunk_size;

    std::ifstream file(filename, std::ifstream::binary);

    for (size_t chunk = 0; chunk < num_chunks; chunk++)
    {
        size_t current_chunk_size =
                chunk == num_chunks - 1 // if last chunk
                ? last_chunk_size       // then fill chunk with remaining bytes
                : chunk_size;           // else fill entire chunk

        std::vector<char> chunk_data(current_chunk_size);
        file.read(&chunk_data[0], current_chunk_size);

        for (const char ch : chunk_data)
        {
            if (c == ch)
                occ++;
        }
    }

    return occ;
}


void Util::read_pos_info(const std::string &filepath, std::vector<int> &pos)
{
    std::fstream file(filepath);
    std::string temp;

    while(!file.eof())
    {
        getline(file, temp, ',');
        if(temp != "")
            pos.push_back(std::stoi(temp));
    }

}

bool Util::exists(const std::string &filename)
{
    struct stat buffer;
    return (stat (filename.c_str(), &buffer) == 0);
}

bool Util::exists_2 (const std::string& name) {
    return ( access( name.c_str(), F_OK ) != -1 );
}


size_t Util::get_file_size(const std::string &filename)
{
    struct stat stat_buf;
    int rc = stat(filename.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}
