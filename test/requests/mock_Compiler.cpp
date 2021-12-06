/**
 * @brief the "MIT/X Consortium License", (adapted for EXPARX.COM)
 *
 * Copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 * Permission is hereby  granted,  free of charge,  to  any  person
 * obtaining a copy of this software and  associated  documentation
 * files   (the  "Software"),  to deal  in   the  Software  without
 * restriction, including  without  limitation the rights  to  use,
 * copy,  modify, merge,  publish,  distribute,  sublicense, and/or
 * sell copies of the  Software, and to permit persons  to whom the
 * Software  is  furnished to  do  so,  subject  to  the  following
 * conditions:
 *
 * (See LICENSE.md for complete details)
 *
 */

#include <extras_rsi/requests/RequestType.hpp>
#include <extras_rsi/sockets/Parameters.hpp>
#include <extras_rsi/sockets/Client.hpp>
#include <iostream>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace std;
using namespace fakeit;

SCENARIO("Mock RequestTypeCompilerInterface", "[RequestTypeCompilerInterface]") {

    rsi::SocketParaneters parameters;
    rsi::PortAuthority portAuthority;
    const char* argv[] = {
        "/home/perry/Projects/extras_rsi/build/socketpool_client",
        "137.184.218.130",
        "8080",
        "data/exparx.webflow.zip",
        "upload",
        "vendor",
        "download" };
    int argc = sizeof(argv) / sizeof(argv[0]);
    parameters.parameters(argc, argv);
    std::string msg = parameters;

    Mock<rsi::RequestTypeCompilerInterface> mock;
    When(Method(mock, compile))
        .AlwaysDo(
            [&msg](const rsi::sockets::ParametersInterface&,
                rsi::PortAuthorityInterface& portAuthority) {
                    if (msg.size() == 0) throw std::string("test exception");
                    extras::rsi::ServiceTypeCompilerVendor vendor;
                    rsi::SocketPoolClient client(msg, vendor);

                    rsi::RequestTypeList list;
                    for (auto request : client.requests()) {
                        auto port = portAuthority.request();
                        std::stringstream ss;
                        ss << request << ' ';
                        ss << client.filename() << ' ';
                        ss << client.ip() << ' ';
                        ss << port;
                        std::string line = ss.str();
                        list.push_back(line);
                    }

                    int socket = std::stoi(client.port());
                    rsi::RequestTypeCompilation compilation(list, socket);

                    // compilation.send_line_block("");

                    auto _compilation = compilation.compilation();
                    auto cmds = vendor.clients(_compilation);
                    for (auto cmd : cmds) {
                        std::cout << "msg received: " << cmd << std::endl;
                    }
                    return compilation;
            });

    rsi::RequestTypeCompilerInterface& i = mock.get();
    i.compile(parameters, portAuthority);
    Verify(Method(mock, compile));
}
