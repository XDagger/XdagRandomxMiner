// Operates with current task data
// Author: Evgeniy Sukhomlinov
// 2018

// Licensed under GNU General Public License, Version 3. See the LICENSE file.

#pragma once

#include "XTaskWrapper.h"
#include "Core/Guards.h"

#ifdef _WIN32
#include "RandomX/randomx.h"
#else
#include <randomx.h>
#endif

class XTaskProcessor
{
private:
    XTaskWrapper _tasks[2];
    uint64_t _taskCount;
    bool _taskIsActive;
    mutable Mutex _lock;

	randomx_flags _flags;
	randomx_dataset* _dataset;
    randomx_cache* _cache;
    
    void InitDataset(randomx_dataset* dataset, randomx_cache* cache, int initThreadCount, unsigned long datasetItemCount);
public:
    XTaskProcessor();
    ~XTaskProcessor();

    //TODO: think of better process
    XTaskWrapper* GetNextTask();
    XTaskWrapper* GetCurrentTask();
    void SwitchTask();
    uint64_t GetCount() { return _taskCount; }
    void ResetTasks() { _taskIsActive = false; }

    void DumpTasks();

	randomx_flags GetFlags() { return _flags;  }
	randomx_dataset* GetDataset();
};
