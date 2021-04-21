# cmake_minimum_required(VERSION <specify CMake version here>)
project(DaggerMiner)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Boost COMPONENTS system filesystem thread date_time chrono regex serialization program_options locale)
if(Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    include_directories(${Boost_INCLUDE_DIR})
endif()
message("boost include dirs ${Boost_INCLUDE_DIRS}")
message("boost include dirs ${Boost_INCLUDE_DIR}")

include(./RandomX_Miner/RandomXConfig.cmake)
find_package(RandomX CONFIG)
if(RANDOMX_FOUND)
    message("-- Found RandomX: include ${RandomX_INCLUDE_DIR}  libraries ${RandomX_LIBRARY}")
    include_directories(${RandomX_INCLUDE_DIR})
else()
    message(FATAL_ERROR "Failed to find RandomX dependency!")
endif()

include_directories(RandomX_Miner)
include_directories(RandomX_Miner/Core)
include_directories(RandomX_MinerHash)
include_directories(RandomX_MinerMinerEngine)
include_directories(RandomX_MinerRandomX)
include_directories(RandomX_MinerUtils)
include_directories(RandomX_MinerXDagCore)
include_directories(RandomX_MinerXDagCore/dar)
include_directories(RandomX_MinerXDagCore/dfstools)

add_executable(DaggerRandomxMiner
        RandomX_Miner/Core/global.h
        RandomX_Miner/Core/global.cpp
        RandomX_Miner/Core/Common.h
        RandomX_Miner/Core/CommonData.cpp
        RandomX_Miner/Core/CommonData.h
        RandomX_Miner/Core/Exceptions.h
        RandomX_Miner/Core/Farm.cpp
        RandomX_Miner/Core/Farm.h
        RandomX_Miner/Core/Guards.h
        RandomX_Miner/Core/Log.cpp
        RandomX_Miner/Core/Log.h
        RandomX_Miner/Core/Miner.cpp
        RandomX_Miner/Core/Miner.h
        RandomX_Miner/Core/MinerManager.cpp
        RandomX_Miner/Core/MinerManager.h
        RandomX_Miner/Core/Terminal.h
        RandomX_Miner/Core/Worker.cpp
        RandomX_Miner/Core/Worker.h
        RandomX_Miner/Hash/sha256.cpp
        RandomX_Miner/Hash/sha256.h
        RandomX_Miner/Hash/sha256_mod.cpp
        RandomX_Miner/Hash/sha256_mod.h
        RandomX_Miner/MinerEngine/XCpuMiner.cpp
        RandomX_Miner/MinerEngine/XCpuMiner.h
        RandomX_Miner/Utils/CpuInfo.cpp
        RandomX_Miner/Utils/CpuInfo.h
        RandomX_Miner/Utils/PathUtils.cpp
        RandomX_Miner/Utils/PathUtils.h
        RandomX_Miner/Utils/Random.cpp
        RandomX_Miner/Utils/Random.h
        RandomX_Miner/Utils/StringFormat.h
        RandomX_Miner/Utils/Utils.cpp
        RandomX_Miner/Utils/Utils.h
        RandomX_Miner/XDagCore/dar/crc.h
        RandomX_Miner/XDagCore/dar/crc_c.cpp
        RandomX_Miner/XDagCore/dfstools/dfslib_crypt.cpp
        RandomX_Miner/XDagCore/dfstools/dfslib_crypt.h
        RandomX_Miner/XDagCore/dfstools/dfslib_string.cpp
        RandomX_Miner/XDagCore/dfstools/dfslib_string.h
        RandomX_Miner/XDagCore/dfstools/dfslib_types.h
        RandomX_Miner/XDagCore/XAddress.cpp
        RandomX_Miner/XDagCore/XAddress.h
        RandomX_Miner/XDagCore/XBlock.cpp
        RandomX_Miner/XDagCore/XBlock.h
        RandomX_Miner/XDagCore/XConnection.cpp
        RandomX_Miner/XDagCore/XConnection.h
        RandomX_Miner/XDagCore/XFee.cpp
        RandomX_Miner/XDagCore/XFee.h
        RandomX_Miner/XDagCore/XGlobal.cpp
        RandomX_Miner/XDagCore/XGlobal.h
        RandomX_Miner/XDagCore/XHash.cpp
        RandomX_Miner/XDagCore/XHash.h
        RandomX_Miner/XDagCore/XHash.hpp
        RandomX_Miner/XDagCore/XPool.cpp
        RandomX_Miner/XDagCore/XPool.h
        RandomX_Miner/XDagCore/XPoolConnection.cpp
        RandomX_Miner/XDagCore/XPoolConnection.h
        RandomX_Miner/XDagCore/XTaskProcessor.cpp
        RandomX_Miner/XDagCore/XTaskProcessor.h
        RandomX_Miner/XDagCore/XTaskWrapper.cpp
        RandomX_Miner/XDagCore/XTaskWrapper.h
        RandomX_Miner/XDagCore/XTime.h
        RandomX_Miner/main.cpp
        RandomX_Miner/resource.h
        RandomX_Miner/version.h)

target_link_libraries(
        DaggerRandomxMiner
        PUBLIC
        ${Boost_LIBRARIES}
        ${RandomX_LIBRARY}
)
