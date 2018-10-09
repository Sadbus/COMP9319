//
// Created by Olav Markus Sjursoe on 15/09/18.
//

#include <sstream>
#include <ctime>
#include "search.h"


Search::Search(const std::string &input_file, const std::string &index_folder)
{
    this->filename = input_file;

    //L = util.get_file_contents(input_file);

    std::string c_table_path;
    std::string name;

    // TODO: Only  construct C table if it does not already exist
    // Extract filename from path
    size_t i = input_file.rfind('/', input_file.length());
    if (i != std::string::npos)
        name = input_file.substr(i+1, input_file.size() - i);
    else
        name = input_file;

    c_table_path = index_folder + "/" + name + ".c";

    if (util.exists(c_table_path))
    {
        //std::cout << "File: " << c_table_path << " exists. Load existing table" << std::endl;
        // Load c_table from file
        c_table = util.read_c_table(c_table_path);
    }
    else
    {
        //std::cout << "File: " << c_table_path <<  " does not exist. Construct table" << std::endl;
        // Construct a c_table

        c_table = util.construct_c_table(input_file, c_table_path);
    }


    std::string pos_filepath = input_file + ".aux";
    util.read_pos_info(pos_filepath, pos);

    //c_table = util.construct_c_table(input_file, c_table_path);
    //std::map<char, std::map<int, int>> occ_table = util.construct_occ_array(filename, c_table.size());

    //create_c_table();
}

/**
 * Performs a backward search on the encoded BWT string with the help
 * of the Rank function and C table.
 *
 *
 * @param P search term
 * @return number of matches for P in L
 */
int Search::backward_search(const std::string query)
{
    // c string P is the search term
    int p = static_cast<int>(query.size());
    char P[p];
    std::strcpy(P, query.c_str());

    int i = p-1; // Index of last character of P
    char c = P[p-1]; // Last character of P
    int first = c_table[c] + 1;
    int last;


    if (std::next(c_table.find(c)) != c_table.end())
        last = std::next(c_table.find(c))->second;
    else
        last =  (int) util.get_file_size(filename);

    while (first <= last && i > 0)
    {
        c = P[i-1];
        first = c_table[c] + util.rank(filename, c, first - 1) + 1;
        last = c_table[c] + util.rank(filename, c, last);
        i--;

        if (last < first)
            return 0;
    }

    return (last - first + 1);
}

/**
 * Takes in an index of a character in L and
 * returns its position in T
 *
 * @param lpos
 * @return
 */
int Search::locate(const unsigned int lpos)
{
    /*
     * To locate every occurrence of a pattern, first the range of
     * characters is found whose suffix is the pattern in the same
     * way the count operation found the range.
     *
     * To map an index in L to one in T, a subset of the indices in
     * L are associated with a position in T. If L[j] has a position
     * associated with it, locate(j) is is trivial. If its not associated,
     * the string is followed with LF(i) until an associated index is found.
     */

    unsigned int tpos = 0;


    return tpos;
}

/** -m
 * This function searches the bwt encoded file and returns the
 * number of matches for pattern p, including overlapping matches.
 *
 * @param d delimiter
 * @param input_file the bwt encoded file
 * @param index_folder the folder containing positional information
 * @pram query the search pattern
 */
void Search::num_substring_matches(const char d, const std::string &index_folder, const std::string &query)
{
    int numMatches = backward_search(query);

    std::cout << numMatches << std::endl;
}

/** -n
 * This function returns the number of records which contains
 * the search pattern.
 *
 * @param d record delimiter
 * @param input_file encoded bwt input file
 * @param index_folder folder containing positional information
 * @param query the search pattern
 */
void Search::num_record_matches(const char d, const std::string &index_folder, const std::string &query)
{
    /*
     * The number of unique records containing the search term
     *
     * Find last and first position of p in L.
     * LF
     *
     */


}

/** -a
 * Performs backward search on the given bwt encoded input file, and
 * outputs the sorted and unique record identifiers (no duplicates)
 * of all the records that contains the input query string.
 *
 * @param d record delimiter
 * @param input_file bwt encoded file
 * @param index_folder folder containing positional information
 * @param query the search pattern
 */
void Search::print_identifiers(const char d, const std::string &index_folder, const std::string &query)
{
    /*
     * List the identifiers of all the matching records (no duplicates, ASC)
     *
     * Using the given query string, bwtsearch will perform backward search on the given bwt encoded file,
     * and output the sorted and unique record identifiers of all the records that contain the input
     * query string to the standard output
     *
     * 1. Using backward search, find the rows containing the search term
     * 2. Locate the the position in T
     * 3. Using the auxilary positional information, locate which records contains the search term
     */


}

/** -i
 * Performs backward search on the given BWT encoded file and search for the
 * records with their identifiers beginning with i and ending with j, as specified
 * in the search term as "i j". It will print the content of the records
 *
 *
 * @param d record delimiter
 * @param input_file BWT encoded file
 * @param index_folder folder containing positional information
 * @param ids identifiers
 */
void Search::print_records(const char d, const std::string &index_folder, const std::string &query)
{
    std::string last = query.substr(2, query.size()-2);

    int firstRecord = std::stoi(query);
    int lastRecord = std::stoi(last);

    // TODO: How to get start index of record!?!?

    for (int i = firstRecord-1; i < lastRecord; i++)
    {
        int rowi = pos[i];
        char c = util.get_char_at_pos(filename, pos[i]);
        std::string r;

        while (c != d)
        {
            r = c + r;
            rowi = c_table[c] + util.rank(filename, c, rowi);
            c = util.get_char_at_pos(filename, rowi);
        }

        std::cout << r << std::endl;
        r = "";
    }
}

/**
 * This function calculates the number of occurences of a character c
 * in the interval [1, n] in the bwt encoded string L.
 *
 * @param c search character
 * @param n from index 1 to n
 */

int Search::rank(const char c, const unsigned int n)
{
    int occ = 0;
    int i = 0;

    /*
     * TODO: Optimize
     * Instead of finding occurrence each time. Pre-compute occurences at each 10th index
     */

/*
    for (int i = 0; i <= n; i++)
    {
        char ch = util.get_char_at_pos(filename, i);

        if (ch == c)
            occ++;
    }


    */

    std::string s = util.get_file_substring(filename, 0, n);

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


/**
 * This function constructs a C table from the bwt encoded string L.
 * C[c] contains the number of characters that are alphabetically
 * smaller than c. Implemented here as a map with character
 * key and integer value for easy lookup.
 *
 */

/*
void Search::create_c_table()
{
    // TODO: Clean this up. Try to avoid temporarily storing freq

    std::map<char, int> freq;

    for (int i = 0; i < L.length(); i++)
        freq[L[i]]++;

    for (auto itr = std::next(freq.begin()); itr != freq.end(); itr++)
        itr->second += std::prev(itr)->second;

    for (auto itr = std::next(freq.begin()); itr != freq.end(); itr++)
        c_table[itr->first] = std::prev(itr)->second;
}
*/