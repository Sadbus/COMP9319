//
// Created by Olav Markus Sjursoe on 7/09/18.
//

#include "bwt.h"

#include <vector>
#include <map>
#include <cstring>


/**
 *
 * @param str
 * @return
 */
std::vector<int> BWT::build_suffix_array(const std::string &str) {
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

    return order;
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
void BWT::sort_characters(const char *s, const size_t n, std::vector<int> &order)
{
    std::map<char, int> freq;

    for (int i = 0; i < n; i++)
        freq[s[i]]++;

    //for (int j = 1; j < freq.size(); j++)
    //    freq[j] = freq[j] + freq[j-1];


    for (auto itr = std::next(freq.begin()); itr != freq.end(); itr++)
        itr->second += std::prev(itr)->second;


    for (int i = n-1; i >= 0; i--)
    {
        char c = s[i];
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
void BWT::compute_char_classes(const char *s, const size_t n, const std::vector<int> &order, std::vector<int> &classes)
{
    // Initialize psotition where the smallest string occours to 0
    classes[order[0]] = 0;

    // Assign classes
    for (int i = 1; i < n; i++)
    {
        // if char is different than the previous one in the order ...
        // i.e if curr is different then prev, curr is bigger
        if (s[order[i]] != s[order[i-1]])
            classes[order[i]] = classes[order[i-1]] + 1; // Assign new class
        else // Character is same as previous
            classes[order[i]] = classes[order[i-1]]; // Assign same class as prev char
    }
}

/**
 *
 * @param s
 * @param n
 * @param order
 * @param classes
 * @param l
 * @return
 */
std::vector<int> BWT::sort_doubled(const char *s, const size_t n, const std::vector<int> &order, const std::vector<int> &classes, int l)
{
    std::vector<int> count(n, 0);
    std::vector<int> newOrder(n, 0);

    for (int i = 0; i < n; i++)
        count[classes[i]]++;

    for (int j = 1; j < n; j++)
        count[j] += count[j-1];

    for (int i = static_cast<int>(n - 1); i >= 0; i--)
    {
        int start = static_cast<int>((order[i] - l + n) % n);
        int cl = classes[start];
        count[cl]--;
        newOrder[count[cl]] = start;
    }

    return newOrder;
}

/**
 *
 * @param newOrder
 * @param classes
 * @param l
 * @return
 */
std::vector<int> BWT::update_classes(const std::vector<int> &newOrder, const std::vector<int> &classes, const int l)
{
    int n = newOrder.size();
    std::vector<int> newClass(n);
    newClass[newOrder[0]] = 0;

    for (int i = 1; i < n; i++)
    {
        int curr = newOrder[i];
        int prev = newOrder[i - 1];
        int mid = (curr + l);
        int midPrev = (prev + l) % n;

        if (classes[curr] != classes[prev] || classes[mid] != classes[midPrev])
            newClass[curr] = newClass[prev] + 1;
        else
            newClass[curr] = newClass[prev];
    }
    return newClass;
}