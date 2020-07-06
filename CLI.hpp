#ifndef RACTF_CLI_CLI_HPP
#define RACTF_CLI_CLI_HPP

#include <string>
#include <iostream>
#include <queue>
#include <map>
#include <functional>

#include "ractf/API.hpp"
#include <cpprest/http_client.h>
namespace ractf {
    class CLI {
    public:
        CLI(const web::uri &apiEndpoint, const std::string &username, const std::string &password,
            const std::string &otp) :
                m_apiConnection(apiEndpoint, username, password, otp) {
#pragma region registering_command
            commandMap["help"] = &CLI::exec_help;
            commandDescriptions["help"] = "Shows this help message";
            commandRegistration.emplace_back("help");

            commandMap["clear"] = &CLI::exec_clear;
            commandDescriptions["clear"] = "Clears the screen";
            commandRegistration.emplace_back("clear");

            commandMap["hello"] = &CLI::exec_helloWorld;
            commandDescriptions["hello"] = "Prints hello world followed by all of the arguments parsed to it";
            commandRegistration.emplace_back("hello");

            commandMap["addcat"] = &CLI::exec_addCategory;
            commandDescriptions["addcat"] = "Adds categories to the internal category level tracker - testing";
            commandRegistration.emplace_back("addcat");

            commandMap["list"] = &CLI::exec_list;
            commandDescriptions["list"] =
                    "lists all problems";
            commandRegistration.emplace_back("list");

            commandMap["download"] = &CLI::exec_download;
            commandDescriptions["download"] =
                    "downloads current problem or all problems if `download all` is run, provides directory structure";
            commandRegistration.emplace_back("download");

            commandMap["quit"] = &CLI::exec_quit;
            commandDescriptions["quit"] = "exit";
            commandRegistration.emplace_back("quit");
#pragma endregion
        }

        void run();

    private:

        void prompt();

        int executeCommand();

        int commandError(std::string_view errorMessage);

        void clearScreen();

        void strip(std::string &str);

        int exec_helloWorld(std::string &arguments);

        int exec_addCategory(std::string &arguments);

        int exec_help(std::string &arguments);

        int exec_clear(std::string &arguments);

        int exec_download(std::string &arguments);

        int exec_quit(std::string &arguments);

        int exec_list(std::string &arguments);

        API m_apiConnection;

        std::vector<std::string> m_subcategories;

        std::map<std::string, int (CLI::*)(std::string &)> commandMap;
        std::map<std::string, std::string> commandDescriptions;
        std::vector<std::string> commandRegistration;
    };
}

#endif //RACTF_CLI_CLI_HPP
