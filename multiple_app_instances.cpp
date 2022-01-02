#include <restinio/all.hpp>
#include "main.h"

using namespace restinio;

template<typename T>
std::ostream& operator<<(std::ostream& to, const optional_t<T>& v) {
    if (v) to << *v;
    return to;
}

int multiple_app_instances(int portno) {
    // Create express router for our service.
    auto router = std::make_unique<router::express_router_t<>>();
    router->http_get(
        "/",
        [portno](auto req, auto params) {
            const auto qp = parse_query(req->header().query());
            return req->create_response()
                .set_body(
                    "Hello World " + std::to_string(portno)
                    /*fmt::format("meter_id={} (year={}/mon={}/day={})",
                        cast_to<int>(params["meter_id"]),
                        opt_value<int>(qp, "year"),
                        opt_value<int>(qp, "mon"),
                        opt_value<int>(qp, "day"))*/
                )
                .done();
        });

    router->non_matched_request_handler(
        [](auto req) {
            return req->create_response(restinio::status_not_found()).connection_close().done();
        });

    // Launching a server with custom traits.
    struct my_server_traits : public default_single_thread_traits_t {
        using request_handler_t = restinio::router::express_router_t<>;
    };

    restinio::run(
        restinio::on_this_thread<my_server_traits>()
        .address("localhost")
        .port(portno)
        .handle_request_timeout(std::chrono::milliseconds(10000))
        .separate_accept_and_create_connect(true)
        .request_handler(std::move(router)));

    return 0;
}