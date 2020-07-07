#ifndef RACTF_CLI_CHALLENGE_HPP
#define RACTF_CLI_CHALLENGE_HPP
#include <vector>
#include <cpprest/json.h>

namespace ractf {
    enum class ChallengeType {
        def = 0,
        unknown = -1
    };

    enum class FlagType {
        plaintext = 0,
        unknown = -1
    };

    struct Challenge {
        int challenge_id;
        int score;
        std::string name;
        std::string description;
        std::string author;
        bool solved;
        bool unlocked;
        bool hidden;
        bool autoUnlock;
        int firstBlood;
        std::string firstBloodTeam;
        int solveCount;
        int category;
        std::string categoryName;
        ChallengeType challengeType;
        FlagType flagType;
        std::vector<std::string> files;
        std::vector<int> unlocks;

        Challenge() = default;

        Challenge(web::json::value &jsonData, std::string& categoryName);
    };
}

#endif //RACTF_CLI_CHALLENGE_HPP
