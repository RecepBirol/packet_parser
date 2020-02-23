/**
 * ____________________________________________________________________________
 * Pcap online class implementation. capture packet from interfase as online
 * 
 * @file        pcap_online.cpp
 * @author      Recep Birol Gül <rgul@nettsi.com>
 * @date        30.01.2020
 * 
 * @copyright   2020 NETTSI Informatics Technology Inc.
 * 
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * ____________________________________________________________________________
 */

#include <pcap_util/pcap_online.hpp>

#include <pcap.h>

namespace pcap_util{

    pcap_t* pcap_online::open(std::string dev_name) {
        char err_buff[PCAP_ERRBUF_SIZE];
        pcap_t* handle = pcap_open_live(dev_name.c_str(), BUFSIZ, 0, -1, err_buff);
        if (handle == nullptr) {
            throw std::runtime_error(err_buff);
        }
        return handle;
    }

    pcap_online::pcap_online(std::string dev_name) 
        : pcap_interface(open(dev_name)), dev_name(std::move(dev_name))
    {}

    pcap_online::~pcap_online() = default;
}
