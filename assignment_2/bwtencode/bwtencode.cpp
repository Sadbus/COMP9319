#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cstring>
#include "bwt.h"
#include "encoder.h"

struct suffix
{
    int index;
    int rank[2];
};

int *buildSuffixArray(char *txt, int n)
{
    struct suffix suffixes[n];

    for (int i = 0; i < n; ++i)
    {
        suffixes[i].index = i;
        suffixes[i].rank[0] = txt[i] - 'a';
        suffixes[i].rank[1] = ((i+1) < n)? (txt[i + 1] - 'a'): -1;
    }

    std::sort(suffixes, suffixes+n,
              [](struct suffix a, struct suffix b)
              {
                  return (a.rank[0] == b.rank[0])? (a.rank[1] < b.rank[1] ?1: 0):
                         (a.rank[0] < b.rank[0] ?1: 0);
              });

    int ind[n];

    for (int k = 4; k < 2*n; k = k*2) {
        int rank = 0;
        int prev_rank = suffixes[0].rank[0];
        suffixes[0].rank[0] = rank;
        ind[suffixes[0].index] = 0;

        for (int i = 1; i < n; ++i) {
            if (suffixes[i].rank[0] == prev_rank &&
                suffixes[i].rank[1] == suffixes[i - 1].rank[1]) {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = rank;
            } else {
                prev_rank = suffixes[i].rank[0];
                suffixes[i].rank[0] = ++rank;
            }
            ind[suffixes[i].index] = i;
        }

        for (int i = 0; i < n; ++i) {
            int nextIndex = suffixes[i].index + k / 2;
            suffixes[i].rank[1] = (nextIndex < n) ?
                                  suffixes[ind[nextIndex]].rank[0] : -1;
        }

        std::sort(suffixes, suffixes + n,
                  [](struct suffix a, struct suffix b) {
                      return (a.rank[0] == b.rank[0]) ? (a.rank[1] < b.rank[1] ? 1 : 0) :
                             (a.rank[0] < b.rank[0] ? 1 : 0);
                  });
    }

    int *suffixArr = new int[n];
    for (int i = 0; i < n; ++i)
        suffixArr[i] = suffixes[i].index;

    return suffixArr;


}

void printArr(int arr[], int n)
{
    for (int i = 0; i < n; i++)
        std::cout << arr[i] << " ";
    std::cout << std::endl;
}

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

int main(int argc, char* argv[])
{
    if (argc < 5)
    {
        std::cerr << "Usage: " << argv[0] << " 'delimiter' tmp_folder input_file output_file" << std::endl;
        exit(1);
    }

    std::string str = argv[1];
    char d = '0';

    if (str.find("\\n") != std::string::npos)
        d = '\n';
    else
        d = str.at(3);


    Encoder encoder;
    encoder.encode(d, argv[2], argv[3], argv[4]);


    /*
    std::string str = get_file_contents(argv[3]);

    char txt[str.size()];
    std::strcpy(txt, str.c_str());
    int n = strlen(txt);
    int *suffixArr = buildSuffixArray(txt,  n);
    std::cout << "Following is suffix array for " << txt << std::endl;
    printArr(suffixArr, n);

    int bwtArr[n];
    for (int i = 0; i < n; i++)
    {
        bwtArr[i] = suffixArr[i] - 1;
        if (bwtArr[i] == -1)
            bwtArr[i] = n;
    }

    printArr(bwtArr, n);

    for (int i = 0; i < n; i++)
        std::cout << txt[bwtArr[i]];
    */

    return 0;
}