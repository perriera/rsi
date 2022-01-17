/**
 * @file Vendor.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief VendorClient, VendorServer
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXPARX_RSISERVICES_MONITOR_CLIENT_HPP
#define _EXPARX_RSISERVICES_MONITOR_CLIENT_HPP

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

#include <extras/interfaces.hpp>
#include <extras_rsi/service/uploader/Client.hpp>
#include <extras_rsi/service/uploader/Server.hpp>
#include <iostream>
#include <sstream>
#include <netinet/in.h>
#include <sys/socket.h>

namespace extras {
    namespace rsi {

        /**
         * @brief concrete class MonitorClient
         *
         */
        concrete class MonitorClient extends UploaderClient {
        public:
            virtual void transfer() override;
        };

        /**
         * @brief monitor_client
         *
         * @param argc
         * @param argv
         * @return int
         */
        int monitor_client(int argc, char const* argv[]);

    }  // namespace rsi

}  // namespace extras

#endif  // _EXPARX_RSISERVICES_MONITOR_CLIENT_HPP
