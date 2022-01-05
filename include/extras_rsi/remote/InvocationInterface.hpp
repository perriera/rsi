/**
 * @file ServiceType.hpp
 * @author Perry Anderson (perry@exparx.com)
 * @brief InvocationInterface
 * @version 0.1
 * @date 2021-11-30
 *
 * @copyright (C) November 22, 2021 EXPARX INCORPORATED
 *
 */

#ifndef _EXPARX_RSI_INVOCATIONINTERFACE_HPP
#define _EXPARX_RSI_INVOCATIONINTERFACE_HPP

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
#include <extras_rsi/remote/ServiceInterface.hpp>
#include <extras_rsi/sockets/Types.hpp>
#include <extras_rsi/sockets/PortAuthority.hpp>
#include <extras_rsi/remote/ParametersInterface.hpp>
#include <extras_rsi/services/SessionType.hpp>
#include <extras_rsi/sockets/LineBlock.hpp>
#include <extras_rsi/exceptions.hpp>
#include <iostream>

namespace extras {
    namespace rsi {

        /**
         * @brief InvocationInterface
         *
         */
        interface InvocationInterface {

            virtual LinePacket servicesResponse(int socket) pure;
            virtual ServiceTypeList servicesRequest(int socket) pure;

            virtual ServiceTypeList compile(
                const ServiceTypeMap& serviceTypes,
                const SessionInterface& session,
                const ServiceTypeList& list
            ) const pure;

            virtual void decompile(
                const ServiceTypeList& before,
                const ServiceTypeList& after
            ) const pure;

            virtual ServiceTypeList resolve(const ParametersInterface& parameters) pure;

            virtual void invoke(const SessionInterface& session, const ServiceTypeList& list) pure;

        };

    }
}

#endif // _EXPARX_RSI_INVOCATIONINTERFACE_HPP


