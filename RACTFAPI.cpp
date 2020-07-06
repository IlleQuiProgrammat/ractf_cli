#include "RACTFAPI.hpp"
#include <cpprest/http_client.h>
#include <thread>

void RACTFAPI::generateToken(const std::string& uname, const std::string& password, const std::string& otp) {
    web::json::value loginDetails;
    loginDetails[U("username")] = web::json::value::string(uname, false);
    loginDetails[U("password")] = web::json::value::string(password, false);
    if (otp == "-1") {
        loginDetails[U("otp")] = web::json::value::null();
    } else {
        loginDetails[U("otp")] = web::json::value::string(otp);
    }

    auto req = apiClient.request(web::http::methods::POST, "/auth/login/", loginDetails.serialize(),
            U("application/json")).then(
            [](const web::http::http_response& response) {
            if (response.status_code() != 200) {
                throw std::runtime_error("Endpoint /auth/login/ returned " + std::to_string(response.status_code())
                        + " instead of 200.\nMore information:\n" + response.to_string());
            }
            return response.extract_json();
        }
    ).then([this](web::json::value jsonResponse) {
        token = jsonResponse[U("d")][U("token")].as_string();
    });
    req.wait();
}

void RACTFAPI::fetchCTFInformation() {
    web::http::http_request request;
    request.headers().add(U("Authorization"), "Token " + token);
    request.set_request_uri(U("/member/self/"));

    auto req = apiClient.request(request).then(
            [](const web::http::http_response &response) {
                if (response.status_code() != 200) {
                    throw std::runtime_error("Endpoint /member/self/ returned " + std::to_string(response.status_code())
                                             + " instead of 200.\nMore information:\n" + response.to_string());
                }
                return response.extract_json();
            }
    ).then([this](web::json::value jsonResponse) {
        teamName = jsonResponse[U("d")][U("team_name")].as_string();
        CTFName = "RACTF";
    });

    req.wait();
}

void RACTFAPI::reloadCategories() {
    web::http::http_request request;
    request.headers().add(U("Authorization"), "Token " + token);
    request.set_request_uri(U("/challenges/categories/"));

    auto req = apiClient.request(request).then(
            [](const web::http::http_response& response) {
                if (response.status_code() != 200) {
                    throw std::runtime_error("Endpoint /challenges/categories/ returned "
                                + std::to_string(response.status_code()) + " instead of 200.\nMore information:\n"
                                + response.to_string());
                }
                return response.extract_json();
            }
    ).then([this](web::json::value jsonResponse) {
        categories = jsonResponse;
    });

    req.wait();
}