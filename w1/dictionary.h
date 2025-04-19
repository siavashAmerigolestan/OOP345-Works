/*/////////////////////////////////////////////////////////////////////////
				  OOP345 Workshop1
Full Name  : Siavash Amerigolestan
Student ID#: 133733220
Email      : samerigolestan@myseneca.ca
Section    : ZBB
Date       : 2024-10-01
Authenticity Declaration:
I have done all the coding by myself and only copied the code that my
professor provided to complete my workshops and assignments.
/////////////////////////////////////////////////////////////////////////*/

#ifndef SENECA_DICTIONARY_H
#define SENECA_DICTIONARY_H

#include <string>
namespace seneca
{
	enum class PartOfSpeech
	{
		Unknown,
		Noun,
		Pronoun,
		Adjective,
		Adverb,
		Verb,
		Preposition,
		Conjunction,
		Interjection,
	};

	struct Word
	{
		std::string word{};
		std::string definition{};
		PartOfSpeech pos = PartOfSpeech::Unknown;
	};

	class Dictionary
	{
		Word* m_words{ nullptr };  
		size_t m_numberOfWords = 0;


	public:
		// default Constructor
		Dictionary();

		// Constructs a Dictionary object by loading words and their definitions from the specified file.
		Dictionary(const char* filename);

		// Copy constructor 
		Dictionary(const Dictionary& rhs);

		// copy assignment operator
		Dictionary& operator=(const Dictionary& rhs);

		// Move constructor 
		Dictionary(Dictionary&& rhs) noexcept;

		// Move assignment operator
		Dictionary& operator=(Dictionary&& rhs) noexcept;

		// Destructor
		virtual ~Dictionary();

		// Search a word in the dictionary
		void searchWord(const char* word);

		// Determines the corresponding PartOfSpeech enum value from a string abbreviation.
		PartOfSpeech determinePartOfSpeech(const std::string& strPos);

		// Returns the string representation of the given PartOfSpeech enum value.
		std::string formatPartOfSpeech(PartOfSpeech pos) const;
	};
}

#endif
