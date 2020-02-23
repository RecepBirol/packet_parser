/**
 * ____________________________________________________________________________
 * 
 * l2_parser class implementation. 
 * 
 * @file        l2_parser.cpp
 * @author      Recep Birol Gül <rgul@nettsi.com>
 * @date        30.01.2020
 * 
 * @copyright   2020 NETTSI Informatics Technology Inc.
 * 
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * ____________________________________________________________________________
 */

#include <packet_parser/l2_parser.hpp>

#include <packet_parser/parsed_data.hpp>

#include <pcap/sll.h>

#include <netinet/in.h>
#include <netinet/ether.h>
#include <net/ethernet.h>

#include <string>

namespace packet_parser{

    bool l2_parser::parse_packet(const std::uint8_t* packet, layer_2_data& l2_data, std::uint32_t pkt_len)
    {
        if (l2_data.header_type == l2_header_type_t::ethernet) {
            
            if ( pkt_len < ETH_HLEN ) {
                std::cout << "Layer 2: pkt len < header len" << std::endl;
                return false;
            }

            const ether_header* eth_hdr = 
                reinterpret_cast<const ether_header*>(packet);

            l2_data.length = ETH_HLEN;
            l2_data.title = "Ethernet II Header";
            l2_data.dest_mac = std::string(
                ether_ntoa((const struct ether_addr*)eth_hdr->ether_dhost));

            l2_data.src_mac = std::string(
                ether_ntoa((const struct ether_addr*)eth_hdr->ether_shost));

            l2_data.type_id = ntohs(eth_hdr->ether_type);

            return true;
        }

        if (l2_data.header_type == l2_header_type_t::linux_sll) {
            if ( pkt_len < SLL_HDR_LEN ) {
                std::cout << "Layer 2: pkt len < min header len" << std::endl;
                return false;
            }
            const sll_header* sll_hdr = 
                reinterpret_cast<const sll_header*>(packet);
            
            l2_data.length = SLL_HDR_LEN;
            l2_data.title = "LINUX SLL Header";
            l2_data.type_id = ntohs(sll_hdr->sll_protocol);
            l2_data.src_mac = std::string(
                ether_ntoa((const ether_addr*)sll_hdr->sll_addr));
            l2_data.sll_pkttype = ntohs(sll_hdr->sll_pkttype);

            return true;
        }

        // unsupported ethernet header type
        return false;
    }
}


