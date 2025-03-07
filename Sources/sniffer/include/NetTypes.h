#ifndef _NET_TYPES__H_ 
#define _NET_TYPES__H_ 1

#include <string>
#include <sstream>
#include <iomanip>
#include "cpptools.h"

///////////////////////////////////////////////////////////////////////////////
// CONSTANTS
///////////////////////////////////////////////////////////////////////////////


#define MAX_PORT_VALUE       0xFFFF
#define PORT_OFFSET_VALUE    0x10000
#define PORT_NONE            0x0
#define PORT_LSB_MASK        0xFFFF
#define PORT_MSB_MASK        0xFFFF0000

#define MAX_IPV4_VALUE       0xFFFFFFFF
#define IPV4_OFFSET_VALUE    0x100000000
#define IPV4_NONE            0x0
#define IPV6_NONE            ""
#define IPV4_LSB_MASK        0xFFFFFFFF
#define IPV4_MSB_MASK        0xFFFFFFFF00000000

#define FLOW_ID_NONE         0


///////////////////////////////////////////////////////////////////////////////
// DATA TYPES
///////////////////////////////////////////////////////////////////////////////

// TODO - verificar tipo e conversão
typedef long               ts_sec;
typedef long               ts_usec;
typedef unsigned int       packet_size;
typedef unsigned short     ttl;
typedef unsigned short     port_number; 
typedef unsigned int       ipv4_address;
typedef size_t             flow_id;
typedef unsigned long int  flow_hash;
// typedef unsigned short     protocol_stack; 
typedef unsigned int       protocol_stack; 

std::string hex_to_dotted_decimal(ipv4_address hexAddress);

double inter_arrival(const struct timeval & t0, const struct timeval & t1);

timeval delta(const struct timeval & t0, const struct timeval & t1);


///////////////////////////////////////////////////////////////////////////////
// Protocols
///////////////////////////////////////////////////////////////////////////////


#define PROTOCOL_ETHERNET              "ethernet"
#define PROTOCOL_IEEE_802_11           "ieee802.11"

enum class LinkProtocol
{
    NONE,
    ETHERNET,
    IEEE_802_11,
};

enum class NetworkProtocol
{   
    NONE,
    IPv4,
    IPv6,
    ARP,
    RARP,
    LOOPBACK,
    WOL,
    ATA,
};

enum class TransportProtocol
{
    NONE,
    TCP,
    UDP,
    ICMP,
    ICMPv6,
    DCCP,
    SCTP,
    IGMP,
};

enum class ApplicationProtocol
{
    NONE,
    BGP,
    DHCP,
    DNS,
    FTP,
    IMAP,
    HTTP,
    HTTPS,
    MDNS,
    NTP,
    POP3,
    QUIC,
    RTP,
    SSDP,
    SIP,
    SSH,
    SNMP,
    SMTP,
    SMTPS,
    Telnet,
    TFTP,
    TLS_SSL,
};

std::ostream& operator<<(std::ostream& os, const LinkProtocol& n);
std::ostream& operator<<(std::ostream& os, const NetworkProtocol& n);
std::ostream& operator<<(std::ostream& os, const TransportProtocol& n);
std::ostream& operator<<(std::ostream& os, const ApplicationProtocol& n);

std::string to_string(LinkProtocol protocol);
std::string to_string(NetworkProtocol protocol);
std::string to_string(TransportProtocol protocol);
std::string to_string(ApplicationProtocol protocol);

/// @brief Compress the network protocols into a bitmap.
/// @param n Network protocol enum.
/// @param t Transport protocol enum.
/// @param a Application protocol enum.
/// @return The bitmap.
protocol_stack zip_stack(NetworkProtocol n, TransportProtocol t, ApplicationProtocol a);

/// @brief Compress two port numbers into a unsigned long
/// @param dst 
/// @param src 
/// @return 
flow_hash zip_ports(port_number dst, port_number src);

/// @brief Compress two IPV4 adresses into a unsigned long.
/// @param dst 
/// @param src 
/// @return 
flow_hash zip_ipv4(ipv4_address dst, ipv4_address src);

/// @brief 
/// @param a 
/// @param b 
/// @return 
size_t hash_strings(std::string a, std::string b);

/// @brief 
/// @param stc 
/// @return 
LinkProtocol to_link_protocol(const char* stc);

/// @brief Returns the Network Protocol from the bitmap protocol stack.
/// @param stack Bitmap.
/// @return Network Protocol Enum.
NetworkProtocol to_network_protocol(protocol_stack stack);

/// @brief Returns the Transport Protocol from the bitmap protocol stack.
/// @param stack Bitmap.
/// @return Transport Protocol Enum.
TransportProtocol to_transport_protocol(protocol_stack stack);

/// @brief Returns the Application Protocol from the bitmap protocol stack.
/// @param stack Bitmap.
/// @return Application Protocol Enum.
ApplicationProtocol to_application_protocol(protocol_stack stack);

ipv4_address pa_byte_to_int(const uint8_t arp_spa[4]);

/// @brief 
/// @param summ 
/// @param dst 
/// @param src 
void recover_ipv4(flow_hash summ, ipv4_address &dst, ipv4_address &src);

void recover_ipv4_str(flow_hash summ, std::string& dst, std::string& src);

void recover_ports(flow_hash summ, port_number &dst, port_number &src);

ApplicationProtocol estimate_application_protocol_v01(TransportProtocol proto, uint16_t src_port, uint16_t dst_port);


#endif // _NET_TYPES__H_