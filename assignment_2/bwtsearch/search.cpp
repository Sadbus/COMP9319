//
// Created by Olav Markus Sjursoe on 15/09/18.
//

#include "search.h"

/**
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
    int first = c_table[c];

    // TODO: Handle error case, ex. char not in map.
    int last = std::next(c_table.find(c))->second;

    while (first <= last && i > 0)
    {
        c = P[i-1];
        first = c_table[c] + rank(c, first - 1) + 1;
        last = c_table[c] + rank(c, last);
        i--;
    }

    if (last < first)
        return 0;
    else
        return (last - first + 1);
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

    for (char ch : L)
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
 * This function constructs a C table from the bwt encode string L.
 * C[c] contains the number of characters that are alphabetically
 * smaller than c. Implemented here as a map with character
 * key and integer value for easy lookup.
 *
 */
void Search::create_c_table()
{
    for (char c : L)
        if(c_table.find(c) == c_table.end())
            for (char ch : L)
                if (ch < c)
                    c_table[c]++;
}
