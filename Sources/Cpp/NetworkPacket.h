#include <stdio.h>
#include <string>
#include <iostream>
#include "NetTypes.h"



class NetworkPacket
{
    public:


        NetworkPacket();

        ~NetworkPacket();

        std::string toString();

        //
        // Physical
        //

        unsigned int getPacketSize();

        double getTimestamp();

        void setPysical(unsigned int packetSize, double timestamp);

        //
        // Flow Level
        //
        unsigned long long getFlowId();
        
        void setFlowId(unsigned long long flowId);

        //
        // Network
        //


        NetworkProtocol getNetworkProtocol();

        bool isIPv4();

        std::string getIPSrcStr();

        std::string getIPDstStr();

        unsigned int getIPv4Src();

        unsigned int getIPv4Dst();

        void getIPv6Src(std::string& ipv6);

        void getIPv6Dst(std::string& ipv6);

        void setNetwork(NetworkProtocol proto, unsigned int ipSrc, unsigned int ipDrc);

        void setNetworkV6(NetworkProtocol proto, std::string src, std::string dst);


        //
        // Transport
        //

        TransportProtocol getTransportProtocol();

        bool isTCPIPv4();

        bool isUDPIPv4();

        port_number srcPort();

        port_number dstPort();

        void setTransport(TransportProtocol proto, port_number src, port_number dst);

        //
        // Application
        //


        ApplicationProtocol getApplicationProtocol();



        //
        // Test
        //

        NetworkPacket sampleTcp();

        NetworkPacket sampleUdp();

        NetworkPacket sampleIcmp();

        NetworkPacket sampleHttp();


    private:

};