#include "Challenge.hpp"
#include "API.hpp"

namespace ractf {

    void Challenge::parseJson(web::json::value& jsonData) {
        try {
            if (jsonData[U("hidden")].as_bool() || !jsonData[U("unlocked")].as_bool()) {
                challenge_id = -1;
                score = -1;
                name = "This challenge is inaccessible.";
            } else {
                challenge_id = jsonData[U("id")].as_number().to_int32();
                name = jsonData[U("name")].as_string();
                category = jsonData[U("category")].as_number().to_int32();
                description = jsonData[U("description")].as_string();
                std::string chalType = jsonData[U("challenge_type")].as_string();
                if (chalType == "default") {
                    challengeType = ChallengeType::def;
                } else {
                    challengeType = ChallengeType::unknown;
                }
                solveCount = jsonData[U("solve_count")].as_number().to_int32();
                author = jsonData[U("author")].as_string();
                score = jsonData[U("score")].as_number().to_int32();
                std::string flagt = jsonData[U("flag_type")].as_string();
                if (flagt == "plaintext") {
                    flagType = FlagType::plaintext;
                } else {
                    flagType = FlagType::unknown;
                }
                for (auto &it : jsonData[U("unlocks")].as_array()) {
                    unlocks.push_back(it.as_number().to_int32());
                }
                solved = jsonData[U("solved")].as_bool();
                unlocked = jsonData[U("unlocked")].as_bool();
                hidden = jsonData[U("hidden")].as_bool();
                firstBlood = jsonData[U("first_blood")].as_number().to_int32();
                firstBloodTeam = jsonData[U("first_blood_name")].as_string();
                solveCount = jsonData[U("solve_count")].as_number().to_int32();
                autoUnlock = jsonData[U("auto_unlock")].as_bool();
                for (auto &it : jsonData[U("files")].as_array()) {
                    files.push_back(it[U("url")].as_string());
                }
            }
        } catch (...) {
            std::cerr << "Error whilst parsing challenge data" << std::endl;
        }
    }

    void Challenge::operator=(web::json::value &rhs) {
        parseJson(std::forward<web::json::value&>(rhs));
    }

    Challenge::Challenge(web::json::value &jsonData, std::string_view categoryName,
                         std::unordered_map<int, std::pair<std::string, Challenge *>> *registrationMap) {
        parseJson(std::forward<web::json::value&>(jsonData));
        this->categoryName = categoryName;
        if (registrationMap) {
            (*registrationMap)[challenge_id] = std::make_pair(categoryName, this);
        }
    }
}