#include <rsi/uploader/Uploader.hpp>
#include <extras/strings.hpp>
#include <rsi/parcel/Wrap.hpp>
#include <rsi/parcel/Parcel.hpp>
#include <rsi/parcel/ParcelImploder.hpp>
#include <rsi/sockets/Types.hpp>
#include <extras/filesystem/paths.hpp>
#include <extras/strings.hpp>
#include <rsi/exceptions.hpp>
#include <ng_imploder/imploder/Imploder.hpp>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <extras/filesystem/system.hpp>
#include <extras/status/StatusLine.hpp>

#include "../unittesting/catch.hpp"
#include "../unittesting/fakeit.hpp"

using namespace extras;
using namespace fakeit;
using namespace std;
namespace fs = std::filesystem;

SCENARIO("Mock UploaderInterface: current", "[UploaderInterface]") {

    rsi::Parameter original = ~extras::Paths("data/exparx.webflow.zip");
    rsi::Parameter _filename = original;
    rsi::Parameter wrapped_parcel;
    rsi::Parameter unWrapped_parcel;

    Mock<rsi::UploaderInterface> uploader_client;
    Mock<rsi::UploaderInterface> uploader_server;
    Mock<rsi::UploaderInterface> vendor_client;
    Mock<rsi::UploaderInterface> vendor_server;
    Mock<rsi::UploaderInterface> downloader_client;
    Mock<rsi::UploaderInterface> downloader_server;

    /**
     * @brief uploader_client, transfer
     *
     * original file is wrapped into a file called wrapped_parcel
     * and sent over a socket to uploader_server
     *
     */
    When(Method(uploader_client, transfer))
        .AlwaysDo(
            [&_filename, &wrapped_parcel]() {
                rsi::ParcelImploder parcelImploder;
                auto wrapped = parcelImploder.wrap(_filename);
                wrapped_parcel = wrapped;
                // extras::rsi::send_file2(wrapped, this->_sockfd);
                std::cout << extras::pass(wrapped) << std::endl;
                std::cout << extras::pass(" uploaded") << std::endl;
            });

    /**
     * @brief uploader_server, transfer
     *
     * wrapped_parcel is unwrapped into a file named the same as
     * original file and written to the server disk
     *
     */
    When(Method(uploader_server, transfer))
        .AlwaysDo(
            [&_filename, &unWrapped_parcel]() {
                rsi::ParcelImploder parcelImploder;
                parcelImploder.unWrap(_filename);
                parcelImploder.merge(_filename);
                auto original = parcelImploder.clean(_filename);
                unWrapped_parcel = original;
                // extras::rsi::write_file(original, this->_new_sock);
                std::cout << extras::pass(_filename) << std::endl;
                std::cout << extras::pass(" uploaded") << std::endl;
            });

    /**
     * @brief vendor_client, transfer
     *
     * does nothing
     *
     */

    When(Method(vendor_client, transfer))
        .AlwaysDo(
            []() {
                std::cout << extras::pass(" uploaded") << std::endl;
            });

    /**
     * @brief vendor_server, transfer
     *
     * looks for a file of the original file name and processes it
     * when it is finished the updated file is the same name as the
     * original file
     *
     */

    When(Method(vendor_server, transfer))
        .AlwaysDo(
            [&unWrapped_parcel, &original]() {
                REQUIRE(unWrapped_parcel == original);
                std::cout << extras::pass(unWrapped_parcel) << std::endl;
                std::cout << extras::pass(" uploaded") << std::endl;
            });

    /**
     * @brief downloader_server, transfer
     *
     * immediate looks for a file of the original file name
     * and wraps it as wrapped_parcel for transport before
     * sending it over the socket
     *
     */
    When(Method(downloader_server, transfer))
        .AlwaysDo(
            [&_filename, &wrapped_parcel, &original]() {
                rsi::ParcelImploder parcelImploder;
                auto wrapped = parcelImploder.wrap(_filename);
                wrapped_parcel = wrapped;
                // extras::rsi::send_file2(wrapped, this->_new_sock);
                std::cout << extras::pass(wrapped) << std::endl;
                std::cout << extras::pass(" downloaded") << std::endl;
            });

    /**
     * @brief downloader_client, transfer
     *
     * immediate looks for a file of the wrapped file name
     * and unwraps it to the orginal file name after receiving
     * it from the socket
     *
     */
    When(Method(downloader_client, transfer))
        .AlwaysDo(
            [&_filename, &unWrapped_parcel]() {
                rsi::ParcelImploder parcelImploder;
                parcelImploder.unWrap(_filename);
                parcelImploder.merge(_filename);
                auto original = parcelImploder.clean(_filename);
                unWrapped_parcel = original;
                // extras::rsi::write_file(original, this->_sockfd);
                std::cout << extras::pass(original) << std::endl;
                std::cout << extras::pass(" downloaded") << std::endl;
            });

    rsi::ParcelImploder imploder;
    imploder.clean(original);

    rsi::UploaderInterface& i_uploader_client = uploader_client.get();
    rsi::UploaderInterface& i_uploader_server = uploader_server.get();
    rsi::UploaderInterface& i_vendor_client = vendor_client.get();
    rsi::UploaderInterface& i_vendor_server = vendor_server.get();
    rsi::UploaderInterface& i_downloader_client = downloader_client.get();
    rsi::UploaderInterface& i_downloader_server = downloader_server.get();

    REQUIRE(fs::exists(original));
    i_uploader_client.transfer();
    i_uploader_server.transfer();
    i_vendor_client.transfer();
    i_vendor_server.transfer();
    i_downloader_server.transfer();
    i_downloader_client.transfer();
    REQUIRE(fs::exists(original));
    Verify(Method(uploader_client, transfer));
    Verify(Method(uploader_server, transfer));
    Verify(Method(vendor_client, transfer));
    Verify(Method(vendor_server, transfer));
    Verify(Method(downloader_server, transfer));
    Verify(Method(downloader_client, transfer));

    if (fs::exists("send.txt"))
        fs::remove("send.txt");
}
