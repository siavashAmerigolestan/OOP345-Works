/*////////////////////////////////////////////////////////////////////////////
							   OOP345 Workshop4-3
Full Name  : Siavash Amerigolestan
Student ID#: 133733220
Email      : samerigolestan@myseneca.ca
Section    : ZBB
Date       : 2024-12-10
Authenticity Declaration:
I declare that this submission is the result of my own work and I only copied
the code that my professor provided to complete my workshops and assignments.
This submitted piece of work has not been shared with any other student or 
3rd party content provider.
////////////////////////////////////////////////////////////////////////////*/

#include "Utilities.h"
using namespace std;
namespace seneca {
	char Utilities::m_delimiter = ',';
	void Utilities::trim(std::string& str) {
		size_t first = str.find_first_not_of(' ');
		if (first == std::string::npos) {
			str.clear();
		}
		else {
			size_t last = str.find_last_not_of(' ');
			str = str.substr(first, last - first + 1);
		}
	}

	string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more) {
		std::string token;
		if (next_pos < str.size()) {
			size_t delimiterIndex = str.find(m_delimiter, next_pos);

			if (delimiterIndex == next_pos) {
				more = false;
				throw "Delimiter is found at next_pos";
			}

			if (delimiterIndex != std::string::npos) {
			token = str.substr(next_pos, delimiterIndex - next_pos);
			trim(token);  
			next_pos = delimiterIndex + 1;
			more = true;
			}
			else {
			token = str.substr(next_pos);
			trim(token);  
			next_pos = str.size();  
			more = false; 
			}

			m_widthField = std::max(m_widthField, token.size());
		}
		else {
			token = "";
			more = false;
		}
		return token;
	}

	void Utilities::setFieldWidth(size_t newWidth) {
		m_widthField = newWidth;
	}

	size_t Utilities::getFieldWidth() const {
		return m_widthField;
	}

	void Utilities::setDelimiter(char newDelimiter) {
		m_delimiter = newDelimiter;
	}

	char Utilities::getDelimiter() {
		return m_delimiter;
	}
}