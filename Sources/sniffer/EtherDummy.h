#ifndef _ETHER_DUMMY__H__  
#define _ETHER_DUMMY__H__ 1

#include <vector>
#include "NetworkPacket.h"
#include "ICaptureDriver.h"

/// @brief This class creates some fixed pre-defined packets. For test purpose only.
class EtherDummy: public ICaptureDriver
{
    public:

        EtherDummy();

        ~EtherDummy();

        int listen(std::string deviceName, time_stamp captureTimeoutSec = 0);

        int nextPacket(NetworkPacket& packet);

        int stop();

    private:

        bool active;
        int currentElement;
        int nPackets;
        std::vector<NetworkPacket>* vecPackets;

};

#endif // _ETHER_DUMMY__H__