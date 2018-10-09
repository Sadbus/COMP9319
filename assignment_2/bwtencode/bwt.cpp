//
// Created by Olav Markus Sjursoe on 7/09/18.
//

#include <map>

#include "bwt.h"


/**
 * Constructs suffix array by first sorting single character cyclic shifts of S.
 * Then sort cyclic shifts of size 2L until L > |S|.
 *
 * @param s input text
 * @return array of sorted suffixes
 */
std::vector<int> BWT::build_suffix_array(const std::string &s)
{
    int n = s.length();

    std::vector<int> order(n);
    std::vector<int> classes(n);

    sort_characters(s, n, order);
    compute_char_classes(s, n, order, classes);
    int L = 1;

    while (L < n)
    {
        order = sort_doubled(n, order, classes, L);
        classes = update_classes(order, classes, L);
        L = 2*L;
    }

    return order;
}

/**
 * Sorts all cyclic rotations of string S with length 1 using counting sort
 *
 * @param order array of order
 * @param S input string
 * @param n length of S
 */
void BWT::sort_characters(const std::string &s, const size_t n, std::vector<int> &order)
{
    std::map<char, int> freq;

    // Creating a frequency table by counting all characters of S.
    for (size_t i = 0; i < n; i++)
        freq[s[i]]++;

    // Starting at the second index, the value of the previous element is added to the next.
    for (auto itr = std::next(freq.begin()); itr != freq.end(); itr++)
        itr->second += std::prev(itr)->second;

    for (int i = static_cast<int>(n - 1); i >= 0; i--)
    {
        // Last character of input text
        char c = s[i];

        // Decrement frequency of c since freq[c] is the positon after the last
        // occurence of C
        freq[c]--;

        // Set the position of freq to i
        order[freq[c]] = i;
    }
}

/**
 * Assigns equivalence classes to each character in S. The equivalence classes
 * helps speed up sorting.
 *
 * @param classes array of size |s|
 * @param order array containing order of sorted suffixes of length 1
 * @param S original input text
 * @param n size of S
 */
void BWT::compute_char_classes(const std::string &s, const size_t n, const std::vector<int> &order, std::vector<int> &classes)
{
    // Since order is sorted, order[0] is the position where the smallest
    // character in S occurs. We therefore initialize this position in classes
    // arrry with equivalence class of 0
    classes[order[0]] = 0;

    // Assign classes
    for (size_t i = 1; i < n; i++)
    {
        // if current is unequal to previous we know that current must
        // be bigger than the previous
        if (s[order[i]] != s[order[i-1]])
            classes[order[i]] = classes[order[i-1]] + 1; // Assign new class
        else // Character is same as previous
            classes[order[i]] = classes[order[i-1]]; // Assign same class as prev char
    }
}

/**
 * Sorts doubled cyclic shifts of T
 *
 * @param s
 * @param n |s|
 * @param order list of sorted suffixes
 * @param classes equivalence classes
 * @param l number of cyclic shifts
 * @return
 */
std::vector<int> BWT::sort_doubled(const size_t n, const std::vector<int> &order, const std::vector<int> &classes, int l)
{
    std::vector<int> freq(n);
    std::vector<int> newOrder(n);

    for (size_t i = 0; i < n; i++)
        freq[classes[i]]++;

    for (size_t j = 1; j < n; j++)
        freq[j] += freq[j-1];

    for (int i = static_cast<int>(n - 1); i >= 0; i--)
    {
        int start = static_cast<int>((order[i] - l + n) % n);
        int cl = classes[start];
        freq[cl]--;
        newOrder[freq[cl]] = start;
    }

    return newOrder;
}

/**
 * Updates classes
 *
 * @param newOrder
 * @param classes
 * @param l
 * @return
 */
std::vector<int> BWT::update_classes(const std::vector<int> &newOrder, const std::vector<int> &classes, const int l)
{
    size_t n = newOrder.size();
    std::vector<int> newClass(n);
    newClass[newOrder[0]] = 0;

    for (size_t i = 1; i < n; i++)
    {
        int curr = newOrder[i];
        int prev = newOrder[i - 1];
        int mid = static_cast<int>((curr + l) % n);
        int midPrev = static_cast<int>((prev + l) % n);

        if (classes[curr] != classes[prev] || classes[mid] != classes[midPrev])
            newClass[curr] = newClass[prev] + 1;
        else
            newClass[curr] = newClass[prev];
    }

    return newClass;
}