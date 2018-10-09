BWT Encode

The program bwtencode does a bwt transform on the input text, writes the
last colum to a new file and stores some extra positional information of
the records in a

Suffix Array

The suffix array is computed in O(|S| + ||) where |S| is the length
of the input text and || is the length of the alphabeth.

First all the all the cyclic rotations of S with length 1 is sorted
using count sort. Then character classes are assigned to each character
in the alphabet of the text S.

This is is repeated for all the cyclic rotations of length 1, 2, 4, 8 etc.
until the length of the rotations is bigger than than the text S.


Positional Information

The positional information simply contains the indexes (zero based)
of the delimiters in the orginal text.


BWT search

The program bwtsearch takes the last colum of a bwt encoded string along with a
file containing positional information as input.

Count

Locate

Display

List identifiers
