// prog3WhichLangMacbeth.cpp
//    Use letter frequency counts to determine what language text is in.
//
// Author: Dhyan Patel
// Date: Oct 17, 2018
// Class: CS 141, Fall 2018
// Language: C++
//
// Translations of Macbeth were created online using Google translate, starting with the
// English version at http://shakespeare.mit.edu/macbeth/full.html
// To trigger the translation option, I went to the Chrome browser / Settings / Language
// option and changed the default language, which triggered showing the translation option
// for the English Macbeth page when it was displayed.  The translated text was then
// copy/pasted into a text file and saved.  The texts are stored using the multi-byte
// UTF-8 format, explained at https://en.wikipedia.org/wiki/UTF-8, though here we are
// not attempting to count more than the first 128 alphabetical characters.


// Your code should go here
#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
#include <cstdlib>
#include <algorithm>
#include <limits>
#define LIMIT 26

using namespace std;

void swap_numbers(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubble_sort(int arr[LIMIT][2], int N){
    for (int i = 0 ; i < N-1 ; i++){
        for (int j = 0 ; j < N - i - 1; j++){
            if (arr[j][0] < arr[j+1][0]){
                swap_numbers(&arr[j][0], &arr[j+1][0]);
                swap_numbers(&arr[j][1], &arr[j+1][1]);
            }
        }
    }
}

void getUser(string paragraph, int lettersArray[LIMIT][2]){
    char c = ' ';
    int i;

    for (i = 0; i<LIMIT; i++){
        lettersArray[i][0] = 0;
        lettersArray[i][1] = (char)('A' + i);
    }

    for (char& c : paragraph){
        if (isalpha(c)){
            c = toupper(c);
            lettersArray[c-'A'][0]++;
        }
    }

    for (int i; i < LIMIT; i++){
        cout << (char)(i+'A') << ":";
        cout << lettersArray[i][0] << " ";
    }
    cout << "\n";
}

void getFrequency(string fileName, int lettersArray[LIMIT][2]){
    ifstream inputFileStream;  // declare the input file stream
    //int lettersArray[LIMIT];  // count occurrences of characters
    char c = ' ';              // input character
    int i;                     // loop counter


    // open input file and verify
    inputFileStream.open( fileName.c_str());   // Convert C++ string to expected C-style string
    if( !inputFileStream.is_open()) {
        cout << "Could not find input file.  Exiting..." << endl;
        exit( -1);
    }

    // initialize lettersArray count values
    for (i=0; i<LIMIT; i++) {
        lettersArray[i][0] = 0;
    }

    for (i=0; i<LIMIT; i++){
        lettersArray[i][1] = (char)('A' + i);
    }

    // Process input one character at at time, echoing input
    // Note that the input skips leading spaces, which is why we don't see
    // them as part of the output.
    //cout << "Reading characters from a file... " << endl;
    while(inputFileStream >> c) {
        // convert alphabetic input characters to upper case
        if(isalpha(c)) {
            c = toupper(c);
            lettersArray[c-'A'][0]++; // update letter count, using the character as the index
            // cout << c << " ";    // Takes too long to display when enabled
        }
    }
    inputFileStream.close();
}

int diffCheck(int language[LIMIT][2], int user[LIMIT][2]){
    int diff = 0;
    for (int i = 0; i < LIMIT; i++){
        int userPos,langPos;
        for (int u = 0; u < LIMIT; u++){
            //cout << "user " << (char)user[i][1] << " language " << language[u][1] << endl;
            if (user[i][1] == language[u][1]){
                if (i - u > 5){
                    diff += i - u;
                }
                break;
            }
        }
    }
    return diff;

}

int main()
{
    cout << "Program 3: Which Language\n"
            "  \n"
            "Select from the following stages of output to display:  \n"
            "   1. Letter frequency counts                           \n"
            "   2. Letter frequency order                            \n"
            "   3. Get user input and display frequency counts       \n"
            "   4. Get user input, display frequency counts, and display language \n"
            "   0. Exit the program    \n"
            "Your choice --> ";

    string fileNames[] = {"MacbethEnglish.txt", "MacbethFinnish.txt",
                          "MacbethFrench.txt", "MacbethGerman.txt",
                          "MacbethHungarian.txt", "MacbethItalian.txt",
                          "MacbethPortuguese.txt", "MacbethSpanish.txt"};
    int choice;

    cin >> choice;
    cout << choice << endl;

    int english[LIMIT][2];
    int finnish[LIMIT][2];
    int french[LIMIT][2];
    int german[LIMIT][2];
    int hungarian[LIMIT][2];
    int italian[LIMIT][2];
    int portuguese[LIMIT][2];
    int spanish[LIMIT][2];
    int userLang[LIMIT][2];

    if (choice == 1 || choice == 3 || choice == 4){
        getFrequency(fileNames[0], english);
        getFrequency(fileNames[1], finnish);
        getFrequency(fileNames[2], french);
        getFrequency(fileNames[3], german);
        getFrequency(fileNames[4], hungarian);
        getFrequency(fileNames[5], italian);
        getFrequency(fileNames[6], portuguese);
        getFrequency(fileNames[7], spanish);


        cout << "\nLetter Frequency Counts:" << endl;
        cout << "  " << setw(6) << "Engl";
        cout << setw(6) << "Finn";
        cout << setw(6) << "Fren";
        cout << setw(6) << "Germ";
        cout << setw(6) << "Hung";
        cout << setw(6) << "Ital";
        cout << setw(6) << "Port";
        cout << setw(6) << "Span" << endl;

        for (int i = 0; i < LIMIT; i++){
            cout << (char)(i+'A') << ":";
            cout << setw(6) << english[i][0];
            cout << setw(6) << finnish[i][0];
            cout << setw(6) << french[i][0];
            cout << setw(6) << german[i][0];
            cout << setw(6) << hungarian[i][0];
            cout << setw(6) << italian[i][0];
            cout << setw(6) << portuguese[i][0];
            cout << setw(6) << spanish[i][0] << endl;
        }
    }
    if (choice == 2 || choice == 3 || choice == 4) {
        bubble_sort(english, LIMIT);
        bubble_sort(finnish, LIMIT);
        bubble_sort(french, LIMIT);
        bubble_sort(german, LIMIT);
        bubble_sort(hungarian, LIMIT);
        bubble_sort(italian, LIMIT);
        bubble_sort(portuguese, LIMIT);
        bubble_sort(spanish, LIMIT);


        cout << "\nLetter Frequency Order:" << endl;
        cout << "  " << setw(6) << "Engl";
        cout << setw(6) << "Finn";
        cout << setw(6) << "Fren";
        cout << setw(6) << "Germ";
        cout << setw(6) << "Hung";
        cout << setw(6) << "Ital";
        cout << setw(6) << "Port";
        cout << setw(6) << "Span" << endl;

        for (int i = 0; i < LIMIT; i++) {
            cout << setw(6) << (char) english[i][1];
            cout << setw(6) << (char) finnish[i][1];
            cout << setw(6) << (char) french[i][1];
            cout << setw(6) << (char) german[i][1];
            cout << setw(6) << (char) hungarian[i][1];
            cout << setw(6) << (char) italian[i][1];
            cout << setw(6) << (char) portuguese[i][1];
            cout << setw(6) << (char) spanish[i][1] << endl;
        }
    }

    if (choice == 3 || choice == 4){
        cout << "Copy and paste a paragraph of text to be analyzed, followed by ^z (PC) or ^d (Mac): "<< endl;

        string paragraph;
        string tempUserInput;
        while (cin >> tempUserInput) {
            paragraph = paragraph + tempUserInput;
        }
        cout << endl;
        getUser(paragraph,userLang);
        bubble_sort(userLang, LIMIT);
        cout << endl;

        cout << "Letter Frequency Order:" << endl;
        cout << "  " << setw(6) << "Engl";
        cout << setw(6) << "Finn";
        cout << setw(6) << "Fren";
        cout << setw(6) << "Germ";
        cout << setw(6) << "Hung";
        cout << setw(6) << "Ital";
        cout << setw(6) << "Port";
        cout << setw(6) << "Span";
        cout << setw(6) << "User" << endl;


        for (int i = 0; i < LIMIT; i++){
            cout << setw(6) << (char)english[i][1];
            cout << setw(6) << (char)finnish[i][1];
            cout << setw(6) << (char)french[i][1];
            cout << setw(6) << (char)german[i][1];
            cout << setw(6) << (char)hungarian[i][1];
            cout << setw(6) << (char)italian[i][1];
            cout << setw(6) << (char)portuguese[i][1];
            cout << setw(6) << (char)spanish[i][1];
            cout << setw(6) << (char)userLang[i][1] << endl;
        }
    }
    if (choice == 4){
        int differences[8] = {diffCheck(english, userLang),
                              diffCheck(finnish, userLang),
                              diffCheck(french, userLang),
                              diffCheck(german, userLang),
                              diffCheck(hungarian, userLang),
                              diffCheck(italian, userLang),
                              diffCheck(portuguese, userLang),
                              diffCheck(spanish, userLang)};
        string languageNames[8] = {"English",
                                   "Finnish",
                                   "French",
                                   "German",
                                   "Hungarian",
                                   "Italian",
                                   "Portuguese",
                                   "Spanish"};

        int max = differences[0];
        string language = languageNames[0];
        for (int i = 0; i < 8; i++){
            //cout << "Language " << languageNames[i] << " Number " << differences[i] << endl;
            if (differences[i] < max){
                max = differences[i];
                language = languageNames[i];
            }
        }

        cout << "This is in " << language << endl;
    }


    return 0;
}