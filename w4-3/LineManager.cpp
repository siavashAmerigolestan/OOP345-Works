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

#include <fstream>
#include <algorithm>
#include <string>
#include "Workstation.h"
#include "LineManager.h"
#include "Utilities.h"
using namespace std;

namespace seneca {
    LineManager::LineManager(const string& file, const vector<Workstation*>& stations) {
        if (!file.empty()) {
            std::ifstream f_(file);

            if (!f_.is_open()) {
                throw "File is not open";
            }

            string record;
            Utilities utilities;

            while (!f_.eof()) {
                getline(f_, record);
                string currentWSName, nextWSName;
                size_t next_pos = 0u;
                bool more = true;

                currentWSName = utilities.extractToken(record, next_pos, more);
                nextWSName = utilities.extractToken(record, next_pos, more);

                auto currentWS = std::find_if(stations.begin(), stations.end(), [=](const Workstation* station) {
                    return station->getItemName() == currentWSName;
                    });

                auto nextWS = std::find_if(stations.begin(), stations.end(), [=](const Workstation* station) {
                    return station->getItemName() == nextWSName;
                    });

                if (currentWS != stations.end()) {
                    m_activeLine.push_back(*currentWS);
                    if (nextWS != stations.end())
                        (*currentWS)->setNextStation(*nextWS);
                }
            }

            m_firstStation = *std::find_if(stations.begin(), stations.end(), [=](const Workstation* station) {
                return std::none_of(stations.begin(), stations.end(), [=](const Workstation* ws) {
                    return ws->getNextStation() == station;
                    });
                });
            m_cntCustomerOrder = g_pending.size();
            f_.close();
        }
        else {
            throw "File name is empty";
        }
    }

    void LineManager::reorderStations() {
        Workstation* next_Wstation = m_firstStation;
        std::vector<Workstation*>  v_Wstation;

        while (next_Wstation) {
            v_Wstation.push_back(next_Wstation);
            next_Wstation = next_Wstation->getNextStation();
        }

        m_activeLine = v_Wstation;
    }

    bool LineManager::run(std::ostream& os) {
        bool result = false;
        static size_t i = 0;
        os << "Line Manager Iteration: " << ++i << std::endl;
        if (!g_pending.empty()) {
            *m_firstStation += std::move(g_pending.front());
            g_pending.pop_front();
        }

        for (auto src : m_activeLine)
            src->fill(os);

        for (auto src : m_activeLine)
            src->attemptToMoveOrder();

        if (m_cntCustomerOrder == (g_completed.size() + g_incomplete.size())) {
            result = true;
        }

        return result;
    }

    void LineManager::display(std::ostream& os) const {
        if (!m_activeLine.empty()) {
            for (const auto& station : m_activeLine) {
                station->display(os);
            }
        }
    }
}