#ifndef _FLOW_ID_CALC__H_
#define _FLOW_ID_CALC__H_ 1

#include <stdio.h>
#include <string>
#include <iostream>
#include <set>
#include <atomic>
#include <unordered_map>

#include "IFlowIdCalc.h"
#include "NetworkPacket.h"
#include "NetTypes.h"
#include "Logger.h"



typedef struct _PortDstSrc
{
    /// @brief transport layer key
    flow_hash dstSrcSumm;

    /// @brief set data
    flow_id flowId;

    bool operator<(const struct _PortDstSrc& other) const 
    {
        return dstSrcSumm < other.dstSrcSumm;
    }    

} PortDstSrc;

/// @brief Transport layer node
typedef struct _TransportLayer
{
    /// @brief key
    TransportProtocol proto;

    /// @brief set for the transport layer flows
    std::set<PortDstSrc>* setPortDstSrc;

    bool operator<(const struct _TransportLayer& other) const 
    {
        return proto < other.proto;
    }    
} TransportLayer;


/// @brief Generic leaf for non-ip network packets
typedef struct _Netv4DstSrc
{
    // Key
    flow_hash dstSrcSumm;
    // flow data
    flow_id flowId;

    bool operator<(const struct _Netv4DstSrc& other) const 
    {
        return dstSrcSumm < other.dstSrcSumm;
    }

} Netv4DstSrc;

/// @brief Generic leaf for non-ip network packets
typedef struct _Netv6DstSrc
{
    // key
    flow_hash dstSrcHash;
    // flow data
    flow_id flowId;

    bool operator<(const struct _Netv6DstSrc& other) const 
    {
        return dstSrcHash < other.dstSrcHash;
    }

} Netv6DstSrc;

/// @brief IPv4 node
typedef struct _Ipv4DstSrc
{
    /// @brief set key
    flow_hash dstSrcSumm;

    /// @brief point to the set of transport layer
    std::set<TransportLayer>* setTransport;


    bool operator<(const _Ipv4DstSrc& other) const 
    {
        return dstSrcSumm < other.dstSrcSumm;
    }

} Ipv4DstSrc;

/// @brief IPv6 node
typedef struct _Ipv6DstSrc
{
    /// @brief set key
    flow_hash dstSrcHash;

    /// @brief point to the set of transport layer
    std::set<TransportLayer>* setTransport;

    bool operator<(const struct _Ipv6DstSrc& other) const 
    {
        return dstSrcHash < other.dstSrcHash;
    }

} Ipv6DstSrc;

/// @brief Network set node
typedef struct _NetworkLayer
{
    /// @brief set key
    NetworkProtocol proto;

    // points to the right network set of the specified protocol
    std::set<Netv4DstSrc>* setNetv4DstSrc = NULL;
    std::set<Netv6DstSrc>* setNetv6DstSrc = NULL;
    std::set<Ipv4DstSrc>* setIpv4DstSrc = NULL;
    std::set<Ipv6DstSrc>* setIpv6DstSrc = NULL;

    bool operator<(const struct _NetworkLayer& other) const 
    {
        return proto < other.proto;
    }
} NetworkLayer;


class FlowIdCalc: public IFlowIdCalc
{
    public:

        FlowIdCalc();

        ~FlowIdCalc();

        // do not allow copy
        FlowIdCalc(const FlowIdCalc& obj) = delete;

        // do not allow copy
        FlowIdCalc& operator=(FlowIdCalc other) = delete;

        std::string toString();

        flow_id setFlowId(NetworkPacket& packet);

        flow_id getCurrentFlowId();

    private:

        std::atomic<flow_id> lastFlowId;

        /// @brief A set that represent the Flow Stack of a given trace.
        /// Structure:
        /// set:NetProtocol -> set:netAddr -> set::TransportProtocol -> set::portAddr
        std::set<NetworkLayer>* netFlowsStack;

        static const flow_hash summPorts(port_number dst, port_number src);

        static const void recoverPorts(flow_hash summ, port_number& dst, port_number& src);

        static const flow_hash summIpv4(ipv4_address dst, ipv4_address src);

        static const void recoverIpv4(flow_hash summ, ipv4_address& dst, ipv4_address& src);

        static const size_t hashStrings(std::string a, std::string b);

        flow_id getNextFlowId();

};

#endif // _FLOW_ID_CALC__H_