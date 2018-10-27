cmake_minimum_required (VERSION 3.12)

project( LastFile )

set( SRC_LIST
main.cpp
)

add_executable ( LastFile ${SRC_LIST} )

set_property(TARGET LastFile PROPERTY CXX_STANDARD 17 )

target_link_libraries ( LastFile 
-lstdc++fs
)
