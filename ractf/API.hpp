#ifndef RACTF_CLI_API_HPP
#define RACTF_CLI_API_HPP

#include <string>
#include <utility>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

#include "Category.hpp"

namespace ractf {
    class API {
    public:
        API(const web::uri &apiEndpoint, const std::string &username, const std::string &password,
            const std::string &otp = "-1")
                : apiClient(apiEndpoint), username(username) {
            generateToken(username, password, otp);
            fetchCTFInformation();
        }

        void generateToken(const std::string &username, const std::string &password, const std::string &otp);

        void reloadCategories();

        std::string CTFName;
        std::string username;
        std::string teamName;
        std::vector<Category> categories;
    private:


        void fetchCTFInformation();

        std::string token;
        web::http::client::http_client apiClient;
    };
}

#endif //RACTF_CLI_API_HPP
