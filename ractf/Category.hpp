//
// Created by dardledumdue on 06/07/2020.
//

#ifndef RACTF_CLI_CATEGORY_HPP
#define RACTF_CLI_CATEGORY_HPP

#include <vector>
#include <cpprest/json.h>
#include <string>

#include "Challenge.hpp"

namespace ractf {
    enum class ContainedType {
        unknown = -1
    };

    struct Category {
        int id;
        int displayOrder;

        std::string name;
        std::string description;
        ContainedType containedType;

        std::vector<Challenge> challenges;

        Category() = default;

        explicit Category(web::json::value &jsonData);
        Category(web::json::value& jsonData,
                std::unordered_map<int,std::pair<std::string, Challenge*>>* registrationMap = nullptr);
    };
}

#endif //RACTF_CLI_CATEGORY_HPP
