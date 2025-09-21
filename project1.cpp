#include <iostream>
#include <string>
using namespace std;

class Text2Compress {
    private:
        int numOfMerges;
    protected:
        int _seq[10000]; // stores the current sequence
        int _length; // length of sequence
        int _freq[500][500]; // static matrix 128+k by 128+k
        int _rules[512][3]; // merge rules: a b -> z
        int _ruleCount; // number of rules learned
        int _maxSymbol; // highest assigned symbol ID
    public:
        Text2Compress() {
            _ruleCount = 0;
            _maxSymbol = 127;
        }
        void initialize(int k, int lines) { // read input text
            int zerout = _maxSymbol + k;
            for(int i = 0; i <= zerout; ++i) { // is <= to ensure it is 128+k, not 127+k.
                for(int j = 0; j <= zerout; ++j) {
                    _freq[i][j] = 1;
                }
            }
            string input; // Input string for text to be entered.
            _length = 0; // Sets length to 0.
            for(int i = 0; i < lines; ++i) { // Loops through the sequence adds each character to _seq.
                getline(cin, input); // Reads in the input from a given line.
                for(char c : input) { // Goes through each character and adds it to the sequence.
                    _seq[_length] = c; // Assigns character to iteration in loop.
                    _length++; // Increments the _length to store in the next loop.
                }
            }
            for (int i = 0; i < _length - 1; ++i) {
                int first = _seq[i]; // Looks at the first character in pair.
                int second = _seq[i + 1]; // Looks at second character in pair.
                if (first >= 0 && first <= _maxSymbol && second >= 0 && second <= _maxSymbol) { // Ranges need to be between 0 and the max length of sequence.
                    _freq[first][second]++; // Increments the value 
                }
            }
        }
        void train(int k) { // perform k merges
            // First, ensure that the rule column size matches the input k, to make sure no errors occur later on.
            // 2) Increment through each element of the array, applying the rule that that matches the outer loop
            // Ex. Through outer loop, increment through each rule, using i, j, etc. Through the inner loop, perform the merges (see documentation from TA).
            // Use the encode 
            numOfMerges = k;
            



            for(int mergeCount = 0; mergeCount < k; ++mergeCount) {
                // Finds the greatest frequency of a pair.
                int maxLim = _maxSymbol + 1;
                int best = 0, firstBest = 0, secondBest = 0;
                for (int first = 0; first < maxLim; ++first) {
                    for (int second = 0; second < maxLim; ++second) {
                        if (_freq[first][second] > best) {
                            best = _freq[first][second];
                            firstBest = first;
                            secondBest = second;
                        }
                    }
                }

                // If there are no more "best" pairs. We can't train it anymore!
                if(best == 0) break;
                int newSym = ++_maxSymbol; // newSym is assignment to _maxSymbol + 1 to add new symbol to matrix.
                _rules[_ruleCount][0] = firstBest; // Adds the first number of pair to the rules matrix.
                _rules[_ruleCount][1] = secondBest; // Adds the second number of pair to the rules matrix.
                _rules[_ruleCount][2] = newSym; // Adds the new "symbol" or number to 
                _ruleCount++; // Increments ruleCount after first set of rules is assigned.

                int write = 0; // This is a placeholder for an int that we will write.
                for (int read = 0; read < _length; ++read) {
                    if (read + 1 < _length
                        && _seq[read]   == firstBest
                        && _seq[read+1] == secondBest)
                    {
                        _seq[write] = newSym;
                        write++; // Increases the write variable to look at next line.
                        read++;   // skip the second value in pair
                    } else {
                    _seq[write] = _seq[read];
                    write++;
                    }
                _length = write; // Length will be assigned where write ends (since the array is shortened.)
                }
            }  
        }
        void encode() { // apply learned merges
            for (int rule = 0; rule < _ruleCount; ++rule) {
                int a = _rules[rule][0];
                int b = _rules[rule][1];
                int z = _rules[rule][2];

                int write = 0;
                for (int read = 0; read < _length; ++read) {
                    if (read + 1 < _length
                        && _seq[read]   == a
                        && _seq[read+1] == b)
                    {
                        _seq[write++] = z;
                        read++;
                    } else {
                        _seq[write++] = _seq[read];
                    }
                }
                _length = write;
            }
        }
        void decode(); // optional: expand compressed form
        void displaySequence() { // print current sequence
            cout << "[";
            for(int i = 0; i <= _length - 1; ++i) {
                cout << _seq[i] << ",";
            }
            cout << "]" << endl;
        }
        void displayRules() { // print learned rules
            for (int i = 0; i < _ruleCount; ++i) {
                cout << _rules[i][0] << ' ' << _rules[i][1] << ' ' << _rules[i][2] << '\n';
            }
        }
        ~Text2Compress() {
            cout << "Object deleted!" << endl; // Object deleted
        }
};

int main() {
    int k, numLines;
    // First row: k and number of lines of input
    cin >> k >> numLines;
    while (cin.peek() == '\r' || cin.peek() == '\n') {
        cin.get(); // eat carriage returns and newlines
    }
    // Step 2: Create a Text2Compress object
    Text2Compress compressor;
    // Step 1: Read lines of input text
    // Store each character127) into the sequence array
    compressor.initialize(k, numLines);
    compressor.displaySequence();
    // Step 3: Train with k merges
    compressor.train(k);
    // Step 4: Display the learned rules
    cout << "Rules learned from Compression:" << endl;
    compressor.displayRules();
    // Step 5: Display the compressed sequence
    cout << "Compressed sequence:" << endl;
    compressor.displaySequence();
    // Step 6: Process decompression lines (triplets + sequence)
    // Step7: print the compressed text
    cout << "Decompressed Text:" << endl;
    // You will write code to handle that part
    return 0;
}