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

#ifndef _EXPARX_RSICONVERTBYTE_HPP
#define _EXPARX_RSICONVERTBYTE_HPP

#include <extras/interfaces.hpp>
#include <iostream>
#include <vector>

namespace extras {
    namespace rsi {

        /**
         * @brief ByteArray, HexArray
         *
         */
        using ByteArray = std::vector<byte>;
        using HexArray = std::string;

        /**
         * @brief hexToBytes
         * @param hex
         * @return std::vector<byte>
         */
        ByteArray hexToBytes(const HexArray& hex);

        /**
         * @brief bytesToHex
         *
         * @param data
         * @param len
         * @return std::string
         */
        HexArray bytesToHex(byte* data, int len);
        HexArray bytesToHex(ByteArray data);


    }
}

#endif // _EXPARX_RSICONVERTBYTE_HPP


