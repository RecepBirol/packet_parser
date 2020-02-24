/**
 * ____________________________________________________________________________
 * 
 * definition of parser class. parse raw network data from layer2
 * to layer4
 * 
 * @file        parser.cpp
 * @author      Recep Birol Gül <rgul@nettsi.com>
 * @date        30.01.2020
 * 
 * @copyright   2020 NETTSI Informatics Technology Inc.
 * 
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * ____________________________________________________________________________
 */

#include <packet_parser/parser.hpp>

#include <packet_parser/l2_parser.hpp>
#include <packet_parser/l3_parser.hpp>
#include <packet_parser/l4_parser.hpp>
#include <packet_parser/parsed_data.hpp>

#include <pcap/dlt.h>

#include <netinet/in.h>

#include <string>
#include <iostream>
#include <iomanip>

namespace packet_parser{

    std::uint32_t parser::total_pkt_count = 0;

    parser::parser() {
        layer_2 = std::make_unique<l2_parser>();
        layer_3 = std::make_unique<l3_parser>();
        layer_4 = std::make_unique<l4_parser>();
    }

    parser::~parser() noexcept(true) = default;

    void parser::process_packet(std::uint8_t* packet,
        std::uint32_t pkt_len, std::int32_t data_link)
    {
        parser::total_pkt_count++;
        
        parsed_data parsed_data {};
        
        std::cout << "=================================" << std::dec 
            << std::noshowbase << parser::total_pkt_count
            << ". packet============================" << std::endl;
        
        if (data_link == DLT_EN10MB) {
            // l2_header_type = l2_header_type_t::ethernet;
            parsed_data.layer_2.header_type = l2_header_type_t::ethernet;
        } else if (data_link == DLT_LINUX_SLL) {
            // l2_header_type = l2_header_type_t::linux_sll;
            parsed_data.layer_2.header_type = l2_header_type_t::linux_sll;
        } else {
            // ? test
            //throw std::runtime_error("Unsupported l2 header type");
            parsed_data.layer_2.header_type = l2_header_type_t::unsupported;
        }


        if (!layer_2->parse_packet(packet, parsed_data.layer_2, pkt_len)) {
            std::cout << "Layer 2 parse failed" << std::endl;
            return;
        }

        std::cout << parsed_data.layer_2 << std::endl;

        const std::uint8_t* l2_payload = (packet + parsed_data.layer_2.length);
        const std::uint32_t l2_pl_len = pkt_len - parsed_data.layer_2.length;

        if (!layer_3->parse_packet(l2_payload, parsed_data.layer_3, l2_pl_len)) {
            std::cout << "Layer 3 parse failed" << std::endl;
            return;
        }

        std::cout << parsed_data.layer_3 << std::endl;

        const std::uint8_t* l3_payload = (l2_payload + parsed_data.layer_3.length);
        const std::uint32_t l3_pl_len = l2_pl_len - parsed_data.layer_3.length;

        if (parsed_data.layer_3.protocol_id == IPPROTO_UDP) {
            parsed_data.layer_4.header_type = l4_header_type_t::udp;
        } else if (parsed_data.layer_3.protocol_id == IPPROTO_TCP) {
            parsed_data.layer_4.header_type = l4_header_type_t::tcp;
        } else {
            parsed_data.layer_4.header_type = l4_header_type_t::unsupported;
        }

        if (!layer_4->parse_packet(l3_payload, parsed_data.layer_4, l3_pl_len)) {
            std::cout << "Layer 4 parse failed" << std::endl;
            return;
        }

        std::cout << parsed_data.layer_4 << std::endl;

        
        const std::uint8_t* l4_payload = (l3_payload + parsed_data.layer_4.length);
        const std::uint32_t l4_pl_len = l3_pl_len - parsed_data.layer_4.length;
        
        std::cout << "Layer 4 payload:" << std::endl;
        std::cout <<
            std::string(reinterpret_cast<const char*>(l4_payload), l4_pl_len) << std::endl;


        std::cout << std::string(80, '=') << std::endl;

    }

}

