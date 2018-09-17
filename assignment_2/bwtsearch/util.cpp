//
// Created by Olav Markus Sjursoe on 15/09/18.
//

#include <iostream>
#include "util.h"


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
