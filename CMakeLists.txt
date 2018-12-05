cmake_minimum_required(VERSION 3.1)
project(NunchuckAdapter)

set(CMAKE_CXX_STANDARD 14)

find_package(Threads)

include_directories(
        "${PROJECT_SOURCE_DIR}/include"
)
message(${PROJECT_SOURCE_DIR})
add_executable(NunchuckAdapter
        src/main.cpp
        include/nunchuckdata.h
        include/threeaxisaccelerometer.h
        include/joystick.h
        include/nunchuckupdater.h
        include/nunchuckreader.h)

#check if is arm architecture
EXECUTE_PROCESS( COMMAND uname -m COMMAND tr -d '\n' OUTPUT_VARIABLE ARCHITECTURE )
message( STATUS "Architecture: ${ARCHITECTURE}" )
if( ${ARCHITECTURE} STREQUAL "armv7l" )
    find_library(wiringPi_LIB wiringPi)
    target_link_libraries(NunchuckAdapter ${wiringPi_LIB})
endif()

install(
        TARGETS NunchuckAdapter
        ARCHIVE         DESTINATION         "lib/static"
        LIBRARY         DESTINATION         "lib/shared"
        RUNTIME         DESTINATION         "bin"
        PUBLIC_HEADER   DESTINATION         "include"
)

return(1)