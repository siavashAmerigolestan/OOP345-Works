#ifndef SENECA_ARCHER_H
#define SENECA_ARCHER_H
#include <iostream>
#include "characterTpl.h"
#include "health.h"
namespace seneca {
    template <typename Weapon_t>
    class Archer : public CharacterTpl<seneca::SuperHealth> {
        int m_baseDefense{};
        int m_baseAttack{};
        Weapon_t m_weapon;

    public:

        Archer(const char* name, int healthMax, int baseAttack, int baseDefense, Weapon_t weapon)
            : CharacterTpl<seneca::SuperHealth>(name, healthMax) {
            m_baseDefense = baseDefense;
            m_baseAttack = baseAttack;
            m_weapon = weapon;
        }
    

        Archer(const Archer<Weapon_t>& rhs) : CharacterTpl<seneca::SuperHealth>(rhs) {
            m_baseAttack = rhs.m_baseAttack;
            m_baseDefense = rhs.m_baseDefense;
            m_weapon = rhs.m_weapon;
        }

        int getAttackAmnt() const override {
            return (1.3 * m_baseAttack);
           
        }

        int getDefenseAmnt() const override {
            return (1.2 * m_baseDefense);
        }

        Character* clone() const override {
            return new Archer<Weapon_t>(*this);
        }

        void attack(Character* enemy) {
            std::cout << getName() << " is attacking " << enemy->getName();
            int damage = getAttackAmnt();
            std::cout << "Archer deals " << damage << " ranged damage!" << std::endl;
            enemy->takeDamage(damage);
        }

        void takeDamage(int dmg) {
            std::cout << getName() << " is attacked for " << getAttackAmnt() << " damage." << std::endl;
            std::cout << "    Archer has a defense of " << getDefenseAmnt() << "." << " Reducing damage received." << std::endl;
            dmg -= m_baseDefense;
            dmg = dmg < 0 ? 0 : dmg;
            CharacterTpl<seneca::SuperHealth>::takeDamage(dmg);
        }
        
    };
}
#endif 

