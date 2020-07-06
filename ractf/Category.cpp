#include "Category.hpp"

#include <cpprest/json.h>
namespace ractf {
    Category::Category(web::json::value &jsonData) {
        id = jsonData[U("id")].as_number().to_int32();
        displayOrder = jsonData[U("display_order")].as_number().to_int32();
        name = jsonData[U("name")].as_string();
        description = jsonData[U("description")].as_string();
        containedType = ContainedType::unknown;

        for (auto &challenge : jsonData[U("challenges")].as_array()) {
            challenges.emplace_back(challenge);
        }
    }
}