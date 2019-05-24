# Assignment 2            


## BWT Encode

The program bwtencode does a bwt transform on the input text, writes the
last colum to a new file and stores some extra positional information of
the records in an auxilary positional information file.


### Suffix Array

The suffix array is computed in O(|S| + |Σ|) where |S| is the length of the input text and |Σ| is the length of the alphabeth.
First all the all the cyclic rotations of S with length 1 is sorted using count sort. Then character classes are assigned to each character in the alphabet of the text S.
This is is repeated for all the cyclic rotations of length 1, 2, 4, 8 etc. until the length of the rotations is bigger than than the text S.


### BWT 

Using the relationship between the Suffix array and the BWT which is that SA[I-1] = L[i]. 
So by subtraction one from each indice of the SA we get the last colum of the BWT transform.


### Positional Information

The auxilary positional file contains a mapping between delimiters in L and T. It is captured with the use of two arrays. One is the lpos array containing position of delimiters in L and the other is the tpos containing positions of delimiters in T.

This information is caputered simply by locating the index of tpos[i] in lpos and storing this index at position i in the auxilary positonal file.


## BWT search

The program bwtsearch takes the last column of a bwt encoded string along with a
file containing positional information as input.


### -m Count 

The count function implements BWT backward search based of the pseudocode shown in the lecture.


### -i print records

The print records function prints the records specified. 

Starting with the index of the first delimiter in the first colum. The previous character of this one is the first character of our decoded record. Meaning the character in the last column of the same row. Using the LF mapping the corresponding character is found in the first column. The last character of this row is added to the beginning of the decoded string. This is reapeated to recover th eoriginal record from last to first character. 

### C table

The c table is implemented as dictionary for easy lookup and creation. It is constructed by first finding the frequency of each character and storing it in a dictionary with char key and unsigned int value. Then each previous freq is added to the freq of the next character. Since the values in the dictionary is sorted, this is the same as countig the number of characters which are lexicographically smaller''

### Occurence function

The occurence for every 10 000th index is precomputed and stored on disk. 

