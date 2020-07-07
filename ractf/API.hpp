#ifndef RACTF_CLI_API_HPP
#define RACTF_CLI_API_HPP

#include <string>
#include <utility>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

#include "Category.hpp"
#include "Challenge.hpp"

namespace ractf {
    class API {
    public:
        template<typename URIType, typename StrType1, typename StrType2, typename StrType3 = std::string>
        requires std::is_convertible<URIType, web::uri>::value
        API(URIType&& apiEndpoint, StrType1&& username, StrType2&& password, StrType3&& otp = "-1")
                : apiClient(std::forward<URIType>(apiEndpoint)), username(std::forward<StrType1>(username))
        {
            generateToken(this->username, std::forward<StrType2>(password), std::forward<StrType3>(otp));
            fetchCTFInformation();
        }

        void generateToken(const std::string &username, const std::string &password, const std::string &otp);

        void reloadCategories();

        std::string CTFName;
        std::string username;
        std::string teamName;
        std::vector<Category> categories;
        std::unordered_map<int, std::pair<std::string, Challenge*>> challengeMap;
    private:


        void fetchCTFInformation();

        std::string token;
        web::http::client::http_client apiClient;
    };
}

#endif //RACTF_CLI_API_HPP
