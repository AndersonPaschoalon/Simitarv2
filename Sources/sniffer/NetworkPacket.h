#ifndef _NETWORK_PACKET__H_
#define _NETWORK_PACKET__H_ 1

#include <stdio.h>
#include <string>
#include <iostream>
#include "NetTypes.h"


class NetworkPacket
{
    public:

        NetworkPacket();

        NetworkPacket(std::string comment);

        ~NetworkPacket();

        NetworkPacket(const NetworkPacket& obj);

        NetworkPacket& operator=(NetworkPacket other);

        std::string toString();

        std::string about();

        //
        // Physical
        //

        size_t getPacketId();

        packet_size getPacketSize();

        PacketTimeStamp getTimestamp();

        void setPysical(size_t pktId, packet_size packetSize, PacketTimeStamp& timestamp);

        //
        // Flow Level
        //
        flow_id getFlowId();
        
        void setFlowId(flow_id flowId);

        //
        // Network
        //

        NetworkProtocol getNetworkProtocol();

        bool isIPv4();

        /// @brief 
        /// @return 
        std::string getIPSrcStr();

        /// @brief 
        /// @return 
        std::string getIPDstStr();

        ipv4_address getIPv4Src();

        ipv4_address getIPv4Dst();

        /// @brief 
        /// @return 
        std::string getIPv6Src();

        /// @brief 
        /// @return 
        std::string getIPv6Dst();

        ttl getTtl();

        void setNetwork(NetworkProtocol proto, ipv4_address ipSrc,ipv4_address ipDst);

        void setNetworkV6(NetworkProtocol proto, std::string src, std::string dst);


        //
        // Transport
        //

        TransportProtocol getTransportProtocol();

        bool isTCPIPv4();

        bool isUDPIPv4();

        port_number getPortSrc();

        port_number getPortDst();

        void setTransport(TransportProtocol proto, port_number src, port_number dst);

        //
        // Application
        //

        ApplicationProtocol getApplicationProtocol();

        void setApplication(ApplicationProtocol app);


    private:

        packet_size packetSize;
        PacketTimeStamp timeStamp;
        size_t packetId;
        flow_id flowId;
        NetworkProtocol networkProtocol;
        ipv4_address ipv4Src;
        ipv4_address ipv4Dst;
        std::string ipv6Src;
        std::string ipv6Dst;
        ttl timeToLive;
        TransportProtocol transportProtocol;
        port_number portSrc;
        port_number portDst;
        ApplicationProtocol aplicationProtocol;
        std::string comment;


};


#endif // _NETWORK_PACKET__H_


