/**
 * ____________________________________________________________________________
 * Pcap offline implematation. read pcap packet offline
 * 
 * @file        pcap_offline.cpp
 * @author      Recep Birol Gül <rgul@nettsi.com>
 * @date        30.01.2020
 * 
 * @copyright   2020 NETTSI Informatics Technology Inc.
 * 
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * ____________________________________________________________________________
 */


#include <pcap_util/pcap_offline.hpp>

#include <pcap.h>

namespace pcap_util{

    pcap_t* pcap_offline::open(std::string file) {
        char err_buff[PCAP_ERRBUF_SIZE];
        pcap_t* handle = pcap_open_offline(file.c_str(), err_buff);

        if (handle == nullptr) {
            throw std::runtime_error(err_buff);
        }

        return handle;
    }

    pcap_offline::pcap_offline(std::string file_name)
        : pcap_interface(open(file_name)), file_name(file_name) 
    {}

    pcap_offline::~pcap_offline() = default;

}