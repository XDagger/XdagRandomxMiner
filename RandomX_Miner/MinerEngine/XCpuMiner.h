// Implementation of CPU-mining
// Author: Evgeniy Sukhomlinov
// 2018

// Licensed under GNU General Public License, Version 3. See the LICENSE file.

#pragma once

#include "Core/Miner.h"
#include "RandomX/randomx.h"

using namespace XDag;

//Mainly for test purposes
class XCpuMiner : public Miner
{
private:
    static unsigned _numInstances;

    void WorkLoop() override;
public:
    XCpuMiner(unsigned index, XTaskProcessor* taskProcessor);
    virtual ~XCpuMiner();

    bool Initialize() override { return true; } // nothing to initialize for CPU

    static unsigned Instances() { return _numInstances > 0 ? _numInstances : 1; }
    static void SetNumInstances(unsigned instances) { _numInstances = instances; }
    static void ListDevices();

    HwMonitor Hwmon() override;
};
