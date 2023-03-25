#ifndef _UNITY_TESTS__H_
#define _UNITY_TESTS__H_ 1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include "UnityTests.h"
#include "EtherDummy.h"
#include "FlowIdCalc.h"
#include "NetworkPacket.h"
#include "Logger.h"
#include "ILocalDbService.h"
#include "LocalDbServiceV1_Naive.h"
#include "ISniffer.h"
#include "Sniffer_v01.h"

class UnityTests{

public:
    static void run();

private:

    static void test_FlowIdCalc();
    static void test_NaiveDatabase_Sniffer_Integration();

    // helpers
    static ISniffer* makeNewSniffer(const char* snifferImplementation);


};

#endif // _UNITY_TESTS__H_

