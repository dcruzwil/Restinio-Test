//#include <iostream>
//#include "main.h"
//#include <restinio/all.hpp>
//
//template < typename RESP >
//RESP
//init_resp(RESP resp)
//{
//	resp.append_header(restinio::http_field::server, "RESTinio sample server /v.0.2");
//	resp.append_header_date_field();
//	return resp;
//}
//using router_t = restinio::router::express_router_t<>;
//// Create request handler.
//auto create_request_handler()
//{
//	auto router = std::make_shared<router_t >();
//
//	router->http_get(
//		"/json",
//		[](const auto& req, const auto&) {
//			req->create_response()
//				.append_header(restinio::http_field::server, "RESTinio hello world server")
//				.append_header_date_field()
//				.append_header(restinio::http_field::content_type, "text/plain; charset=utf-8")
//				.set_body("Server tag: ....................")
//				.done();
//
//			return restinio::request_accepted();
//		}
//	);
//	return[handler = std::move(router)](const auto& req) {
//		return (*handler)(req);
//	};
//}
//// Create request handler.
//auto create_request_handler1(const std::string& tag)
//{
//	auto router = std::make_shared<router_t >();
//
//	router->http_get(
//		"/",
//		[tag](const auto& req, const auto&) {
//			req->create_response()
//				.append_header(restinio::http_field::server, "RESTinio hello world server")
//				.append_header_date_field()
//				.append_header(restinio::http_field::content_type, "text/plain; charset=utf-8")
//				.set_body("Server tag: " + tag)
//				.done();
//
//			return restinio::request_accepted();
//		}
//	);
//	return[handler = std::move(router)](const auto& req) {
//		return (*handler)(req);
//	};
//}
//
//// Create request handler.
//auto create_request_handler2(const std::string& tag)
//{
//	auto router = std::make_shared< router_t >();
//
//	router->http_get(
//		"/",
//		[tag](const auto& req, const auto&) {
//			req->create_response()
//				.append_header(restinio::http_field::server, "RESTinio hello world server")
//				.append_header_date_field()
//				.append_header(restinio::http_field::content_type, "text/plain; charset=utf-8")
//				.set_body("Handler 2 Server tag: " + tag)
//				.done();
//
//			return restinio::request_accepted();
//		}
//	);
//	return[handler = std::move(router)](const auto& req) {
//		return (*handler)(req);
//	};
//}
//
//int multi_server()
//{
//	// Since RESTinio supports both stand-alone ASIO and boost::ASIO
//	// we specify an alias for a concrete asio namesace.
//	// That's makes it possible to compile the code in both cases.
//	// Typicaly only one of ASIO variants would be used,
//	// and so only asio::* or only boost::asio::* would be applied.
//	namespace asio_ns = restinio::asio_ns;
//
//	try
//	{
//		// External io_context.
//		asio_ns::io_context io_context;
//
//		using server_t = restinio::http_server_t<>;
//		using settings_t = restinio::server_settings_t<>;
//
//		server_t srv1{
//			restinio::external_io_context(io_context),
//			settings_t{}
//				.port(8080)
//				.address("localhost")
//				.request_handler(create_request_handler()) };
//
//		server_t srv2{
//			restinio::external_io_context(io_context),
//			settings_t{}
//				.port(8081)
//				.address("localhost")
//				.request_handler(create_request_handler2("server2")) };
//
//		server_t srv0{
//			restinio::external_io_context(io_context),
//			settings_t{}
//				.port(8080)
//				.address("localhost")
//				.request_handler(create_request_handler()) };
//
//		asio_ns::signal_set break_signals{ io_context, SIGINT };
//		break_signals.async_wait(
//			[&](const asio_ns::error_code& ec, int) {
//				if (!ec)
//				{
//					srv0.close_sync();
//					srv1.close_sync();
//					srv2.close_sync();
//				}
//			});
//
//		asio_ns::post(io_context, [&] {
//			srv1.open_sync();
//			srv2.open_sync();
//			srv0.open_sync();
//			});
//
//		io_context.run();
//
//
//	}
//	catch (const std::exception& ex)
//	{
//		std::cerr << "Error: " << ex.what() << std::endl;
//		return 1;
//	}
//	
//}