cmake_minimum_required(VERSION 3.26)
project(scanner)

set(CMAKE_CXX_STANDARD 17)

add_executable(scanner
        src/main.cpp
)

target_link_libraries(scanner PRIVATE user32 gdi32)

if(MSVC)
    set_target_properties(scanner PROPERTIES
            LINK_FLAGS "/SUBSYSTEM:WINDOWS"
    )
endif()
