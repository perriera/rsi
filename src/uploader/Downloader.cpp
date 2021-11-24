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
     * @brief Vendor Client/Server ::transfer()
     *
     */

    rsi::Lock rsi::DownloaderServer::lock(const rsi::Lock& lock) const {
        rsi::FileNotFoundException::assertion(lock, __INFO__);
        rsi::ParcelImploder parcelImploder;
        auto wrapped = parcelImploder.wrap(lock);
        rsi::FileNotFoundException::assertion(wrapped, __INFO__);
        send(wrapped);
        parcelImploder.clean(lock);
        return lock;
    }
    rsi::Lock rsi::DownloaderServer::unlock(const rsi::Lock& lock) const {
        auto status = read_line();
        std::cout << extras::pass(filename()) << std::endl;
        std::cout << extras::pass(status) << std::endl;
        std::cout << extras::pass("send_file2 successful") << std::endl;
        return lock;
    }

    void rsi::DownloaderServer::transfer() const {
        unlock(lock(filename()));
        // auto fn = filename();
        // rsi::FileNotFoundException::assertion(fn, __INFO__);
        // rsi::ParcelImploder parcelImploder;
        // auto wrapped = parcelImploder.wrap(fn);
        // rsi::FileNotFoundException::assertion(wrapped, __INFO__);
        // send(wrapped);
        // std::cout << extras::pass("send_file2 successful") << std::endl;
        // std::string line = read_line();
        // std::cout << extras::pass(filename()) << std::endl;
        // std::cout << extras::pass(line) << std::endl;
    }

    rsi::Lock rsi::DownloaderClient::lock(const rsi::Lock& filename) const {
        rsi::ParcelImploder parcelImploder;
        auto wrappedName = parcelImploder.wrapped(filename);
        wrappedName = write(wrappedName);
        return filename;
        // // rsi::FileNotFoundException::assertion(lock, __INFO__);
        // // rsi::ParcelImploder parcelImploder;
        // // auto wrapped = parcelImploder.wrap(lock);
        // // rsi::FileNotFoundException::assertion(wrapped, __INFO__);
        // // send(wrapped);
        // // parcelImploder.clean(lock);
        // return lock;
    }
    rsi::Lock rsi::DownloaderClient::unlock(const rsi::Lock& filename) const {
        auto fn = filename;
        rsi::ParcelImploder parcelImploder;
        auto wrappedName = parcelImploder.wrapped(fn);
        auto from = fn;
        fn = extras::replace_all(fn, "data/", client_dir);
        rsi::FileNotFoundException::assertion(wrappedName, __INFO__);
        auto to = fn;
        auto cmd = "cp " + from + " " + to;
        SystemException::assertion(cmd, __INFO__);
        parcelImploder.unWrap(fn);
        parcelImploder.merge(fn);
        auto original = parcelImploder.clean(fn);
        std::cout << extras::pass(filename) << std::endl;
        std::cout << extras::pass("write_file successful") << std::endl;
        std::string msg = "downloader completed";
        send_line(msg);
        // auto status = i_semaphore.read_line();
        // std::cout << extras::pass(filename) << std::endl;
        // std::cout << extras::pass(status) << std::endl;
        // std::cout << extras::pass("send_file2 successful") << std::endl;
        return filename;

        // auto status = read_line();
        // std::cout << extras::pass(filename()) << std::endl;
        // std::cout << extras::pass(status) << std::endl;
        // std::cout << extras::pass("send_file2 successful") << std::endl;
        // return lock;
    }

    void rsi::DownloaderClient::transfer() const {
        unlock(lock(filename()));
        // auto fn = filename();
        // rsi::ParcelImploder parcelImploder;
        // auto wrappedName = parcelImploder.wrapped(fn);
        // wrappedName = write(wrappedName);
        // auto from = fn;
        // static std::string client_dir = "data/client/";
        // fn = extras::replace_all(fn, "data/", client_dir);
        // rsi::FileNotFoundException::assertion(wrappedName, __INFO__);
        // auto to = fn;
        // auto cmd = "cp " + from + " " + to;
        // SystemException::assertion(cmd, __INFO__);
        // parcelImploder.unWrap(fn);
        // parcelImploder.merge(fn);
        // auto original = parcelImploder.clean(fn);
        // std::cout << extras::pass(fn) << std::endl;
        // std::cout << extras::pass("write_file successful") << std::endl;
        // std::string msg = "downloader completed";
        // send_line(msg);
    }

}  // namespace extras
