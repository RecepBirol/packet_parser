# ____________________________________________________________________________
# pcap_utility project CMake file
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

project(packet_parser.pcap_utility)

aux_source_directory(${PROJECT_SOURCE_DIR}/src PCAP_UTILITY_SRCS)
add_library(${PROJECT_NAME} ${PCAP_UTILITY_SRCS})
target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_SOURCE_DIR}/include)
target_link_libraries(${PROJECT_NAME} pcap)