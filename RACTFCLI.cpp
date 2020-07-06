#include "RACTFCLI.hpp"

#include <cstdlib>
#include <exception>

void RACTFCLI::prompt() {
    std::cout << m_apiConnection.teamName << " @ " << m_apiConnection.CTFName;
    if (!m_subcategories.empty()) {
        std::cout << " - " << m_subcategories[0];
        if (m_subcategories.size() > 1) {
            std::cout << "(";
            std::for_each(
                    m_subcategories.begin() + 1, m_subcategories.end() - 1,
                    [](auto& it) {
                        std::cout << it << "/";
                        }
                    );
            std::cout << *(m_subcategories.end() - 1) << ") "@;
        }
    }
    std::cout << "> ";
    std::flush(std::cout);
}

void RACTFCLI::clearScreen() {
#ifdef __linux__
    system("clear");
#endif
#ifdef _WIN32
    system("cls");
#endif
}

void RACTFCLI::run() {
    int exitCode = 0;
    while (exitCode == 0) {
        try {
            exitCode = executeCommand();
        } catch (std::exception& e) {
            std::cerr << e.what() << std::endl;
        }
    }
    std::cout << exitCode << std::endl;
}

int RACTFCLI::executeCommand() {
    prompt();
    std::string command;
    std::cin >> command;
    std::string arguments;
    std::getline(std::cin, arguments);
    strip(arguments);
    if (!commandMap.contains(command)) return commandError("Command not found");
    return std::invoke(commandMap[command], this, arguments);
}

void RACTFCLI::strip(std::string &str) {
        auto textbegin = std::find_if(str.begin(), str.end(),
                                      [](char c) {
                                          return !std::isspace<char>(c, std::locale::classic());
                                      });
        auto textend = std::find_if(str.rbegin(), str.rend(),
                                    [](char c) {
                                        return !std::isspace<char>(c, std::locale::classic());
                                    });
        str = str.substr(textbegin - str.begin(), textend - str.rend());
}

int RACTFCLI::exec_addCategory(std::string &arguments) {
    m_subcategories.push_back(arguments);
    std::cout << "Added " << arguments << " to the list" << std::endl;
    return EXIT_SUCCESS;
}

int RACTFCLI::exec_helloWorld(std::string &arguments) {
    std::cout << "Hello, World! " << arguments << std::endl;
    return EXIT_SUCCESS;
}

int RACTFCLI::commandError(std::string_view errorMessage) {
    std::cout << "Error: " << errorMessage << std::endl;
    return 0;
}

int RACTFCLI::exec_help(std::string &arguments) {
    if (arguments.length() == 0) {
        std::cout <<
R"==(Welcome to the RACTF CLI from which you can automatically download challenge details in a structured manner, submit
flags and read challenge descriptions on the command line making it easier than ever to start working straight away.

Prerequisites: a valid account.

Command reference:)==" << std::endl;
        for (auto& it : commandRegistration) {
            std::cout << "\t" << it << "\t\t\t\t\t" << commandDescriptions[it] << std::endl;
        }
    } else {
        auto it = commandDescriptions.find(arguments);
        if (it == commandDescriptions.end())
            return commandError("Description for `" + arguments
                                + "` could not be found. Did you type the command correctly?");
        std::cout << commandDescriptions[arguments] << std::endl;
    }
    return EXIT_SUCCESS;
}

int RACTFCLI::exec_clear(std::string &arguments) {
    clearScreen();
    return EXIT_SUCCESS;
}

int RACTFCLI::exec_download(std::string &arguments) {
    // TODO: download (all) files
    return commandError("Operation not currently supported");
}

int RACTFCLI::exec_quit(std::string& arguments) {
    return 1;
}

int RACTFCLI::exec_list(std::string &arguments) {
    // TODO: Only on launch for speed perhaps?
    m_apiConnection.reloadCategories();
    std::cout << "Result3: " << m_apiConnection.categories.serialize() << std::endl;
    for (auto& category : m_apiConnection.categories[U("d")].as_array()) {
        std::cout << category[U("name")].as_string() << "\n";
        for (auto& challenge : category[U("challenges")].as_array()) {
            if (!challenge[U("name")].is_null())
                std::cout << "\t" << challenge[U("score")].as_number().to_int32() << " - "
                    << challenge[U("name")].as_string() << " (" << challenge[U("id")].as_number().to_int32()
                    << ")\n";
        }
    }
    return 0;
}
