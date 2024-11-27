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
#include <sstream>
#include "spellChecker.h"

namespace seneca {
	
	SpellChecker::SpellChecker(const char* filename) {
		std::ifstream file(filename);
		if (!file) {
			throw "Bad file name!";
		}
		std::string line;
		size_t i = 0;
		while (std::getline(file, line) && i < 6) {
			std::istringstream iss(line);
			iss >> m_badWords[i] >> m_goodWords[i];
			++i;
		}
	}

	void SpellChecker::operator()(std::string& text) {
		for (size_t i = 0; i < 6; i++) {
			size_t pos = 0;
			while ((pos = text.find(m_badWords[i], pos)) != std::string::npos) {
				text.replace(pos, m_badWords[i].length(), m_goodWords[i]);
				m_replaces[i]++;
				pos += m_goodWords[i].length();
			}
		}
	}

	void SpellChecker::showStatistics(std::ostream& out) const {
		out << "Spellchecker Statistics" << std::endl;
		for (int i = 0; i < 6; i++) {
			out << std::right << std::setw(15) << m_badWords[i] << ": " << m_replaces[i] << " replacements" << std::endl;
		}
	}
}