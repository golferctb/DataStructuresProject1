#include <iostream>
#include <string>
using namespace std;

class Text2Compress {
    private:
        int numSentences;
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
                    _freq[i][j] = 0;
                }
            }
            string input; // Input string for text to be entered.
            _length = 0; // Sets length to 0.
            for(int i = 0; i < lines; ++i) {
                getline(cin, input); // Reads in the input from a given line.
                for(char c : input) { // Goes through each character and adds it to the sequence.
                    _seq[_length] = c;
                    _length++;
                }
            }
            for (int i = 0; i < _length - 1; ++i) {
                int first = _seq[i]; // Looks at the first character in pair.
                int second = _seq[i + 1]; // Looks at second character in pair.
                if (first >= 0 && first <= _maxSymbol && second >= 0 && second <= _maxSymbol) { // Ranges need to be between 0 and the max length of sequence.
                    _freq[first][second]++;
                }
            }
            // Debugging. Delete this loop.
            for(int i = 0; i < 127; ++i) {
                for(int j = 0; j < 127; ++j) {
                    if(_freq[i][j] > 0) {
                        cout << _freq[i][j] << endl;
                    }
                }
            }
            return;
        }
        void train(int k) { // perform k merges
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
        }
        void encode(); // apply learned merges
        void decode(); // optional: expand compressed form
        void displaySequence() { // print current sequence
            cout << "[";
            for(int i = 0; i <= _length - 1; ++i) {
                cout << _seq[i] << " " << endl;
            }
            cout << "]";
        }
        void displayRules() { // print learned rules
            cout << "a b -> z" << endl; //TODO: Write this method.
        }
};

int main() {
    int k, numLines; 
    // First row: k and number of lines of input
    cin >> k >> numLines;
    cin.ignore(); // skip newline
    // Step 1: Read lines of input text
    // Store each character’s ASCII code (0–127) into the sequence array
    // Step 2: Create a Text2Compress object
    Text2Compress compressor;
    compressor.initialize(k, numLines);
    // Step 3: Train with k merges
    //TODO: compressor.train(k);
    // Step 4: Display the learned rules
    // TODO: compressor.displayRules();
    // Step 5: Display the compressed sequence
    // TODO: compressor.displaySequence();
    // Step 6: Process decompression lines (triplets + sequence)
    // You will write code to handle that part
    return 0;
}