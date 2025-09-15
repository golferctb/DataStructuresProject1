string sentences[];

class Text2Compress {
    private:
    protected:
        int _seq[200000]; // stores the current sequence
        int _length; // length of sequence
        int _freq[640][640]; // static matrix 128+k by 128+k
        int _rules[512][3]; // merge rules: a b -> z
        int _ruleCount; // number of rules learned
        int _maxSymbol; // highest assigned symbol ID
    public:
        Text2Compress();
        void initialize(int k, int lines) { // read input text
            for(int i = 0; i < k; i++) { //TODO: Write iteration function (just outside loop)
                for(char c : )
            }
        }
        void train(int k); // perform k merges
        void encode(); // apply learned merges
        void decode(); // optional: expand compressed form
        void displaySequence(); // print current sequence
        void displayRules(); // print learned rules
};

#include <iostream>
#include <string>
using namespace std;
int main() {
    int k, numLines;
    // First row: k and number of lines of input
    cin >> k >> numLines;
    cin.ignore(); // skip newline
    // Step 1: Read lines of input text
    
    // Store each character’s ASCII code (0–127) into the sequence array
    // Step 2: Create a Text2Compress object
    Text2Compress compressor;
    // Step 3: Train with k merges
    compressor.train(k);
    // Step 4: Display the learned rules
    compressor.displayRules();
    // Step 5: Display the compressed sequence
    compressor.displaySequence();
    // Step 6: Process decompression lines (triplets + sequence)
    // You will write code to handle that part
    return 0;
}