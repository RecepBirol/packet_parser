/**
 * ____________________________________________________________________________
 * 
 * l3_parser class implementation. parse ipv4 adn ipv6 headers.
 * 
 * @file        l3_parser.cpp
 * @author      Recep Birol Gül <rgul@nettsi.com>
 * @date        30.01.2020
 * 
 * @copyright   2020 NETTSI Informatics Technology Inc.
 * 
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * ____________________________________________________________________________
 */

#include <packet_parser/l3_parser.hpp>

#include <packet_parser/parsed_data.hpp>

#include <netinet/ip.h>
#include <linux/ipv6.h>
#include <arpa/inet.h>

#include <string>

using namespace packet_parser;

#define MIN_IPV4_HDR_LEN    20
#define MIN_IPV6_HDR_LEN    40

bool l3_parser::parse_packet(const std::uint8_t* payload, layer_3_data& l3_data,
    std::uint32_t length)
{
    const iphdr* ip_hdr = reinterpret_cast<const iphdr*>(payload);

    if (ip_hdr->version == 4) {
        if (length < MIN_IPV4_HDR_LEN) {
            std::cout << "header length too few, len: " << length << std::endl;
            return false;
        }
        
        // ignore fragmented packets
        if (ip_hdr->frag_off & htons(IP_MF | IP_OFFMASK)) {
            std::cout << "Layer 3: fragmented packet" << std::endl;
            return false;
        }

        l3_data.length = ip_hdr->ihl  * 4;
        l3_data.title = "IPv4 Header";
        l3_data.header_type = l3_header_type_t::ip_v4;
        l3_data.protocol_id = ip_hdr->protocol;
        l3_data.identification = ntohs(ip_hdr->id);
        
        char src_ip_buff[INET_ADDRSTRLEN];
        char dst_ip_buff[INET_ADDRSTRLEN];

        inet_ntop(AF_INET,&(ip_hdr->saddr), src_ip_buff, INET_ADDRSTRLEN);
        inet_ntop(AF_INET,&(ip_hdr->daddr), dst_ip_buff, INET_ADDRSTRLEN);

        l3_data.src_ip = std::string(src_ip_buff);
        l3_data.dst_ip = std::string(dst_ip_buff);


    } else if (ip_hdr->version == 6) {
        if (length < MIN_IPV6_HDR_LEN) {
            std::cout << "header length too few, len: " << length << std::endl;
            return false;
        }

        const ipv6hdr* ip_hdr_v6 = reinterpret_cast<const ipv6hdr*>(payload);

        l3_data.length = MIN_IPV6_HDR_LEN;
        l3_data.title = "IPv6 Header";
        l3_data.header_type = l3_header_type_t::ip_v6;
        l3_data.protocol_id = ip_hdr_v6->nexthdr;
        l3_data.identification = 0;

        char src_ip_buff[INET6_ADDRSTRLEN];
        char dst_ip_buff[INET6_ADDRSTRLEN];

        inet_ntop(AF_INET6, &(ip_hdr_v6->saddr), src_ip_buff, INET6_ADDRSTRLEN);
        inet_ntop(AF_INET6, &(ip_hdr_v6->daddr), dst_ip_buff, INET6_ADDRSTRLEN);

        l3_data.dst_ip = std::string(dst_ip_buff);
        l3_data.src_ip = std::string(src_ip_buff);
        
    } else {
        // unknown ip header
        l3_data.header_type = l3_header_type_t::unsupported;
        std::cout << "Layer 3: unsupported header type." <<  std::endl;
        return false;
    }
        
    if (l3_data.protocol_id == IPPROTO_TCP) {
        l3_data.protocol = "TCP";
    } else if (l3_data.protocol_id == IPPROTO_UDP) {
        l3_data.protocol = "UDP";
    } else {    
        l3_data.protocol = "Unknown";
    }

    return true;
}

