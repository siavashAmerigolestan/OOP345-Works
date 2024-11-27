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
#include "book.h"

using namespace std;
namespace seneca {

    Book::Book(const std::string& author, const std::string& title, const std::string& country, unsigned short year,
        double price, const std::string& summary) : MediaItem(title, summary, year) {
        m_author = author;
        m_price = price;
        m_country = country;
    }

    void Book::display(std::ostream& out) const
    {
        if (g_settings.m_tableView)
        {
            out << "B | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << this->getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(2) << this->m_country << " | ";
            out << std::setw(4) << this->getYear() << " | ";
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
            out << this->getTitle() << " [" << this->getYear() << "] [";
            out << m_author << "] [" << m_country << "] [" << m_price << "]\n";
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

    Book* Book::createItem(const std::string& strBook) {
        if (strBook.empty() || strBook.front() == '#') {
            throw "Not a valid book.";
        }
        std::string author, title, country, yearString, priceString, summary;
        unsigned short year;
        double price;
        size_t begin = 0;
        size_t end;

        end = strBook.find(',');
        author = strBook.substr(begin, end);

        // TITLE
        begin = end + 1;
        end = strBook.find(',', begin);
        title = strBook.substr(begin, end - begin);

        // COUNTRY
        begin = end + 1;
        end = strBook.find(',', begin);
        country = strBook.substr(begin, end - begin);

        // PRICE
        begin = end + 1;
        end = strBook.find(',', begin);
        priceString = strBook.substr(begin, end - begin);

        // YEAR
        begin = end + 1;
        end = strBook.find(',', begin);
        yearString = strBook.substr(begin, end - begin);

        // SUMMARY
        begin = end + 1;
        summary = strBook.substr(begin);

        trim(author);
        trim(title);
        trim(country);
        trim(yearString);
        trim(summary);

        price = std::stod(priceString);
        year = std::stoi(yearString);
        return new Book(author, title, country, year, price, summary);
    }
}

