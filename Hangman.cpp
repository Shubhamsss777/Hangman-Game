‎#include <iostream>
‎#include <string>
‎#include <cstdlib>
‎#include <ctime>
‎#include <fstream>
‎#include <cctype>
‎#include <vector>
‎using namespace std;
‎
‎const int MAX_TRIES = 6;
‎vector<string> dictionary; // stores all words from file
‎
‎// Load all words from dictionary.txt
‎void loadDictionary(string filename) {
‎    ifstream file(filename);
‎    string word;
‎    if (!file) {
‎        cout << "Error: dictionary.txt not found!" << endl;
‎        cout << "Make sure dictionary.txt is in the same folder as this.exe" << endl;
‎        exit(1);
‎    }
‎    while (file >> word) {
‎        // convert to uppercase
‎        for(int i = 0; i < word.length(); i++) {
‎            word[i] = toupper(word[i]);
‎        }
‎        // only add words with length > 2
‎        if(word.length() > 2)
‎            dictionary.push_back(word);
‎    }
‎    file.close();
‎    cout << "Loaded " << dictionary.size() << " words from dictionary!" << endl << endl;
‎}
‎
‎// Draw hangman based on wrong guesses
‎void drawHangman(int tries) {
‎    cout << " +---+" << endl;
‎    cout << " | |" << endl;
‎
‎    if (tries >= 1) cout << " O |" << endl; // Head
‎    else cout << " |" << endl;
‎
‎    if (tries == 2) cout << " | |" << endl; // Body
‎    else if (tries == 3) cout << "/| |" << endl; // Body + 1 arm
‎    else if (tries >= 4) cout << "/|\\ |" << endl; // Body + 2 arms
‎    else cout << " |" << endl;
‎
‎    if (tries == 5) cout << "/ |" << endl; // 1 leg
‎    else if (tries >= 6) cout << "/ \\ |" << endl; // 2 legs
‎    else cout << " |" << endl;
‎
‎    cout << " |" << endl;
‎    cout << "=========" << endl << endl;
‎}
‎
‎// Save results to file
‎void saveData(string playerName, int wins, int losses) {
‎    ofstream file("hangman_results.txt", ios::app);
‎    if (!file) {
‎        cout << "Error saving data!" << endl;
‎        return;
‎    }
‎    file << "Player Name: " << playerName << endl;
‎    file << "Wins: " << wins << endl;
‎    file << "Losses: " << losses << endl;
‎    file << "---------------------------" << endl;
‎    file.close();
‎    cout << "Your game results have been saved to hangman_results.txt!" << endl;
‎}
‎
‎int main() {
‎    srand(time(NULL)); // seed random
‎    loadDictionary("dictionary.txt"); // load words
‎
‎    int winCount = 0;
‎    int loseCount = 0;
‎    char playAgain = 'y';
‎    string playerName;
‎
‎    cout << "=====================" << endl;
‎    cout << " HANGMAN GAME" << endl;
‎    cout << "=====================" << endl;
‎    cout << "Enter your name: ";
‎    cin >> playerName;
‎    cout << endl;
‎
‎    while (playAgain == 'y' || playAgain == 'Y') {
‎        // Pick random word from dictionary
‎        string word = dictionary[rand() % dictionary.size()];
‎        string hiddenWord(word.length(), '-');
‎        string guessedLetters = "";
‎        int tries = 0;
‎        char guess;
‎
‎        cout << "Welcome to Hangman, " << playerName << "!" << endl;
‎        cout << "The word has " << word.length() << " letters." << endl << endl;
‎
‎        while (tries < MAX_TRIES && hiddenWord!= word) {
‎            drawHangman(tries);
‎
‎            cout << "Word: " << hiddenWord << endl;
‎            cout << "Guessed Letters: " << guessedLetters << endl;
‎            cout << "Tries Remaining: " << MAX_TRIES - tries << endl;
‎            cout << "Enter your guess: ";
‎            cin >> guess;
‎            guess = toupper(guess); // make uppercase
‎
‎            // Check if already guessed
‎            if (guessedLetters.find(guess)!= string::npos) {
‎                cout << "You already guessed that letter. Try again." << endl << endl;
‎                continue;
‎            }
‎
‎            guessedLetters += guess;
‎            guessedLetters += " ";
‎
‎            // Check if guess is in word
‎            if (word.find(guess)!= string::npos) {
‎                for (int i = 0; i < word.length(); i++) {
‎                    if (word[i] == guess) {
‎                        hiddenWord[i] = guess;
‎                    }
‎                }
‎                cout << "Correct guess!" << endl << endl;
‎            } else {
‎                tries++;
‎                cout << "Incorrect guess!" << endl << endl;
‎            }
‎        }
‎
‎        drawHangman(tries); // show final state
‎
‎        if (hiddenWord == word) {
‎            cout << "Congratulations! You guessed the word: " << word << endl;
‎            winCount++;
‎        } else {
‎            cout << "Game Over! The word was: " << word << endl;
‎            loseCount++;
‎        }
‎
‎        cout << "Score - Wins: " << winCount << " | Losses: " << loseCount << endl;
‎
‎        char saveChoice;
‎        cout << "Do you want to save your results? (y/n): ";
‎        cin >> saveChoice;
‎        if (saveChoice == 'y' || saveChoice == 'Y') {
‎            saveData(playerName, winCount, loseCount);
‎        }
‎
‎        cout << "Do you want to play again? (y/n): ";
‎        cin >> playAgain;
‎        cout << endl;
‎    }
‎
‎    cout << "Thank you for playing Hangman!" << endl;
‎    return 0;
‎}