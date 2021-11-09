#ifndef _EXPARX_RSISOCKETSPOOL_HPP
#define _EXPARX_RSISOCKETPOOL_HPP

#include <netinet/in.h>
#include <sys/socket.h>

#include <extras/interfaces.hpp>
#include <iostream>
#include <map>
#include <sstream>
#include <vector>

/**
 * @brief
 *
 */

namespace exparx {
    namespace rsi {

        /**
         * @brief SocketPoolInterface
         *
         * The idea is that we assign a port to be the authority on deligating
         * available port numbers, (from a range of port numbers). At the basic
         * level a series of predefined tokens are given to this interface. If all
         * tokens are reconized then a port number is returned for each token.
         *
         * The purpose of a token is to inform the SocketPool instance what type of
         * socket service will be expected to be running on that port. Earlier
         * prototypes to this just returned a single port number. However, it was
         * soon realized that perhaps more than one port is required and to inform
         * the socket pool manager in advance of what type of service to running on
         * that port would be advantageous.
         *
         * This version only returns a port number, a more enhanced version would
         * support IP addresses, (hence supporting socket pools over different IPs).
         *
         */

        using PortNumber = int;
        using Socket = int;
        using PortNumberPool = std::vector<PortNumber>;
        using SocketRequestType = std::string;
        using SocketRequestTypeList = std::vector<SocketRequestType>;
        using SocketRequestTypeMap = std::map<PortNumber, SocketRequestType>;

        using RequestType = std::string;
        using RequestTypeList = std::vector<RequestType>;

        using ServiceType = std::string;
        using ServiceTypeList = std::vector<ServiceType>;
        using ServiceTypeMap = std::map<ServiceType, ServiceType>;

        interface ServiceTypeCompilerInterface {
            virtual ServiceTypeList clients(
                const RequestTypeList& requests) const pure;
            virtual ServiceTypeList servers(
                const RequestTypeList& requests) const pure;
        };

        interface SocketPoolInterface {
            virtual void transfer() const pure;
        };


    }
}

#endif // _EXPARX_RSISOCKETSPOOL_HPP


