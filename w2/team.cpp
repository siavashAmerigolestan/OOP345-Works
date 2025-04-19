/*/////////////////////////////////////////////////////////////////////////
                               OOP345 Workshop2
Full Name  : Siavash Amerigolestan
Student ID#: 133733220
Email      : samerigolestan@myseneca.ca
Section    : ZBB
Date       : 2024-10-18
/////////////////////////////////////////////////////////////////////////*/

#include "team.h"
using namespace std;
namespace seneca {
    Team::Team() {
    }

    Team::Team(const char* name) {
        m_name = name;
    }

    Team::Team(const Team& rhs) {
        *this = rhs;
    }

    Team& Team::operator=(const Team& rhs) {
        if (this != &rhs) {
            for (size_t i = 0; i < m_size; ++i) {
                delete m_contain[i];
            }
            delete[] m_contain;

            m_name = rhs.m_name;
            m_contain = new Character * [rhs.m_size];
            m_size = rhs.m_size;
            for (size_t i = 0; i < m_size; ++i) {
                m_contain[i] = rhs.m_contain[i]->clone();
            }
        }

        return *this;
    }

    Team::~Team() {
        for (size_t i = 0; i < m_size; ++i) {
            delete m_contain[i];
        }
        delete[] m_contain;
    }

    Team::Team(Team&& rhs) noexcept {
        *this = std::move(rhs);
    }

    Team& Team::operator=(Team&& rhs) noexcept {
        if (this != &rhs) {
            for (size_t i = 0; i < m_size; ++i) {
                delete m_contain[i];
            }
            delete[] m_contain;
            m_name = rhs.m_name;
            m_contain = rhs.m_contain;
            m_size = rhs.m_size;
            rhs.m_name = "";
            rhs.m_contain = nullptr;
            rhs.m_size = 0;
        }

        return *this;
    }

    int Team::find(const std::string& c) {
        int foundIndex = -1;
        for (size_t i = 0; foundIndex == -1 && i < m_size; i++) {
            if (m_contain[i]->getName() == c) {
                foundIndex = static_cast<int>(i);
            }
        }
        return foundIndex;
    }

    void Team::addMember(const Character* c) {
        int index = find(c->getName());
        if (index == -1) {
            Character** temp = new  Character * [m_size + 1];
            for (size_t i = 0; i < m_size; i++) {
                temp[i] = m_contain[i];
            }
            temp[m_size] = c->clone();
            delete[] m_contain;
            m_contain = temp;
            m_size++;
        }
    }

    void Team::removeMember(const std::string& c) {
        int index = find(c);
        if (index >= 0) {
            size_t j{};
            Character** temp = new Character * [m_size - 1];
            for (size_t i = 0; i < m_size; i++) {
                if (i != static_cast<size_t>(index)) {
                    (temp[j++] = m_contain[i]);
                }
            }
            delete[] m_contain;
            m_contain = temp;
            m_size--;
        }
  
    }

    Character* Team::operator[](size_t idx) const {
        if (idx < static_cast<size_t>(m_size)) {
            return m_contain[idx];
        }
        else {
            return nullptr;
        }
    }

    void Team::showMembers() const {
        if (m_name.empty() && m_size == 0)
            std::cout << "No team." << endl;
        else {
            std::cout << "[Team] " << m_name << endl;
            for (size_t i = 0; i < m_size; ++i) {
                std::cout << "    " << (i + 1) << ": " << *(m_contain[i]) << endl;
            }
        }
    }
}