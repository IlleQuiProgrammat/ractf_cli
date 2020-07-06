#include "CLI.hpp"

#include <cpprest/http_client.h>
#include <filesystem>

int main() {
    // TODO: Config file
    web::uri endpoint = U("https://api.ractf.co.uk/api/v2/");
    std::string username, password, otp;

    std::cout << "Username: ";
    std::cout.flush();
    std::cin >> username;

    // TODO: hide password
    std::cout << "Password: ";
    std::cout.flush();
    std::cin >> password;

    std::cout << "TOTP Code (-1 if this is not enabled): ";
    std::cout.flush();
    std::cin >> otp;

    ractf::CLI cli(endpoint, username, password, otp);
    cli.run();
    return 0;
}
