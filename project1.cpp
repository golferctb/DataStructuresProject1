#include <iostream>
#include <string>
using namespace std;

class Text2Compress {
    private:
        int numOfMerges;
        void resetRules() { // Resets the rules sequence.
            for(int i = 0; i < 3; i++) {
                for(int j = 0; j < 512; j++) {
                    _rules[i][j] = 0;
                }
            }
        }
        void resetSeq() { // Zeros out the _seq array.
            for(int i = 0; i < _length; i++) {
                _seq[i] = 0;
            }
        }
        void shiftRight(int index) { // Shifts all the elements in the _seq array right that are right of the index.
            for(int i = _length; i >= index; --i) {
                _seq[i + 1] = _seq[i];
                _length++;
            }
        }
        void shiftLeft(int index) { // Shifts all the elements in the _seq array left that are right of the index.
            for (int i = index; i < _length - 1; ++i) {
                _seq[i] = _seq[i + 1];
            }
            --_length;
        }
        void printDecompressedText() {
            for(int i = 0; i < _length; ++i) {
                cout << char(_seq[i]);
            }
        }   
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
            _maxSymbol = 127; // There are 127 possible ASCII values.
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
                    if(int(c) > 127) {
                        cerr << "Character MUST be alphabetic!!" << endl;
                    }
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
            for(int mergeCount = 0; mergeCount < k; ++mergeCount) { // Finds the greatest frequency of a pair.
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
                
                displayRules();

                for(int rule = 0; rule < _ruleCount; ++rule) { // Loops through the matrix array by row and adds the z value to replace and "a" and "b" values.
                    for(int i = 0; i < _length; i++) {
                        if(_seq[i] == firstBest && _seq[i + 1] == secondBest) {
                            shiftLeft(i);
                            _seq[i] = newSym;
                        }
                    }
                }
            }  
        }
        void encode() { // apply learned merges
            for (int rule = 0; rule < _ruleCount; ++rule) {
                int a = _rules[rule][0]; // Sets the corresponding "a" in the rule.
                int b = _rules[rule][1]; // Sets the corresponding "b" in the rule.
                int z = _rules[rule][2]; // Sets the corresponding "z" in the rule.

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
        void decode() { // Decodes sequence.
            // Zero out _rules matrix
            resetRules();
            cin >> _ruleCount;

            for(int rule = 0; rule < _ruleCount; rule++) { // Adds each of the rules in the _rules matrix.
                int firstNum, secondNum, newNum;
                cin >> firstNum >> secondNum >> newNum;
                _rules[rule][0] = firstNum;
                _rules[rule][1] = secondNum;
                _rules[rule][2] = newNum;
            }
            
            resetSeq();
            _length = 0; // Sets length to 0.
            for(int iter = 0; iter < 10000; iter++) {
                if(cin.fail()) break;
                int number;
                cin >> number;
                _seq[iter] = number;
                _length++;
            }
            _length--;

            for(int rule = 0; rule < _ruleCount; rule++) { // Increments through the rules to decompress.
                int dataChange = _rules[rule][2];
                for(int seqIter = 0; seqIter < _length; ++seqIter) { // Iterates through the sequence, applying the specific code.
                    if(_seq[seqIter] == dataChange) {
                        shiftRight(seqIter);
                        _seq[seqIter] = _rules[rule][0];
                        _seq[seqIter + 1] = _rules[rule][1];
                    }
                }
            }
            printDecompressedText();
        }
        void displaySequence() { // print current sequence
            for(int i = 0; i <= _length; ++i) {
                cout << _seq[i] << " ";
            }
            cout << endl;
        }
        void displayRules() { // print learned rules
            for (int i = 0; i < _ruleCount; ++i) {
                cout << _rules[i][0] << ' ' << _rules[i][1] << ' ' << _rules[i][2] << '\n';
            }
        }
        ~Text2Compress() {}
};

int main() {
    int k, numLines;
    // First row: k and number of lines of input
    cin >> k >> numLines;
    if(k <= 0 || numLines <= 0) {
        cerr << "Invalid inputs!" << endl;
    }
    while (cin.peek() == '\r' || cin.peek() == '\n') {
        cin.get(); // eat carriage returns and newlines
    }
    // Step 2: Create a Text2Compress object
    Text2Compress compressor;
    // Step 1: Read lines of input text
    // Store each character127) into the sequence array
    compressor.initialize(k, numLines);
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
    compressor.decode();
    return 0;
}