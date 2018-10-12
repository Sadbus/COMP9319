#include <iostream>
#include <cstring>
#include <map>
#include <sstream>
#include <vector>
#include <ctime>
#include "util.h"
#include "search.h"

/*
 * Args:
 * 1. delimiter
 * 2. input_file
 * 3. index_folder
 * 4. option
 * 5. query search_term
 */

int main(int argc, char* argv[])
{
    if (argc < 6)
    {
        Util::print_usage(argv);

        exit(1);
    }

    std::string str = argv[1];
    char d;

    if (str.find("\\n") != std::string::npos)
        d = '\n';
    else
        d = str[1];

    std::string option = argv[4];

    Search search(argv[2], argv[3], d);

    try
    {
        if(option.compare("-m") == 0)
        {
            // Print the number of matching substrings (including duplicates)
            search.num_substring_matches(d, argv[3], argv[5]);

        }
        else if (option.compare("-n") == 0)
        {
            // Print the number of unique matching records
            search.num_record_matches(d, argv[3], argv[5]);
        }
        else if (option.compare("-a") == 0)
        {
            // List the unique identifiers of all the matching records in
            // ascending order.
            search.print_identifiers(d, argv[3], argv[5]);
        }
        else if (option.compare("-i") == 0)
        {
            //Display the content of the records with ids provided in the search term
            search.print_records(d, argv[3], argv[5]);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}
