# ____________________________________________________________________________
# parser application project CMake file
#
# @file        CMakeLists.txt
# @author      Recep Birol Gül <rgul@nettsi.com>
# @date        30.01.2020
# 
# @copyright   2020 NETTSI Informatics Technology Inc.
# 
# Unauthorized copying of this file, via any medium is strictly prohibited
# Proprietary and confidential
# ____________________________________________________________________________

project(packet_parser.app)

add_executable(${PROJECT_NAME} main.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} pcap packet_parser.pcap_utility packet_parser.lib)



