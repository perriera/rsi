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

#ifndef _EXPARX_PARCEL_HPP
#define _EXPARX_PARCEL_HPP

#include <extras/interfaces.hpp>
#include <extras/strings.hpp>
#include <rsi/sockets/Types.hpp>
#include <rsi/bin2hex/ConvertFile.hpp>
#include <rsi/exceptions.hpp>
#include <extras/crcs.hpp>
#include <rsi/parcel/Exceptions.hpp>
#include <rsi/parcel/Line.hpp>
#include <iostream>
#include <sstream>
#include <netinet/in.h>
#include <sys/socket.h>

namespace extras {
    namespace rsi {
        /**
         * @brief ParcelInterface
         *
         *   build/rsi_client 127.0.0.1 8080 transfer send.txt
         *   ss >> prg >> filename >> ip >> port;
         *
         */

        interface ParcelInterface {

            // virtual BinFile loadBin(const Filename& filename) const pure;
            // virtual HexFile convertToHex() const pure;
            // virtual HexFile hexFile() const pure;

            virtual const Parameter& original() const pure;
            virtual const Parameter& hexed() const pure;
            virtual const Parameter& packed() const pure;
            virtual const Parameter& duplicate() const pure;

            virtual void pack() const pure;
            virtual void unpack() const pure;
            virtual void merge() const pure;
            virtual bool verify_integrity() const pure;
            virtual void clean() const pure;
            virtual void cat() const pure;
            virtual void dir() const pure;
            virtual void unzip() const pure;

        };

        concrete class Parcel  implements ParcelInterface {

            Parameter _parcel;
            Parameter _hexed;
            Parameter _packed;
            Parameter _unpacked;

        public:
            Parcel(const Parameter& parcel) : _parcel(parcel) {
                _hexed = _parcel + "_hexed.txt";
                _packed = _parcel + "_packed.txt";
                _unpacked = _parcel + "_duplicate.bin";
            }
            virtual const Parameter& original() const override { return _parcel; }
            virtual const Parameter& hexed() const override { return _hexed; }
            virtual const Parameter& packed() const override { return _packed; }
            virtual const Parameter& duplicate() const override { return _unpacked; }

            virtual void pack() const override;
            virtual void unpack() const override;
            virtual void merge() const override;
            virtual bool verify_integrity() const override;
            virtual void clean() const override;
            virtual void cat() const override;
            virtual void dir() const override;
            virtual void unzip() const override;

        };

    }  // namespace rsi

}  // namespace extras

#endif  // _EXPARX_PARCEL_HPP
