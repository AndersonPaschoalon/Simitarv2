#include "EtherDummy.h"

EtherDummy::EtherDummy()
{
    printf("EtherDummy\n");
    this->vecPackets = new std::vector<NetworkPacket>();
    this->currentElement = -1;
    this->active = false;
}

EtherDummy::~EtherDummy()
{
    this->vecPackets->clear();
    delete this->vecPackets;
}

EtherDummy::EtherDummy(const EtherDummy &obj)
{
    this->active = obj.active;
    this->currentElement = obj.currentElement;
    this->nPackets = obj.nPackets;
    this->deviceName = obj.deviceName;
    this->vecPackets = new std::vector<NetworkPacket>();
    for (int i = 0; i < obj.vecPackets->size(); i++)
    {
        this->vecPackets->push_back(obj.vecPackets->at(i));
    }

}

EtherDummy &EtherDummy::operator=(EtherDummy other)
{
    if(this != &other)
    {
        this->active = other.active;
        this->currentElement = other.currentElement;
        this->nPackets = other.nPackets;
        this->deviceName = other.deviceName;
        this->vecPackets = new std::vector<NetworkPacket>();
        for (int i = 0; i < other.vecPackets->size(); i++)
        {
            this->vecPackets->push_back(other.vecPackets->at(i));
        }
    }
    return *this;
}

std::string EtherDummy::toString()
{
    return std::string("{ active:") + std::to_string(this->active) + 
           std::string(", currentElement:") + std::to_string(this->currentElement) +
           std::string(", nPackets:") + std::to_string(this->nPackets) +
           std::string(", deviceName:") + this->deviceName + std::string("}");
}

int EtherDummy::listen(const char* deviceName, double captureTimeoutSec, long maxPacketCounter)
{
    this->setListenVars(deviceName, captureTimeoutSec, maxPacketCounter);
    int nElements = 0;
    int timeStamp = 0.0;
    PacketTimeStamp ts = {.sec=0, .usec=0};
    packet_size size0 = 64;
    packet_size size1 = 128;
    packet_size size2 = 512;
    packet_size size3 = 1024;
    ipv4_address addr1 = 0xFFFF1212; // 255.255.18.18
    ipv4_address addr2 = 0xFFFF0015; // 255.255.0.21
    port_number port1 = 0x00FF; // 255
    port_number port2 = 0xFF00; // 65280
    size_t pktId = 0;
    this->active = true;

    // Flow 1
    pktId++;
    NetworkPacket p1 = NetworkPacket("Flow 1, ip, addr1, addr2, tcp, port1, port2");
    p1.setPysical(pktId, size0, ts);
    p1.setNetwork(NetworkProtocol::IPv4, addr1, addr2);
    p1.setTransport(TransportProtocol::TCP, port1, port2);
    p1.setApplication(ApplicationProtocol::HTTP);

    // Flow 2
    pktId++;
    ts.sec += 1;
    NetworkPacket p2 = NetworkPacket("Flow 2, ip, addr2, addr1, tcp, port1, port2");
    p2.setPysical(pktId, size1, ts);
    p2.setNetwork(NetworkProtocol::IPv4, addr2, addr1);
    p2.setTransport(TransportProtocol::TCP, port1, port2);
    p2.setApplication(ApplicationProtocol::HTTP);

    // Flow 3
    pktId++;
    ts.sec += 1;
    NetworkPacket p3 = NetworkPacket("Flow 3, ip, addr2, addr1, tcp, port2, port1");
    p3.setPysical(pktId, size2, ts);
    p3.setNetwork(NetworkProtocol::IPv4, addr2, addr1);
    p3.setTransport(TransportProtocol::TCP, port2, port1);
    p3.setApplication(ApplicationProtocol::HTTP);

    // Flow 3
    pktId++;
    ts.sec += 1;
    NetworkPacket p4 = NetworkPacket("Flow 3, ip, addr2, addr1, tcp, port2, port1");
    p4.setPysical(pktId, size1, ts);
    p4.setNetwork(NetworkProtocol::IPv4, addr2, addr1);
    p4.setTransport(TransportProtocol::TCP, port2, port1);
    p4.setApplication(ApplicationProtocol::HTTP);

    // Flow 4
    pktId++;
    ts.sec += 1;
    NetworkPacket p5 = NetworkPacket("Flow 4, ip, addr2, addr1, udp, port2, port1");
    p5.setPysical(pktId, size0, ts);
    p5.setNetwork(NetworkProtocol::IPv4, addr2, addr1);
    p5.setTransport(TransportProtocol::UDP, port2, port1);
    p5.setApplication(ApplicationProtocol::HTTP);

    // Flow 4
    pktId++;
    ts.sec += 1;
    NetworkPacket p6 = NetworkPacket("Flow 4, ip, addr2, addr1, udp, port2, port1");
    p6.setPysical(pktId, size1, ts);
    p6.setNetwork(NetworkProtocol::IPv4, addr2, addr1);
    p6.setTransport(TransportProtocol::UDP, port2, port1);
    p6.setApplication(ApplicationProtocol::HTTP);

    // Flow 5
    pktId++;
    ts.sec += 1;
    NetworkPacket p7 = NetworkPacket("Flow 5, icmp, addr2, addr1");
    p7.setPysical(pktId, size2, ts);
    p7.setNetwork(NetworkProtocol::ICMP, addr2, addr1);

    // Flow 6
    pktId++;
    ts.sec += 1;
    NetworkPacket p8 = NetworkPacket("Flow 6, icmp, addr1, addr2");
    p8.setPysical(pktId, size3, ts);
    p8.setNetwork(NetworkProtocol::ICMP, addr1, addr2);

    //  Flow 6
    pktId++;
    ts.sec += 1;
    NetworkPacket p9 = NetworkPacket("Flow 6, icmp, addr1, addr2");
    p9.setPysical(pktId, size3, ts);
    p9.setNetwork(NetworkProtocol::ICMP, addr1, addr2);

    // Flow 7
    pktId++;
    ts.sec += 1;
    NetworkPacket p10 = NetworkPacket("Flow 7, arp, addr1, addr2");
    p10.setPysical(pktId, size3, ts);
    p10.setNetwork(NetworkProtocol::ARP, addr1, addr2);

    // Flow 8
    pktId++;
    ts.sec += 1;
    NetworkPacket p11 = NetworkPacket("Flow 8, arp, addr2, addr1");
    p11.setPysical(pktId, size0, ts);
    p11.setNetwork(NetworkProtocol::ARP, addr2, addr1);

    this->vecPackets->push_back(p1);
    this->vecPackets->push_back(p2);
    this->vecPackets->push_back(p3);
    this->vecPackets->push_back(p4);
    this->vecPackets->push_back(p5);
    this->vecPackets->push_back(p6);
    this->vecPackets->push_back(p7);
    this->vecPackets->push_back(p8);
    this->vecPackets->push_back(p9);
    this->vecPackets->push_back(p10);
    this->vecPackets->push_back(p11);

    return  DEVICE_SUCCESS;
}

int EtherDummy::listen(const char *deviceName)
{
    return this->listen(deviceName, 0, -1);
}

int EtherDummy::nextPacket(NetworkPacket &packet)
{
    if(this->active == false)
    {
        return ERROR_LISTEN_NOT_CALLED;
    }
    this->currentElement++;
    if (this->currentElement >= this->vecPackets->size())
    {
        this->currentElement = 0;
    }
    packet = this->vecPackets->at(this->currentElement);

    // update packet id
    size_t count = (size_t)this->packetCounter;
    packet_size size = packet.getPacketSize();
    PacketTimeStamp ts = packet.getTimestamp();
    packet.setPysical(count, size, ts);

    // update parent class state
    this->updatePacketCounter();

    return NEXT_PACKET_OK;
}

int EtherDummy::stop()
{
    this->currentElement = -1;
    this->nPackets = 0;
    this->vecPackets->clear();
    return DEVICE_SUCCESS;
}
