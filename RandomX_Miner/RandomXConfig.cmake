find_path(RandomX_ROOT_DIR
        NAMES include/randomx.h
        PATHS /usr/local  /opt/local/ /usr/
        NO_DEFAULT_PATH
        )

find_path(RandomX_DIR
        NAMES include/randomx.h
        PATHS /usr/local/  /opt/local/ /usr/
        NO_DEFAULT_PATH
        )

find_path(RandomX_INCLUDE_DIR
        NAMES randomx.h
        PATHS ${RandomX_ROOT_DIR}/include
        NO_DEFAULT_PATH
        )

find_library(RandomX_LIBRARY
        NAMES randomx
        PATHS ${RandomX_ROOT_DIR}/lib/ ${RandomX_ROOT_DIR}/lib64/ /usr/lib/x86_64-linux-gnu
        NO_DEFAULT_PATH
        )

if(RandomX_INCLUDE_DIR AND RandomX_LIBRARY)
    set(RANDOMX_FOUND TRUE)
else()
    set(RANDOMX_FOUND FALSE)
endif()

message("RandomX_INCLUDE_DIR found ${RandomX_INCLUDE_DIR}")
message("RandomX_LIBRARY found ${RandomX_LIBRARY}")


mark_as_advanced(
        RandomX_ROOT_DIR
        RandomX_INCLUDE_DIR
        RandomX_LIBRARY
)

set(CMAKE_REQUIRED_INCLUDES ${RandomX_INCLUDE_DIR})
set(CMAKE_REQUIRED_LIBRARIES ${RandomX_LIBRARY})
