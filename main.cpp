#include <cctype>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <limits>
#include <string>
#include <vector>
using namespace std;

void intro();
string getAnswer(int lenghtOfWord);
int getNumberOfGuesses();
int getLengthOfWord();
string getUsername();
bool isValidInput(const string &word, const vector<string> &guessedWords,
                  int numberOfLetters);
void game(const string &username, const string &answer, int numberOfGuesses);
void printToFile(const string &playerName, const vector<string> &guessedWords,
                 const vector<string> &guessedWordResults);

/**
 * @brief Get a value from the user using cin
 *
 * @param prompt The prompt that the user will see. You may want to add a new
 * line character
 *
 * @return The value from the user
 */
template <typename T> T input(const char *prompt);

string toLower(const string &input);

bool isAlpha(const string &input);

void clearScreen();

int main() {
    intro();
    int numberOfGuesses = getNumberOfGuesses();
    int lengthOfWord = getLengthOfWord();
    string username = getUsername();
    string answer = getAnswer(lengthOfWord);
    game(username, answer, numberOfGuesses);
    return 0;
#include "dogs.jpg"

    void intro() {
        // TODO: improve these instructions
        cout << "               __" << endl;
        cout << "              / _)" << endl;
        cout << "     _.----._/ /" << endl;
        cout << "    /         /" << endl;
        cout << " __/ (  | (  |" << endl;
        cout << "/__.-'|_|--|_|" << endl;

        cout << "Hello and welcome to Word Dino!" << endl;
        cout << "Your goal is to guess a word." << endl;
        cout << endl;
        cout << "Here are the rules" << endl;
        cout << "If your text turns yellow, your letter is in the word, but it "
                "is "
                "not in the right place"
             << endl;
        cout << "If your text turns green, your letter is in the word and in "
                "the "
                "right place"
             << endl;
        cout << "Have fun!" << endl;
    }
    // This should read the lengthOf word and read the corresponding file (there
    // is only 1 so far which is for 5 letter words)
    string getAnswer(int lengthOfWord) {

        string filename =
            "word-list-" + to_string(lengthOfWord) + "-letter.txt";
        ifstream file(filename);

        // Check if the file is opened successfully
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return "";
        }

        // Count the number of lines in the file
        int numberOfLines = 0;
        string line;
        while (getline(file, line)) {
            numberOfLines++;
        }

        // Check if the file is empty
        if (numberOfLines == 0) {
            cerr << "Error: File is empty." << endl;
            return "";
        }

        // Generate a random number between 1 and the number of lines
        srand(static_cast<unsigned int>(
            time(nullptr))); // Seed the random number generator
        int randomLineNumber = rand() % numberOfLines + 1;

        // Reset the file position to the beginning
        file.clear();
        file.seekg(0, ios::beg);

        // Read the selected word from the file
        int currentLineNumber = 0;
        string targetWord;
        while (getline(file, line)) {
            currentLineNumber++;
            if (currentLineNumber == randomLineNumber) {
                targetWord = line;
                break;
            }
        }

        // Close the file
        file.close();

        // Check if the selected word has the desired length
        if (targetWord.length() == lengthOfWord) {
            return targetWord;
        } else {
            cerr << "Error: Selected word does not have the desired length."
                 << endl;
            return "";
        }
    }

    int getNumberOfGuesses() {
        int guesses;
        while (true) {
            guesses = input<int>("How many guesses would you like? ");

            if (guesses < 1 || guesses > 100) {
                cout << "Please enter a number 1-100" << endl;
                continue;
            }
            break;
        }
        return guesses;
    }

    int getLengthOfWord() {
        int wordLength;
        while (true) {
            wordLength = input<int>("How long would you like the word to be "
                                    "(between 2 and 6 letters)? ");

            if (wordLength < 2 || wordLength > 6) {
                cout << "Please enter a number between 2-6" << endl;
                continue;
            }
            break;
        }
        return wordLength;
    }

    string getUsername() {

        while (true) {
            cout << "Would you like to save data? " << endl;
            cout << "(Y)es" << endl;
            cout << "(N)o" << endl;

            char userInput = input<char>("Please enter a letter: ");

            userInput = tolower(userInput);

            switch (userInput) {
            case 'y':
                break;
            case 'n':
                return "";
            default:
                continue;
            }
            break;
        }

        string username =
            input<string>("Please enter the username you would like to use: ");
        return username;
    }
    // This function should return false if the input is invalid.
    // Return true at the end if all checks pass.
    bool isValidInput(const string &input, const vector<string> &guessedWords,
                      int numberOfLetters) {
        if (input.length() != numberOfLetters) {
            cout << "Input was not the right number of letters. " << endl;
            return false;
        }

        if (!isAlpha(input)) {
            cout << "Your input must use alphabetical characters only. "
                 << endl;
            return false;
        }

        for (string word : guessedWords) {
            if (input == word) {
                cout << "You have already guessed that word. " << endl;
                return false;
            }
        }

        string filename =
            "word-list-" + to_string(numberOfLetters) + "-letter.txt";
        ifstream file(filename);

        // Check if the file is opened successfully
        if (!file.is_open()) {
            cerr << "Error opening file: " << filename << endl;
            return false;
        }

        string line;
        while (getline(file, line)) {
            if (input == line) {
                file.close();
                return true;
            }
        }

        cerr << "Word not found on list" << endl;
        file.close();
        return false;
    }

    void game(const string &username, const string &answer,
              int numberOfGuesses) {

        vector<string> guessedWords;
        vector<string> guessedWordResults;
        int Length = 6;
        string keyboard[] = {
            "q w e r t y u i o p", "                   ", " a s d f g h j k l ",
            "                   ", "  z x c v b n m    ", "                   ",
        };

        int remainingGuesses = numberOfGuesses;

        while (remainingGuesses > 0) {
            clearScreen();

            for (int i = 0; i < guessedWords.size(); i++) {
                cout << guessedWords[i] << endl;
                cout << guessedWordResults[i] << endl;
                cout << endl;
            }

            for (string row : keyboard) {
                cout << row << endl;
            }

            cout << "Remaining guesses: " << remainingGuesses << endl;

            string guess;
            while (true) {
                guess = input<string>("Please enter your guess: ");
                guess = toLower(guess);
                if (!isValidInput(guess, guessedWords, answer.length())) {
                    continue;
                }
                break;
            }
            guessedWords.push_back(guess);

            // Check if the guessed word is correct
            if (guess == answer) {
                cout << "Congratulations! You guessed the word: " << answer
                     << endl;
                break;
            }

            string wordResult = "";
            // Provide feedback on the guessed word
            for (int i = 0; i < guess.length(); ++i) {
                char charResult;

                if (guess[i] == answer[i]) {
                    charResult = 'O'; // Right letter in the right spot

                } else if (answer.find(guess[i]) != string::npos) {
                    charResult = '-'; // Right letter in the wrong spot

                } else {
                    charResult = 'X'; // Wrong letter
                }
                wordResult += charResult;

                for (int e = 0; e < Length; e++) {
                    if (keyboard[e].find(guess[i]) != string::npos) {
                        int pos = keyboard[e].find(guess[i]);

                        // Skip letter is already correct.
                        if (keyboard[e + 1][pos] == 'O') {
                            continue;
                        }
                        keyboard[e + 1][pos] = charResult;
                    }
                }
            }

            guessedWordResults.push_back(wordResult);

            remainingGuesses -= 1;
        }

        if (remainingGuesses == 0) {
            cerr << "Sorry, you've run out of guesses. The word was: " << answer
                 << endl;
        }

        printToFile(username, guessedWords, guessedWordResults);
    }

    void printToFile(const string &username, const vector<string> &guessedWords,
                     const vector<string> &guessedWordResults) {

        if (username == "") {
            return;
        }

        string fileName = username + ".txt";

        fstream file;
        file.open(fileName, fstream::in | fstream::out | fstream::app);

        string contents;
        if (!(file >> contents)) {
            file.close();
            file.open(fileName, fstream::in | fstream::out | fstream::trunc);

            file << "               __" << endl;
            file << "              / _)" << endl;
            file << "     _.----._/ /" << endl;
            file << "    /         /" << endl;
            file << " __/ (  | (  |" << endl;
            file << "/__.-'|_|--|_|" << endl;
            file << endl;
            file << "Word Dino results for " << username << endl;
            file << endl;
        }

        file << endl;

        time_t currentTime = time(0);

        file << ctime(&currentTime) << endl;

        for (int i = 0; i < guessedWords.size(); i++) {
            file << guessedWords[i] << endl;
            file << guessedWordResults[i] << endl;
            file << endl;
        }

        cout << "Data saved in " << fileName << endl;
        file.close();
    }

    template <typename T> T input(const char *prompt) {
        T input;

        // Loop while input is invalid
        while (true) {
            cout << prompt;
            cin >> input;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cerr << "Invalid Input" << endl;
                continue;
            }
            break;
        }
        return input;
    }

    string toLower(const string &input) {
        string output = "";
        for (char character : input) {
            output += tolower(character);
        }
        return output;
    }

    bool isAlpha(const string &input) {
        bool output = true;
        for (char character : input) {
            if (!isalpha(character)) {
                output = false;
            }
        }
        return output;
    }

#ifdef __unix__
    void clearScreen() { system("clear"); }
#endif

#ifdef WINDOWS
    void clearScreen() { system("cls"); }
#endif
