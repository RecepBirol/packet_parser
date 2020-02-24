/**
 * ____________________________________________________________________________
 * Start packet capture and packet parser
 * 
 * @file        main.cpp
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
#include <pcap_util/pcap_offline.hpp>
#include <pcap_util/pcap_online.hpp>

#include <packet_parser/parser.hpp>

#include <pcap.h>
#include <stdlib.h>
#include <unistd.h>

#include <iostream>
#include <iomanip>
#include <csignal>
#include <memory>


/**
 * @brief Delegete incoming packet to packet parser.
 * 
 * @param args   extra arguments
 * @param header pcap packet header of captured packet
 * @param packet packet payload
 */
static void packet_handler(u_char* args,
    const struct pcap_pkthdr* header,
    const u_char* packet)
{
    
    std::int32_t data_link = pcap_datalink(reinterpret_cast<pcap_t*>(args));
    static packet_parser::parser packet_parser {};

    // TODO(rgul): packet fregmentation should be handled, if needed

    packet_parser.process_packet(const_cast<std::uint8_t*>(packet),
        static_cast<std::uint32_t>(header->caplen), data_link);
}

/**
 * @brief Handles the signals raised to the application
 * 
 * @param sn signal number 
 */
void signal_handler(int sn) {
    std::cout << "\n\nTotal Number of Packet: " << std::dec
        << packet_parser::parser::total_pkt_count << std::endl;
    std::cout << "Bye..." << std::endl;

    exit(sn);
}

/**
 * @brief Main entry point of the application
 */
int main(int argc, char* argv[]) {
    std::signal(SIGINT, signal_handler);
    
    std::string interface_name {};
    std::string pcap_file_path {};
    
    std::unique_ptr<pcap_util::pcap_interface> pcap;


    std::int32_t opt = getopt(argc, argv, "i:f:o:");

    if (opt == 'i') {
        interface_name = std::string(optarg);
        std::cout << "Interface name: " << interface_name << std::endl;
        pcap = std::make_unique<pcap_util::pcap_online>(interface_name);
    } else if (opt == 'f') {
        pcap_file_path = std::string(optarg);
        pcap = std::make_unique<pcap_util::pcap_offline>(pcap_file_path);
    } else {
        std::cout << "app start default settings" << std::endl;
        pcap_if_t * all_devs;
        char err_buff[PCAP_ERRBUF_SIZE];
        pcap_findalldevs(&all_devs, err_buff);
        pcap = std::make_unique<pcap_util::pcap_online>(all_devs->name);
    }

    if (pcap != nullptr) {
        pcap->list_all_devs();
        pcap->start(packet_handler);
    }
    

    return 0;
}