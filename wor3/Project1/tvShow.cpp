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
#include <numeric>
#include <algorithm>
#include "tvShow.h"
#include "settings.h"

namespace seneca {
    TvShow::TvShow(unsigned int id, const std::string& title, unsigned short year, const std::string& summary) : 
        MediaItem(title, summary, year), m_id(id) { }

    void TvShow::display(std::ostream& out) const
    {
        if (g_settings.m_tableView)
        {
            out << "S | ";
            out << std::left << std::setfill('.');
            out << std::setw(50) << this->getTitle() << " | ";
            out << std::right << std::setfill(' ');
            out << std::setw(2) << this->m_episodes.size() << " | ";
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
            out << this->getTitle() << " [" << this->getYear() << "]\n";
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << "" << '\n';
            while (pos < this->getSummary().size())
            {
                out << "    " << this->getSummary().substr(pos, g_settings.m_maxSummaryWidth) << '\n';
                pos += g_settings.m_maxSummaryWidth;
            }
            for (auto& item : m_episodes)
            {
                out << std::setfill('0') << std::right;
                out << "    " << 'S' << std::setw(2) << item.m_season
                    << 'E' << std::setw(2) << item.m_numberInSeason << ' ';
                if (item.m_title != "")
                    out << item.m_title << '\n';
                else
                    out << "Episode " << item.m_numberOverall << '\n';

                pos = 0;
                while (pos < item.m_summary.size())
                {
                    out << "            " << item.m_summary.substr(pos, g_settings.m_maxSummaryWidth - 8) << '\n';
                    pos += g_settings.m_maxSummaryWidth - 8;
                }
            }
            out << std::setw(this->getTitle().size() + 7) << std::setfill('-') << ""
                << std::setfill(' ') << '\n';
        }
    }

    TvShow* TvShow::createItem(const std::string& strShow) {
        if (strShow.empty() || strShow.front() == '#')
            throw "Not a valid show.";

        unsigned int id;
        std::string idString, title, yearString, summary;
        unsigned short year;

        size_t begin = 0;
        size_t end;

        end = strShow.find(',');
        idString = strShow.substr(begin, end);

        begin = end + 1;
        end = strShow.find(',', begin);
        title = strShow.substr(begin, end - begin);

        begin = end + 1;
        end = strShow.find(',', begin);
        yearString = strShow.substr(begin, end - begin);

        begin = end + 1;
        summary = strShow.substr(begin);


        trim(idString);
        trim(title);
        trim(yearString);
        trim(summary);

        id = static_cast<unsigned int>(std::stoi(idString));
        year = static_cast<unsigned short>(std::stoi(yearString));
        return new TvShow(id, title, year, summary);
    }

    double TvShow::getEpisodeAverageLength() const {
        if (m_episodes.empty()) {
            return 0.0;
        }
        unsigned int sumOfLengths = std::accumulate(m_episodes.begin(), m_episodes.end(), (unsigned int)0,
            [](unsigned sum, const TvEpisode& currentEpisode) { return sum + currentEpisode.m_length; });
        return static_cast<double>(sumOfLengths) / m_episodes.size();
    }

    std::list<std::string> TvShow::getLongEpisodes() const {
        std::list<std::string> longRunningEpisodes;

        std::for_each(m_episodes.begin(), m_episodes.end(),
            [&](const TvEpisode& episode) {
                if (episode.m_length > 3600) {
                    longRunningEpisodes.push_back(episode.m_title);
                }
            });
        return longRunningEpisodes;
    }
}