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

/*
 * constructs a c table (implemented as a map in this case) from
 * the encoded bwt string. The C[c] contains the number of characters
 * that are alphabetically smaller than c.
 *
 * @param s encoded bwt string
 */
std::map<char, unsigned int> construct_c_table(const std::string &s)
{
    std::map<char, unsigned int> c_table;

    for (char c : s)
        if(c_table.find(c) == c_table.end())
            for (char ch : s)
                if (ch < c)
                    c_table[c]++;

    return c_table;
}


/*
 * returns the rank (number of occurrences) of a character c in the range [1, n]
 * in the encoded bwt string, s.
 *
 * @param c search character
 * @param n from index 1 to n
 * @param s encoded bwt string
 */
int rank(const char c, const unsigned int n, const std::string &s)
{
    int occ = 0;
    int i = 0;

    for (char ch : s)
    {
        if (i >= n)
            break;

        if(ch == c)
            occ++;

        i++;
    }

    return occ;
}


void num_matching_substrings(const char &d, const std::string &input_file, const std::string &index_folder, const std::string &query) {}
void num_matching_records(const char &d, const std::string &input_file, const std::string &index_folder, const std::string &query) {}
void list_identifiers(const char &d, const std::string &input_file, const std::string &index_folder, const std::string &query) {}
void display_records(const char &d, const std::string &input_file, const std::string &index_folder, const int[] ids) {}


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
        print_usage(argv);
        exit(1);
    }

    std::string str = argv[1];
    char d = '0';

    if (str.find("\\n") != std::string::npos)
        d = '\n';
    else
        d = str.at(3);

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
