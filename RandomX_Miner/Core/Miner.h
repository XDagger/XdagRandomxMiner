/*
    This file is part of cpp-ethereum.

    cpp-ethereum is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    cpp-ethereum is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with cpp-ethereum.  If not, see <http://www.gnu.org/licenses/>.
*/
/** @file Miner.h
* @author Gav Wood <i@gavwood.com>
* @date 2015
*/

// Modified by Evgeniy Sukhomlinov 2018

#pragma once

#include "Worker.h"
#include <thread>
#include <list>
#include <vector>
#include <string>
#include <boost/timer.hpp>
#include "Common.h"
#include "Log.h"
#include "XDagCore/XTaskProcessor.h"

#define MINER_WAIT_STATE_WORK	 1

namespace XDag
{
    enum class MinerType : int
    {
        NotSet = 0,
        CL = 1,
        CPU = 2
    };

    static inline MinerType operator|(MinerType lt, MinerType rt)
    {
        return static_cast<MinerType> (
            static_cast<std::underlying_type<MinerType>::type>(lt) |
            static_cast<std::underlying_type<MinerType>::type>(rt)
            );
    }

    static inline MinerType operator&(MinerType lt, MinerType rt)
    {
        return static_cast<MinerType> (
            static_cast<std::underlying_type<MinerType>::type>(lt) &
            static_cast<std::underlying_type<MinerType>::type>(rt)
            );
    }

    static inline MinerType& operator|=(MinerType& lt, MinerType rt)
    {
        lt = static_cast<MinerType> (
            static_cast<std::underlying_type<MinerType>::type>(lt) |
            static_cast<std::underlying_type<MinerType>::type>(rt)
            );
        return lt;
    }

    struct HwMonitor
    {
        int tempC = 0;
        int fanP = 0;
    };

    inline std::ostream& operator<<(std::ostream& os, HwMonitor _hw)
    {
        return os << _hw.tempC << "C " << _hw.fanP << "%";
    }

    /// Describes the progress of a mining operation.
    struct WorkingProgress
    {
        uint64_t hashes = 0;		///< Total number of hashes computed.
        uint64_t ms = 0;			///< Total number of milliseconds of mining thus far.
        uint64_t Rate() const { return ms == 0 ? 0 : hashes * 1000 / ms; }

        std::vector<uint64_t> minersHashes;
        //std::vector<HwMonitor> minerMonitors;
        uint64_t MinerRate(const uint64_t hashCount) const { return ms == 0 ? 0 : hashCount * 1000 / ms; }
    };

    inline std::ostream& operator<<(std::ostream& _out, WorkingProgress _p)
    {
        float mh = _p.Rate() / 1000000.0f;
        _out << "Speed "
            << EthTealBold << std::fixed << std::setw(6) << std::setprecision(2) << mh << EthReset
            << " Mh/s    ";

        for(size_t i = 0; i < _p.minersHashes.size(); ++i)
        {
            mh = _p.MinerRate(_p.minersHashes[i]) / 1000000.0f;
            _out << "u/" << i << " " << EthTeal << std::fixed << std::setw(5) << std::setprecision(2) << mh << EthReset;
            //if(_p.minerMonitors.size() == _p.minersHashes.size())
            //    _out << " " << EthTeal << _p.minerMonitors[i] << EthReset;
            _out << "  ";
        }

        return _out;
    }

    /**
     * @brief A miner - a member and adoptee of the Farm.
     * @warning Not threadsafe. It is assumed Farm will synchronise calls to/from this class.
     */
    class Miner : public Worker
    {
    public:
        Miner(std::string const& name, uint32_t index, XTaskProcessor* taskProcessor);
        virtual ~Miner() = default;

        uint64_t HashCount() const { return _hashCount.load(std::memory_order_relaxed); }
        void ResetHashCount() { _hashCount.store(0, std::memory_order_relaxed); }
        virtual HwMonitor Hwmon() = 0;
        virtual bool Initialize() = 0;

    protected:
        XTaskWrapper* GetTask() const { return _taskProcessor->GetCurrentTask(); }
        void AddHashCount(uint64_t n) { _hashCount.fetch_add(n, std::memory_order_relaxed); }

        const uint32_t _index = 0;
    private:
        std::atomic<uint64_t> _hashCount = { 0 };

        XTaskProcessor* _taskProcessor;
    };
}
