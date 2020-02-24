# ____________________________________________________________________________
# parser capi application project CMake file
#
# @file        CMakeLists.txt
# @author      Recep Birol Gül <rgul@nettsi.com>
# @date        24.02.2020
# 
# @copyright   2020 NETTSI Informatics Technology Inc.
# 
# Unauthorized copying of this file, via any medium is strictly prohibited
# Proprietary and confidential
# ____________________________________________________________________________

project(packet_parser.capi.app)

add_executable(${PROJECT_NAME} main.c)

target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} pcap packet_parser.pcap_utility packet_parser.lib)



