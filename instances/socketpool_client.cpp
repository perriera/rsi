#include <rsi/sockets/Client.hpp>
#include <rsi/sockets/StatusLine.hpp>
#include <iostream>

using namespace  extras;

int main(int argc, char const* argv[]) {
    try {
        std::cout << rsi::start(argv[0]) << std::endl;
        extras::rsi::ServiceTypeCompilerVendor vendor;
        extras::rsi::SocketPoolClient client(vendor);
        client.parameters(argc, argv);
        client.connect();
        client.transfer();
        std::cout << rsi::pass("File sockets allocated successfully") << std::endl;
        client.close();
        std::cout << rsi::end(argv[0]) << std::endl << std::endl;
        return 0;
    }
    catch (std::exception& ex) {
        std::cout << rsi::fail(ex.what()) << std::endl << std::endl;
        return -1;
    }
}
