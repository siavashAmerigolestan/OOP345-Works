#ifndef SENECA_CHARACTERTPL_H
#define SENECA_CHARACTERTPL_H
#include <iostream>
#include "character.h"
#include "weapons.h"
#include "health.h"
#include "abilities.h"
namespace seneca {
    template <typename T>
    class CharacterTpl : public Character {
        T m_health;
        int m_healthMax;

    public:

        CharacterTpl(const char* name, int healthMax) : Character(name) {
            m_health = healthMax;
            m_healthMax = healthMax;
        }
  
        CharacterTpl(const CharacterTpl<T>& rhs) : Character(rhs.getName().c_str()) {
            m_health = rhs.m_health;
            m_healthMax = rhs.m_healthMax;
        }

		void takeDamage(int dmg) override {
			m_health -= dmg;
			if (m_health > 0) {
				std::cout << "    " << getName() << " took " << dmg << " damage, " << m_health << " health remaining." << std::endl;
			}
			
			else {
				m_health = 0;
				std::cout << "    " << getName() << " has been defeated!" << std::endl;
			}
		}

		int getHealth() const override {
			return static_cast<int>(m_health);
		}

		int getHealthMax() const override {
			return m_healthMax;
		}

		void setHealth(int health) override {
			m_health = health;
		}

		void setHealthMax(int health) override {
			m_health = health;
			m_healthMax = health;
		}
       
    };

}
#endif

