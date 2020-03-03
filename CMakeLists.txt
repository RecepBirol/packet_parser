# ____________________________________________________________________________
# packet parser project top level CMake file
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

cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_FLAGS "-fPIC ${CMAKE_CXX_FLAGS}")

project(packet_parser)

add_subdirectory(pcap_utility)
add_subdirectory(parser)
add_subdirectory(parser_application)
add_subdirectory(parser_capi_app)