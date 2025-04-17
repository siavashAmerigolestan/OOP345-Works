/*/////////////////////////////////////////////////////////////////////////
                               OOP345 Workshop3
Full Name  : Siavash Amerigolestan
Student ID#: 133733220
Email      : samerigolestan@myseneca.ca
Section    : ZBB
Date       : 2024-11-24
/////////////////////////////////////////////////////////////////////////*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <string>
#include "settings.h"
#include "dictionary.h"
using namespace std;

namespace seneca
{
    // default Constructor
    Dictionary::Dictionary() : m_words(nullptr), m_numberOfWords(0) {
    }

    // Constructs a Dictionary object by loading words and their definitions from the specified file.
    Dictionary::Dictionary(const char* filename)
    {
        // Open the specified file using an ifstream object.
        ifstream file(filename);
        // Check if the file opened successfully
        if (file.is_open())
        {
            size_t count = 0;
            string fLine;

            // Iterate through the file to count the total number of lines (words).
            while (getline(file, fLine)) {
                count++;
            }

            //  Clear the EOF flag and reset the file pointer to the beginning for re-reading.
            file.clear();
            file.seekg(0);

            // Allocate memory for the words
            m_words = new Word[count];
            m_numberOfWords = 0;

            // Load words and definitions from the file
            while (getline(file, fLine))
            {
                // Read the file again to populate the words and their definitions.
                size_t firstDelimiter = fLine.find(',');
                size_t secondDelimiter = fLine.find(',', firstDelimiter + 1);

                // Ensure both delimiters are found before proceeding.
                if (firstDelimiter != string::npos && secondDelimiter != string::npos) {
                    // Extract the word, part of speech, and definition
                    string wordString = fLine.substr(0, firstDelimiter);
                    string partOfSpeechString = fLine.substr(firstDelimiter + 1, secondDelimiter - firstDelimiter - 1);
                    string definitionString = fLine.substr(secondDelimiter + 1);

                    //  Assign the extracted values to the current Word structure
                    m_words[m_numberOfWords].word = wordString;
                    m_words[m_numberOfWords].definition = definitionString;
                    m_words[m_numberOfWords].pos = determinePartOfSpeech(partOfSpeechString);
                    m_numberOfWords++;
                }
            }
        }
        else {
            cerr << "Error: Could not open file: " << filename << endl;
        } 
    }

    // Copy constructor 
    Dictionary::Dictionary(const Dictionary& rhs){
        m_words = nullptr;
        *this = rhs;
    }

    // copy assignment operator
    Dictionary& Dictionary::operator=(const Dictionary& rhs){
        if (this != &rhs)
        {
            delete[] m_words;
            m_numberOfWords = rhs.m_numberOfWords;
            m_words = new Word[m_numberOfWords];
            for (size_t i = 0; i < m_numberOfWords; i++)
            {
                m_words[i] = rhs.m_words[i];
            }
        }
        return *this;
    }

    // Move constructor 
    Dictionary::Dictionary(Dictionary&& rhs) noexcept {
         m_words = rhs.m_words;
         m_numberOfWords = rhs.m_numberOfWords;
         rhs.m_words = nullptr;
         rhs.m_numberOfWords = 0;
    }
    
    // Move assignment operator
    Dictionary& Dictionary::operator=(Dictionary&& rhs) noexcept {
         if (this != &rhs) {
             delete[] m_words;
             m_words = rhs.m_words;
             m_numberOfWords = rhs.m_numberOfWords;

             rhs.m_words = nullptr;
             rhs.m_numberOfWords = 0;
         }
         return *this;
    }

    // Destructor
    Dictionary::~Dictionary() {
        delete[] m_words;
    }

    // Search a word in the dictionary
    void Dictionary::searchWord(const char* word) {
        bool isFound = false;
        size_t wordLenght = strlen(word);
        bool searchComplete = false;

        // Iterate through the list of words in the dictionary.
        for (size_t i = 0; i < m_numberOfWords && !searchComplete; i++) {
            if (m_words[i].word == word){
                // Print the word if it's the first occurrence.
                if (!isFound) {
                    cout << m_words[i].word;
                }
                else {
                    // Print spaces for alignment for subsequent definitions.
                    cout << setw(wordLenght) << " ";  
                }

                cout << " - ";

                // Print part of speech if required
                if (g_settings.m_verbose && m_words[i].pos != PartOfSpeech::Unknown) {
                    std::cout << "(" << formatPartOfSpeech(m_words[i].pos) << ") ";
 
                }

                cout << m_words[i].definition << endl;
                isFound = true;

                // If m_show_all is false, stop after the first match
                if (!g_settings.m_show_all) {
                    searchComplete = true;
                }
            }
        }

        // If word is not found, print a message
        if (!isFound) {
            cout << "Word '" << word << "' was not found in the dictionary." << endl;
        }
    }

    // Determines the corresponding PartOfSpeech enum value from a string abbreviation.
    PartOfSpeech Dictionary::determinePartOfSpeech(const string& strPos) {
        if (strPos == "n." || strPos == "n.pl.") {
            return PartOfSpeech::Noun;
        }
        else if (strPos == "adv.") {
            return PartOfSpeech::Adverb;
        }
        else if (strPos == "a.") {
            return PartOfSpeech::Adjective;
        }
        else if (strPos == "v." || strPos == "v. i." || strPos == "v. t." || strPos == "v. t. & i.") {
            return PartOfSpeech::Verb;
        }
        else if (strPos == "prep.") {
            return PartOfSpeech::Preposition;
        }
        else if (strPos == "pron.") {
            return PartOfSpeech::Pronoun;
        }
        else if (strPos == "conj.") {
            return PartOfSpeech::Conjunction;
        }
        else if (strPos == "interj.") {
            return PartOfSpeech::Interjection;
        }
        return PartOfSpeech::Unknown;
    }

    // Returns the string representation of the given PartOfSpeech enum value.
    std::string Dictionary::formatPartOfSpeech(PartOfSpeech pos) const {
        if (pos == PartOfSpeech::Noun) {
            return "noun";
        }
        else if (pos == PartOfSpeech::Pronoun) {
            return "pronoun";
        }
        else if (pos == PartOfSpeech::Adjective) {
            return "adjective";
        }
        else if (pos == PartOfSpeech::Adverb) {
            return "adverb";
        }
        else if (pos == PartOfSpeech::Verb) {
            return "verb";
        }
        else if (pos == PartOfSpeech::Preposition) {
            return "preposition";
        }
        else if (pos == PartOfSpeech::Conjunction) {
            return "conjunction";
        }
        else if (pos == PartOfSpeech::Interjection) {
            return "interjection";
        }
        else {
            return "unknown";
        }
    }
} // namespace seneca



