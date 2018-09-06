The huffman tree consists of nodes containing a character and frequency, along with a pointer to left and right child.
To construct the tree, a node is created for every character and added to a minimum heap which i have implemented using std::priority:queue.
The two leaf nodes with the smallest frequency are taken out, a parent node is created with the sum of their frequency, the new node is added to the minheap.
THis is repeated until the tree is built.


The format of the header is pretty simple. It is just the frequency table delimited by comma.
The header is padded so that the length is always 1024 bits.

Search works by decoding a chunk of data, and iterating over the chunk one character at the time.
I have tested that overlapping search terms are caught. My implementation is a bit rushed,
there are cases where it will not work, ex. when a word is split in to two chunks.