/**
 * ____________________________________________________________________________
 * pcap interface implematation. read and capture pcap files
 * 
 * @file        pcap_interface.cpp
 * @author      Recep Birol Gül <rgul@nettsi.com>
 * @date        30.01.2020
 * 
 * @copyright   2020 NETTSI Informatics Technology Inc.
 * 
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * ____________________________________________________________________________
 */

#include <pcap_util/pcap_interface.hpp>

#include <pcap.h>

#include <memory>
#include <string>
#include <iostream>

namespace pcap_util{

    void pcap_interface::def_packet_callback(
        u_char* args,
        const struct pcap_pkthdr* header,
        const u_char* packet)
    {
        static std::uint32_t packet_count {};

        
        //std::cout << "packet captured: " << packet << std::endl;
        packet_count++;
        
        std::cout << "time: " << header->ts.tv_sec 
            << "\nlength of portion present: " << header->caplen
            << "\nlength this packet (off wire): " << header->len 
            << std::endl;

        std::cout << "total count of captured packets: " << 
            packet_count << std::endl;

        std::cout << "==================================" << std::endl;   
    }

    void pcap_interface::list_all_devs(void) const {
        pcap_if_t* curr_dev = all_if_devs.get();
        while(curr_dev) {
            std::cout << "dev: " << curr_dev->name << std::endl;
            curr_dev = curr_dev->next;
        }
    }

    void pcap_interface::start() {
        start(def_packet_callback);
    }

    void pcap_interface::start(callback_fn callback) {
        if (pcap_loop(pcap_handle.get(), 0, callback, 
        reinterpret_cast<u_char*>(this)) < 0)
        {
            throw std::runtime_error(pcap_geterr(pcap_handle.get()));
        }
    }

    pcap_interface::pcap_interface(pcap_t* pcap_handle)
        : pcap_handle(pcap_file_ptr(pcap_handle, pcap_close)), 
        all_if_devs(pcap_if_ptr(nullptr, pcap_freealldevs))
    {
        char err_buff[PCAP_ERRBUF_SIZE];
        pcap_if_t* _all_devs;    
        if (0 != pcap_findalldevs(&_all_devs, err_buff)) {
            throw std::runtime_error(err_buff);
        }

        all_if_devs = pcap_if_ptr(_all_devs, pcap_freealldevs);
    }

    std::int32_t pcap_interface::get_datalink(void) {
        return pcap_datalink(pcap_handle.get());
    }

    pcap_interface::~pcap_interface() = default;

}




