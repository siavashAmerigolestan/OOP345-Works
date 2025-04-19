/*/////////////////////////////////////////////////////////////////////////
                               OOP345 Workshop2
Full Name  : Siavash Amerigolestan
Student ID#: 133733220
Email      : samerigolestan@myseneca.ca
Section    : ZBB
Date       : 2024-10-18
/////////////////////////////////////////////////////////////////////////*/
#include<iostream>
#include<string>
#include "guild.h"
using namespace std;
namespace seneca {
    Guild::Guild() {
        m_name = "";
        m_contain = nullptr;
        m_size = 0;
    }

    Guild::Guild(const char* name) {
        m_name = name;
    }

    Guild::Guild(const Guild& rhs) {
        m_name = rhs.m_name;
        m_size = rhs.m_size;
        m_contain = new Character * [m_size];
        for (size_t i = 0; i < m_size; i++) {
            m_contain[i] = rhs.m_contain[i];
        }
    }
    Guild& Guild::operator=(const Guild& rhs) {
        if (this != &rhs) {
            delete[] m_contain;
            m_name = rhs.m_name;
            m_size = rhs.m_size;
            m_contain = new Character * [m_size];
            for (size_t i = 0; i < m_size; i++) {
                m_contain[i] = rhs.m_contain[i];
            }
        }
        return *this;
    }

    Guild::~Guild() {
        delete[] m_contain;
    }

    Guild::Guild(Guild&& rhs) noexcept {
        m_name = rhs.m_name;
        m_size = rhs.m_size;
        m_contain = rhs.m_contain;
        rhs.m_name = "";
        rhs.m_size = 0;
        rhs.m_contain = nullptr;

    }

    Guild& Guild::operator=(Guild&& rhs) noexcept {
        if (this != &rhs) {
            delete[] m_contain;
            m_name = rhs.m_name;
            m_size = rhs.m_size;
            m_contain = rhs.m_contain;
            rhs.m_name = "";
            rhs.m_size = 0;
            rhs.m_contain = nullptr;
        }
        return *this;
 
    }

    int Guild::find(const std::string& c) {
        int foundIndex = -1;
        for (size_t i = 0; foundIndex == -1 && i < m_size; i++) {
            if (m_contain[i]->getName() == c) {
                foundIndex = static_cast<int>(i);
            }
        }
        return foundIndex;
   
    }

    void Guild::addMember(Character* c) {
        int index = find(c->getName());
        if (index == -1) {
            Character** temp = new  Character * [m_size + 1];
            for (size_t i = 0; i < m_size; i++) {
                temp[i] = m_contain[i];
            }
            temp[m_size] = c;
            c->setHealthMax(c->getHealthMax() + 300);
            c->setHealth(c->getHealthMax());
            delete[] m_contain;
            m_contain = temp;
            m_size++;
        }
 
    }

    void Guild::removeMember(const std::string& c) {
        int index = find(c);
        if (index >= 0) {
            m_contain[index]->setHealthMax(m_contain[index]->getHealthMax() - 300);
            m_contain[index]->setHealth(m_contain[index]->getHealthMax());
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

    Character* Guild::operator[](size_t idx) const {
        if (idx < static_cast<size_t>(m_size)) {
            return m_contain[idx];
        }
        else {
            return nullptr;
        } 
    }

    void Guild::showMembers() const {
        if (m_name.empty() && m_size == 0)
            std::cout << "No guild." << endl;
        else {
            std::cout << "[Guild] " << m_name << endl;
            for (size_t i = 0; i < m_size; ++i) {
                std::cout << "    " << (i + 1) << ": " << *(m_contain[i]) << endl;
            }
        }
    }
}