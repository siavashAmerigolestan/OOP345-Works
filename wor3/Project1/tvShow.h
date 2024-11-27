#ifndef SENECA_TVSHOW_H
#define SENECA_TVSHOW_H
#include <string>
#include <vector>
#include <list>
#include "MediaItem.h"
#include <sstream>
#include <iostream>
#include <algorithm>
#include <numeric>

namespace seneca {
    class TvShow : public MediaItem {
        unsigned int m_id;
        struct TvEpisode
        {
            const TvShow* m_show{};
            unsigned short m_numberOverall{};
            unsigned short m_season{};
            unsigned short m_numberInSeason{};
            std::string m_airDate{};
            unsigned int m_length{};
            std::string m_title{};
            std::string m_summary{};
        };
        std::vector<TvEpisode> m_episodes;
        TvShow(unsigned int m_id, const std::string& title, unsigned short year, const std::string& summary);
    public:
        void display(std::ostream& out) const override;
        static TvShow* createItem(const std::string& strShow);
        template<typename Collection_t>
        static void addEpisode(Collection_t& col, const std::string& strEpisode) {
            if (strEpisode.empty() || strEpisode.front() == '#') {
                throw "Not a valid episode.";
            }
            unsigned short numberOverall, season, numberInSeason;
            unsigned int id, length;
            std::string idString, numberOverallString, seasonString, numberInSeasonString, airDate, lengthString, title, summary;

            size_t start = 0;
            size_t end;

            end = strEpisode.find(',');
            idString = strEpisode.substr(start, end - start);

            start = end + 1;
            end = strEpisode.find(',', start);
            numberOverallString = strEpisode.substr(start, end - start);

            start = end + 1;
            end = strEpisode.find(',', start);
            seasonString = strEpisode.substr(start, end - start);

            start = end + 1;
            end = strEpisode.find(',', start);
            numberInSeasonString = strEpisode.substr(start, end - start);

            start = end + 1;
            end = strEpisode.find(',', start);
            airDate = strEpisode.substr(start, end - start);

            start = end + 1;
            end = strEpisode.find(',', start);
            lengthString = strEpisode.substr(start, end - start);

            start = end + 1;
            end = strEpisode.find(',', start);
            title = strEpisode.substr(start, end - start);

            start = end + 1;
            summary = strEpisode.substr(start);

            trim(idString);
            trim(numberOverallString);
            trim(seasonString);
            trim(numberInSeasonString);
            trim(airDate);
            trim(lengthString);
            trim(title);
            trim(summary);

            id = static_cast<unsigned int>(std::stoi(idString));
            numberOverall = static_cast<unsigned short>(std::stoi(numberOverallString));


            if (!seasonString.empty()) {
                season = static_cast<unsigned short>(std::stoi(seasonString));
            }
            else {
                season = 1;
            }

            numberInSeason = static_cast<unsigned short>(std::stoi(numberInSeasonString));

            auto convertTime = [](const std::string& timeStr) -> unsigned int {
                unsigned int hours = 0, minutes = 0, seconds = 0;
                char delimiter;
                std::istringstream timeStream(timeStr);
                timeStream >> hours >> delimiter >> minutes >> delimiter >> seconds;
                return hours * 3600 + minutes * 60 + seconds;
            };
            length = convertTime(lengthString);

            bool showFound = false;
            for (size_t i = 0; i < col.size() && !showFound; i++) {
                TvShow* targetShow = dynamic_cast<TvShow*>(col[i]);
                if (targetShow->m_id == id) {
                    TvEpisode episode = { targetShow, numberOverall, season, numberInSeason, airDate, length, title, summary };
                    targetShow->m_episodes.push_back(episode);
                    showFound = true;
                }
            }

        }
        double getEpisodeAverageLength() const;
        std::list<std::string> getLongEpisodes() const;

    };
}

#endif 


