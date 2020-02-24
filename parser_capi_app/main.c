/**
 * ____________________________________________________________________________
 * Start packet capture and packet parser
 * 
 * @file        capi_main.c
 * @author      Recep Birol Gül <rgul@nettsi.com>
 * @date        24.02.2020
 * 
 * @copyright   2020 NETTSI Informatics Technology Inc.
 * 
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * ____________________________________________________________________________
 */

#include <pcap_util/capi/pcap_utility.h>

#include <pcap.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief Delegete incoming packet to packet parser.
 * 
 * @param args   extra arguments
 * @param header pcap packet header of captured packet
 * @param packet packet payload
 */
/*
static void packet_handler(u_char* args,
    const struct pcap_pkthdr* header,
    const u_char* packet)
{
    
    std::int32_t data_link = pcap_datalink(reinterpret_cast<pcap_t*>(args));
    static packet_parser::parser packet_parser {};

    // TODO(rgul): packet fregmentation should be handled, if needed

    packet_parser.process_packet(const_cast<std::uint8_t*>(packet),
        static_cast<std::uint32_t>(header->caplen), data_link);
} */

/**
 * @brief Main entry point of the application
 */
int main(int argc, char* argv[]) {

    uint32_t opt = getopt(argc, argv, "i:f:o:");
    
    pcap_interface* pcap;

    if (opt == 'i') {
        printf("interface name: %s", optarg);
        pcap = pcap_util_new_online_capture(optarg);
    } else if (opt == 'f') {
        printf("file path: %s", optarg);

    } else {

        printf("application start default settings");
    }
    
    pcap_util_list_all_devs(pcap);
    pcap_util_start_capture_with_default_handler(pcap);

    
    return 0;
}