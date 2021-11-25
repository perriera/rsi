#include <rsi/uploader/Uploader.hpp>
#include <rsi/uploader/Downloader.hpp>
#include <rsi/subsystem.hpp>
#include <rsi/exceptions.hpp>
#include <extras/strings.hpp>
#include <extras/devices/ansi_colors.hpp>
#include <extras/filesystem/paths.hpp>
#include <rsi/parcel/Parcel.hpp>
#include <iostream>
#include <filesystem>
#include <extras/status/StatusLine.hpp>
#include <rsi/parcel/Wrap.hpp>
#include <extras/filesystem/system.hpp>

using namespace std;
namespace fs = std::filesystem;

namespace extras {

    /**
     * @brief Uploader Client/Server ::transfer()
     *
     */
    rsi::Lock rsi::UploaderClient::lock(const rsi::Lock& lock) const {
        rsi::FileNotFoundException::assertion(lock, __INFO__);
        rsi::ParcelImploder parcelImploder;
        auto wrapped = parcelImploder.wrap(lock);
        rsi::FileNotFoundException::assertion(wrapped, __INFO__);
        send(wrapped);
        return lock;
    }
    rsi::Lock rsi::UploaderClient::unlock(const rsi::Lock& lock) const {
        auto status = read_line();
        rsi::ParcelImploder parcelImploder;
        parcelImploder.clean(lock);
        RemoteDiedException::assertion(status, __INFO__);
        std::cout << extras::pass(lock) << std::endl;
        std::cout << extras::pass(status) << std::endl;
        std::cout << extras::pass("send_file2 successful") << std::endl;
        return lock;
    }

    void rsi::UploaderClient::transfer() const {
        unlock(lock(filename()));
    }

    rsi::Lock rsi::UploaderServer::lock(const rsi::Lock& lock) const {
        rsi::ParcelImploder parcelImploder;
        auto wrappedName = parcelImploder.wrapped(lock);
        return write(wrappedName);
    }
    rsi::Lock rsi::UploaderServer::unlock(const rsi::Lock& lock) const {
        rsi::ParcelImploder parcelImploder;
        parcelImploder.unWrap(filename());
        parcelImploder.merge(filename());
        auto original = parcelImploder.clean(filename());
        send_line("uploader completed");
        std::cout << extras::pass(filename()) << std::endl;
        std::cout << extras::pass("write_file successful") << std::endl;
        return original;
    }

    void rsi::UploaderServer::transfer() const {
        unlock(lock(filename()));
    }

}  // namespace extras
