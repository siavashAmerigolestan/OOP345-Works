#ifndef SENECA_BOOK_H
#define SENECA_BOOK_H
#include <string>
#include "MediaItem.h"

namespace seneca {
	class Book : public MediaItem {
		std::string m_author;
		std::string m_country;
		double m_price;

		Book(const std::string& author, const std::string& title, const std::string& country,
			unsigned short year, double price, const std::string& summary);
	public:
		void display(std::ostream& out) const override;
		Book* createItem(const std::string& strBook);

	};
}

#endif
