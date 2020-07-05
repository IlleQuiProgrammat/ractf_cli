#ifndef RACTF_CLI_RACTFAPI_HPP
#define RACTF_CLI_RACTFAPI_HPP

#include <string>
#include <utility>
#include <cpprest/http_client.h>
#include <cpprest/filestream.h>

class RACTFAPI {
public:
    RACTFAPI(const web::uri& apiEndpoint, const std::string& username, std::string password, int otp = -1)
        : apiClient(apiEndpoint), username(username)
        {
            generateToken(username, std::move(password), otp);
            fetchData();
        }

    void generateToken(const std::string& username, const std::string& password, int otp);

    std::string CTFName;
    std::string username;
    std::string teamName;
private:


    void fetchData();

    std::string token;
    web::http::client::http_client apiClient;
};


#endif //RACTF_CLI_RACTFAPI_HPP
