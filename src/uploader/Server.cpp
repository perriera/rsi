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
 * The above copyright notice and  this permission  notice shall be
 * included in all copies or  substantial portions of the Software.
 *
 * THE SOFTWARE IS  PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESSED  OR   IMPLIED,  INCLUDING   BUT  NOT  LIMITED  TO  THE
 * WARRANTIES OF MERCHANTABILITY, FITNESS FOR A  PARTICULAR PURPOSE
 * AND NON-INFRINGEMENT.  IN  NO  EVENT  SHALL EXPARX  INCORPORATED
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER  IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING  FROM, OUT  OF
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR  OTHER DEALINGS
 * IN THE SOFTWARE.
 *
 * Except  as  contained  in this  notice, the  name of  the EXPARX
 * INCORPORATED shall not  be used in  advertising or  otherwise to
 * promote the sale, use or other dealings in this Software without
 * prior written authorization from EXPARX INCORPORATED.
 *
 * exparx.com and www.exparx.com  are domain names  registered with
 * EXPARX INCORPORATED, (other GPL-themed licenses are included).
 *
 */

#include <arpa/inet.h>
#include <unistd.h>

#include <rsi/uploader/Uploader.hpp>
#include <rsi/subsystem.hpp>
#include <rsi/exceptions.hpp>
#include <extras/strings.hpp>
#include <iostream>
#include <filesystem>
#include <extras/status/StatusLine.hpp>
#include <rsi/parcel/Wrap.hpp>
#include <extras/filesystem/system.hpp>

using namespace std;
namespace fs = std::filesystem;

namespace extras {

    /**
     * @brief UploaderServer::connect()
     *
     */
    void rsi::UploaderServer::connect() {
        this->_sockfd = extras::rsi::configure_serversocket(
            ip().c_str(), stoi(port()), _server_addr);
        socklen_t addr_size = sizeof(_new_addr);
        this->_new_sock =
            accept(this->_sockfd, (struct sockaddr*)&_new_addr, &addr_size);
        if (_new_sock == -1) {
            ::close(this->_sockfd);
            throw RSIException("Timeout on uploader_server accept", __INFO__);
        }
    }

    void rsi::UploaderServer::close() const {
        ::close(this->_new_sock);
        ::close(this->_sockfd);
    }

    void rsi::UploaderServer::send(const Filename& filename) const {
        extras::rsi::send_file2(filename, this->_new_sock);
    }

    void rsi::UploaderServer::send_line(const rsi::UploaderStatus& msg) const {
        extras::rsi::send_line(msg, this->_new_sock);
    }

    rsi::UploaderStatus rsi::UploaderServer::read_line() const {
        return extras::rsi::read_line(this->_new_sock);
    }

    rsi::Filename rsi::UploaderServer::write(const Filename& filename) const {
        extras::rsi::write_file(filename, this->_new_sock);
        return filename;
    }

    /**
     * @brief UploaderServer::lock()
     *
     * @param lock
     * @return rsi::Lock
     */
    rsi::Lock rsi::UploaderServer::lock(const rsi::Lock& lock) const {
        rsi::ParcelImploder parcelImploder;
        auto wrappedName = parcelImploder.wrapped(lock);
        return write(wrappedName);
    }

    /**
     * @brief UploaderServer::unlock()
     *
     * @return rsi::Lock
     */
    rsi::Lock rsi::UploaderServer::unlock(const rsi::Lock&) const {
        rsi::ParcelImploder parcelImploder;
        parcelImploder.unWrap(filename());
        parcelImploder.merge(filename());
        auto original = parcelImploder.clean(filename());
        send_line("uploader completed");
        std::cout << extras::pass(filename()) << std::endl;
        std::cout << extras::pass("write_file successful") << std::endl;
        return original;
    }

    /**
     * @brief UploaderServer::transfer()
     *
     */
    void rsi::UploaderServer::transfer() const {
        unlock(lock(filename()));
    }

}  // namespace extras
