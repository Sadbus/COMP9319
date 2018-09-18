#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <ctime>
#include "bwt.h"
#include "encoder.h"

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

/**
 * Time: O(|S|)
 *
 * Sort all cyclic rotations of S with length 1 using count sort
 *
 * @param order array of order
 * @param S input string
 * @param n length of S
 */
void sort_characters(const char *S, const size_t n, std::vector<int> &order)
{
    std::map<char, int> freq;

    for (int i = 0; i < n; i++)
        freq[S[i]]++;

    //for (int j = 1; j < freq.size(); j++)
    //    freq[j] = freq[j] + freq[j-1];


    for (auto itr = std::next(freq.begin()); itr != freq.end(); itr++)
       itr->second += std::prev(itr)->second;


    for (int i = n-1; i >= 0; i--)
    {
        char c = S[i];
        freq[c]--;
        order[freq[c]] = i;
    }
}


/**
 * O(|S|) fucntion to assign classes to each character in string S
 *
 * @param classes
 * @param order
 * @param S
 * @param n
 */
void compute_char_classes(const char *S, const size_t n, const std::vector<int> &order, std::vector<int> &classes)
{
    // Initialize psotition where the smallest string occours to 0
    classes[order[0]] = 0;

    // Assign classes
    for (int i = 1; i < n; i++)
    {
        // if char is different than the previous one in the order ...
        // i.e if curr is different then prev, curr is bigger
        if (S[order[i]] != S[order[i-1]])
            classes[order[i]] = classes[order[i-1]] + 1; // Assign new class
        else // Character is same as previous
            classes[order[i]] = classes[order[i-1]]; // Assign same class as prev char
    }
}

std::vector<int> sort_doubled(const char *S, const size_t n, const std::vector<int> &order, const std::vector<int> &classes, int L)
{
    std::vector<int> count(n, 0);
    std::vector<int> newOrder(n, 0);

    for (int i = 0; i < n; i++)
        count[classes[i]]++;

    for (int j = 1; j < n; j++)
        count[j] += count[j-1];

    for (int i = static_cast<int>(n - 1); i >= 0; i--)
    {
        int start = static_cast<int>((order[i] - L + n) % n);
        int cl = classes[start];
        count[cl]--;
        newOrder[count[cl]] = start;
    }

    return newOrder;
}

std::vector<int> update_classes(const std::vector<int> &newOrder, const  std::vector<int> &classes, const int L)
{
    int n = newOrder.size();
    std::vector<int> newClass(n);
    newClass[newOrder[0]] = 0;

    for (int i = 1; i < n; i++)
    {
        int curr = newOrder[i];
        int prev = newOrder[i - 1];
        int mid = (curr + L);
        int midPrev = (prev + L) % n;

        if (classes[curr] != classes[prev] || classes[mid] != classes[midPrev])
            newClass[curr] = newClass[prev] + 1;
        else
            newClass[curr] = newClass[prev];
    }
    return newClass;
}

void build_suffix_array(const std::string &str)
{
    char *S = new char[str.length() + 1];
    strcpy(S, str.c_str());

    size_t n = str.length();

    std::vector<int> order(n, 0);
    std::vector<int> classes(n, 0);

    sort_characters(S, n, order);
    compute_char_classes(S, n, order, classes);
    int L = 1;

    while (L < n)
    {
           order = sort_doubled(S, n, order, classes, L);
           classes = update_classes(order, classes, L);
           L = 2*L;
    }

    //std::cout << "Order = {";
    //for (int i = 0; i < n; i++)
    //    std::cout << order[i] << ", ";
    //std::cout << "}" << std::endl;

}


int main(int argc, char* argv[])
{
    if (argc < 5)
    {
        std::cerr << "Usage: " << argv[0] << " 'delimiter' tmp_folder input_file output_file" << std::endl;
        exit(1);
    }

    std::string str = argv[1];
    char d;

    if (str.find("\\n") != std::string::npos)
        d = '\n';
    else
        d = str.at(3);

    std::string s = get_file_contents(argv[3]);
    std::cout << "Size of file: " << s.size() / 1024 << " KB" << std::endl;


    std::clock_t begin = std::clock();

    Encoder encoder;
    encoder.encode(d, argv[2], argv[3], argv[4]);

    std::clock_t end = clock();

    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    std::cout << "Time elapsed: " << elapsed_secs << " sec" << std::endl;

    return 0;
}

