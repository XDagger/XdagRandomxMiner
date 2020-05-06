// Operates with current task data
// Author: Evgeniy Sukhomlinov
// 2018

// Licensed under GNU General Public License, Version 3. See the LICENSE file.

#include <iostream>
#include "XTaskProcessor.h"
#include "Core/Log.h"


XTaskProcessor::XTaskProcessor()
{
    _taskCount = 0;
    _taskIsActive = false;

	_dataset = nullptr;

	_flags = randomx_get_flags();
	_flags |= RANDOMX_FLAG_LARGE_PAGES;
	_flags |= RANDOMX_FLAG_FULL_MEM;
}

XTaskProcessor::~XTaskProcessor()
{
	if (_dataset != nullptr)
	{
		randomx_release_dataset(_dataset);
	}

}

XTaskWrapper* XTaskProcessor::GetNextTask()
{
    Guard l(_lock);
    return &_tasks[(_taskCount + 1) & 1];
}

XTaskWrapper* XTaskProcessor::GetCurrentTask()
{
    Guard l(_lock);
    if(!_taskIsActive)
    {
        return NULL;
    }

    return &_tasks[_taskCount & 1];
}

void XTaskProcessor::SwitchTask()
{
	Guard l(_lock);

	xdag_hash_t preKey;
	memcpy(preKey, _tasks[_taskCount & 1]._task.randomx_key.data, sizeof(xdag_hash_t));

	++_taskCount;
	_tasks[_taskCount & 1]._taskIndex = _taskCount;
	_tasks[_taskCount & 1]._isShareFound = false;
	_taskIsActive = true;

	xdag_hash_t newKey;
	memcpy(newKey, _tasks[_taskCount & 1]._task.randomx_key.data, sizeof(xdag_hash_t));

	if (_dataset == nullptr || XHash::CompareHashes(preKey, newKey) != 0)
	{
		if (_dataset != nullptr)
		{
			randomx_release_dataset(_dataset);
			_dataset = nullptr;
		}
		std::cout << "Generating Cache and Dataset" << std::endl;
		randomx_cache* cache = randomx_alloc_cache(_flags);
		if (cache == nullptr) {
			std::cerr << "Cache allocation failed" << std::endl;
			exit(-1);
		}
		randomx_init_cache(cache, newKey, sizeof(xdag_hash_t));

		_dataset = randomx_alloc_dataset(_flags);
		if (_dataset == nullptr) {
			std::cerr << "Dataset allocation failed" << std::endl;
			exit(-1);
		}		
		uint32_t datasetItemCount = randomx_dataset_item_count();
		InitDataset(_dataset, cache, 4, datasetItemCount);

		randomx_release_cache(cache);
	}
}

void XTaskProcessor::DumpTasks()
{
    Guard l(_lock);
    clog(XDag::DebugChannel) << "Count of tasks: " << _taskCount << "task index: " << (_taskCount & 1);
    clog(XDag::DebugChannel) << "Task 0";
    _tasks[0].DumpTask();
    clog(XDag::DebugChannel) << "Task 1";
    _tasks[1].DumpTask();
}

randomx_dataset* XTaskProcessor::GetDataset()
{
	if (!_taskIsActive)
	{
		return nullptr;
	}
	return _dataset;
}

void XTaskProcessor::InitDataset(randomx_dataset* dataset, randomx_cache* cache, int initThreadCount, unsigned long datasetItemCount)
{
	std::vector<std::thread> threads;
	if (initThreadCount > 1) {
		auto perThread = datasetItemCount / initThreadCount;
		auto remainder = datasetItemCount % initThreadCount;
		uint32_t startItem = 0;
		for (int i = 0; i < initThreadCount; ++i) {
			auto count = perThread + (i == initThreadCount - 1 ? remainder : 0);
			threads.push_back(std::thread(&randomx_init_dataset, dataset, cache, startItem, count));
			startItem += count;
		}
		for (unsigned i = 0; i < threads.size(); ++i) {
			threads[i].join();
		}
	}
	else {
		randomx_init_dataset(dataset, cache, 0ul, datasetItemCount);
	}
}
