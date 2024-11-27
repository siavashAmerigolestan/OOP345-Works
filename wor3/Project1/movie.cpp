/*/////////////////////////////////////////////////////////////////////////
                               OOP345 Workshop3
Full Name  : Siavash Amerigolestan
Student ID#: 133733220
Email      : samerigolestan@myseneca.ca
Section    : ZBB
Date       : 2024-11-24
/////////////////////////////////////////////////////////////////////////*/

#include <iostream>
#include <iomanip>
#include <string>
#include "settings.h"
#include "movie.h"
using namespace std;
namespace seneca {
    Movie::Movie(const std::string& title, unsigned short year, const std::string& summary) : MediaItem(title, summary, year) {}

    void Movie::display(std::ostream& out) const {
        if (g_settings.m_tableView)
        {
            out << "M | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << this->getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(9) << this->getYear() << " | ";
            out << std::left;
            if (g_settings.m_maxSummaryWidth > -1)
            {
                if (static_cast<short>(this->getSummary().size()) <= g_settings.m_maxSummaryWidth)
                    out << this->getSummary();
                else
                    out << this->getSummary().substr(0, g_settings.m_maxSummaryWidth - 3) << "...";
            }
            else
                out << this->getSummary();
            out << std::endl;
        }
        else
        {
            size_t pos = 0;
            out << this->getTitle() << " [" << this->getYear() << "]\n";
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
            while (pos < this->getSummary().size())
            {
                out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
                << std::setfill(' ') << '\n';
        }
    }

    Movie* Movie::createItem(const std::string& strMovie) {
        if (strMovie.empty() || strMovie.front() == '#') {
            throw "Not a valid movie.";
        }
        std::string title, yearString, summary;
        unsigned short year;
        size_t begin = 0;
        size_t end;

        end = strMovie.find(',');
        title = strMovie.substr(begin, end);

        begin = end + 1;
        end = strMovie.find(',', begin);
        yearString = strMovie.substr(begin, end - begin);

        begin = end + 1;
        summary = strMovie.substr(begin);

        trim(title);
        trim(yearString);
        trim(summary);

        year = std::stoi(yearString);

        return new Movie(title, year, summary);
    }
}
