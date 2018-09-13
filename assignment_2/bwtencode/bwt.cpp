//
// Created by Olav Markus Sjursoe on 7/09/18.
//

#include <vector>
#include <algorithm>
#include <numeric>
#include "bwt.h"
#include <iostream>

void BWT::bucket_sort(int *a, const int n)
{
    int i, j, k, buckets[10];

    for (int i = 0; i < 10; i++)
        buckets[i] = 0;

    for (i = 0; i < n; ++i)
        ++buckets[a[i]];

    for (i = 0, j = 0; j < 10; ++j)
        for (k = buckets[j]; k > 0; --k)
            a[i++] = j;
}

std::vector<int> BWT::compute_suffix_array(const std::string &s)
{
    const int n = s.size();
    std::vector<int> suffixArray(n);

    // Fills the vector with integers in the range of [0, n-1]
    std::iota (std::begin(suffixArray), std::end(suffixArray), 0);

    // Sorts the vector of indexes lexicographically, without actually
    // storing the suffixes.
    std::sort(suffixArray.begin(), suffixArray.end(),
              [&s, &n](int x, int y)
              {
                  return s.substr(x, n-x) < s.substr(y, n-y);
              });


    return suffixArray;

    /*
  int bwtArray[n];

  // creates an array of bwt indexes by subtracting 1 from each
  // index of the suffix array.
  for (int i = 0; i < vec.size(); i++)
  {
      bwtArray[i] = vec[i] - 1;
      if (bwtArray[i] < 0)
          bwtArray[i] = n - 1;

  }

  std::string bwt;

  // Creates the bwt from the suffix array
  for (int i = 0; i < n; i++)
  {
      bwt.append(s.substr(bwtArray[i], 1));
  }



    return bwt;
       */
}
