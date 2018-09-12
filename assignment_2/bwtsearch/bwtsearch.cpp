#include <iostream>
#include <cstring>

std::string get_file_contents(const char *filename)
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

void print_usage(char* argv[])
{
    std::cerr << "Usage: " << argv[0] << std::endl
              << "\t" << " 'delimiter' encoded_file index_folder -m 'query_string' (matching substrings)" << std::endl
              << "\t" << " 'delimiter' encoded_file index_folder -n 'query_string' (number of unique matching records)" << std::endl
              << "\t" << " 'delimiter' encoded_file index_folder -a 'query_string' (listing all identifiers)" << std::endl
              << "\t" << " 'delimiter' encoded_file index_folder -i 'record_id' (diplay contents of record)" << std::endl;
}


int main(int argc, char* argv[])
{
    if (argc < 6)
    {
        print_usage(argv);
        exit(1);
    }

    try
    {
        if(strcmp(argv[4], "-m"))
        {
            // Return the number of matching substrings (including duplicates)
        }
        else if ( strcmp(argv[4], "-n"))
        {
            // Return the number of unique matching records

        }
        else if (strcmp(argv[4], "-a"))
        {
            // List the unique identifiers of all the matching records in
            // ascending order.
        }
        else if (strcmp(argv[4], "-i"))
        {
            // Display the content of the records with ids provided in the search term
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}