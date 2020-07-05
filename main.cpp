#include "RACTFCLI.hpp"
#include <cpprest/http_client.h>
int main() {
    web::uri endpoint = U("http://localhost:8080/");
    RACTFCLI cli(endpoint, "local", "password", -1);
    cli.run();
    return 0;
}
