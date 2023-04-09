#include "DriverLibpcap.h"

DriverLibpcap::DriverLibpcap()
{
    this->active = false;
}

DriverLibpcap::~DriverLibpcap()
{
}

DriverLibpcap::DriverLibpcap(const DriverLibpcap &obj)
{
    this->active = obj.active;
}

DriverLibpcap &DriverLibpcap::operator=(DriverLibpcap other)
{
    if(this != &other)
    {
        this->active = other.active;
    }
    return *this;
}

std::string DriverLibpcap::toString()
{
    return std::string();
}

int DriverLibpcap::listen(const char *deviceName, double captureTimeoutSec, long maxPackets)
{
    this->active = true;
    initialize_libpcap_wrapper();
    std::thread t(start_capture, deviceName, captureTimeoutSec, maxPackets);
    t.detach();
    return 0;
}

int DriverLibpcap::nextPacket(NetworkPacket &packet)
{
    if(this->active == false)
    {
        return ERROR_LISTEN_NOT_CALLED;
    }

    int ret = ERROR_LISTEN_NOT_CALLED;
    bool queueRet = false;
    while (true)
    {
        NetworkPacket* ptrPkt = nullptr;
        queueRet = packetsQueue->try_pop(ptrPkt);
        // 1. the queue is empty, but there are packets to be pushed, stopCapture == 0
        // 2. the queue is empty, but there are no packets to be pushed, stopCapture == 1
        if(queueRet == false)
        {
            if (endOfFile == 1)
            {
                ret  = STOP_CAPTURE_EOF;
                // Set the flag, so doContinue() will return with false, and the loop will break
                this->isLastPacket = true;
                break;
            }
            else if (stopCapture == 1 )
            {
                ret  = STOP_CAPTURE_INTERRUPTED;
                // Set the flag, so doContinue() will return with false, and the loop will break
                this->isLastPacket = true;
                break;
            }
            else
            {
                // sleep for a while, to wait new packets to be captured
                std::this_thread::sleep_for(std::chrono::seconds(1));
                printf("Waiting for the next packet...\n");
            }
        }
        else
        {
            ret = NEXT_PACKET_OK;
            packet = *ptrPkt;
            delete ptrPkt;
            break;
        }        
    }

    // update current timestamp to check the timeout
    this->lastTs = {
        .sec = currentTimeStamp.tv_sec,
        .usec = currentTimeStamp.tv_usec,
    };

    return ret;
}

int DriverLibpcap::stop()
{
    finalize_libpcap_wrapper();
    return 0;
}
