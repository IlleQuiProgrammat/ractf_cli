#include "RACTFCLI.hpp"

int main() {
    RACTFCLI cli("http://localhost:8080/", "token");
    cli.run();
    std::cin.get();
    return 0;
}
