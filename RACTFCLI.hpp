#ifndef RACTF_CLI_RACTFCLI_HPP
#define RACTF_CLI_RACTFCLI_HPP

#include <string>
#include <iostream>
#include <queue>
#include <map>
#include <functional>

class RACTFCLI {
public:
    RACTFCLI(std::string_view apiEndpoint, std::string_view token) :
            m_apiEndpoint(apiEndpoint), m_token(token) {
        // TODO: get from server
        m_CTFName = "RACTF";

#pragma region registering_command
        commandMap["help"] = &RACTFCLI::exec_help;
        commandDescriptions["help"] = "Shows this help message";
        commandRegistration.emplace_back("help");

        commandMap["clear"] = &RACTFCLI::exec_clear;
        commandDescriptions["clear"] = "Clears the screen";
        commandRegistration.emplace_back("clear");

        commandMap["hello"] = &RACTFCLI::exec_helloWorld;
        commandDescriptions["hello"] = "Prints hello world followed by all of the arguments parsed to it";
        commandRegistration.emplace_back("hello");

        commandMap["addcat"] = &RACTFCLI::exec_addCategory;
        commandDescriptions["addcat"] = "Adds categories to the internal category level tracker - testing";
        commandRegistration.emplace_back("addcat");
#pragma endregion
    }
    void run();

    static std::string retrieveApiKey(std::string_view username, std::string_view password, int TOTPCode);
private:

    void prompt();
    int executeCommand();
    int commandError(std::string_view errorMessage);
    void clearScreen();
    void strip(std::string& str);

    int exec_helloWorld(std::string& arguments);
    int exec_addCategory(std::string& arguments);
    int exec_help(std::string& arguments);
    int exec_clear(std::string& arguments);
    int exec_cd(std::string& arguments);
    int exec_pwd(std::string& arguments);

    std::string_view m_apiEndpoint;
    std::string_view m_token;

    std::string m_CTFName;

    std::vector<std::string> m_subcategories;

    std::map<std::string, int(RACTFCLI::*)(std::string&)> commandMap;
    std::map<std::string, std::string> commandDescriptions;
    std::vector<std::string> commandRegistration;
};


#endif //RACTF_CLI_RACTFCLI_HPP
