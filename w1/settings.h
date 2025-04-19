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

#ifndef SENECA_SETTINGS_H
#define SENECA_SETTINGS_H
#include <string>

namespace seneca {
	struct Settings {
		bool m_show_all = false;
		bool m_verbose = false;
		std::string m_time_units = "nanoseconds";
	};
	extern seneca::Settings g_settings;
}


#endif
