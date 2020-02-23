/**
 * ____________________________________________________________________________
 * 
 * l4_parser class implementation. Parse TCP and UDP headers.
 * 
 * @file        l4_parser.cpp
 * @author      Recep Birol Gül <rgul@nettsi.com>
 * @date        30.01.2020
 * 
 * @copyright   2020 NETTSI Informatics Technology Inc.
 * 
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * ____________________________________________________________________________
 */

#include <packet_parser/l4_parser.hpp>

#include <packet_parser/parsed_data.hpp>

#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <netinet/in.h>

#include <string>

namespace packet_parser{

    bool l4_parser::parse_packet(const std::uint8_t* payload, layer_4_data& l4_data,
        std::uint32_t length)
    {
        if (l4_data.header_type == l4_header_type_t::unsupported) {
            std::cout << "Layer 4 unsupported header type" << std::endl;
            return false;
        }

        switch(l4_data.header_type) {
            case l4_header_type_t::tcp: {
                const tcphdr* tcp_hdr = reinterpret_cast<const tcphdr*>(payload);
                l4_data.src_port = ntohs(tcp_hdr->source);
                l4_data.dst_port = ntohs(tcp_hdr->dest);
                l4_data.length = tcp_hdr->th_off * 4;
                l4_data.title = "TCP Header:";
                break;
            }

            case l4_header_type_t::udp: {
                const udphdr* udp_hdr = reinterpret_cast<const udphdr*>(payload);
                l4_data.src_port = ntohs(udp_hdr->source);
                l4_data.dst_port = ntohs(udp_hdr->dest);
                l4_data.length = 8;
                l4_data.title = "UDP Header:";
                break;
            }
            // never reaches here, but added for avoid compiler warnings
            default:
                break;
        } // switch-case

        return true;
    } // parse packet


}

