/**
 * ____________________________________________________________________________
 * 
 * Parsed data structures. insertion operator overloads to
 * print parsing result
 * 
 * @file        parserd_data.hpp
 * @author      Recep Birol Gül <rgul@nettsi.com>
 * @date        30.01.2020
 * 
 * @copyright   2020 NETTSI Informatics Technology Inc.
 * 
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * ____________________________________________________________________________
 */

#pragma once

#include <cstdint>
#include <string>
#include <iostream>
#include <iomanip>

namespace packet_parser {

    /**
     * @brief Supported OSI Layer 2 header types 
     * 
     */
    enum class l2_header_type_t : std::uint8_t {
        unsupported,
        ethernet,
        linux_sll
    }; // l2_header_type_t

    /**
     * @brief Supported OSI Layer3 header types 
     * 
     */
    enum class l3_header_type_t : std::uint8_t {
        unsupported,
        ip_v4,
        ip_v6
    }; // l3_header_type_t


    /**
     * @brief Supported OSI Layer 4 header types 
     * 
     */
    enum class l4_header_type_t : std::uint8_t {
        unsupported,
        tcp,
        udp
    }; // l4_header_type_t


    /**
     * @brief OSI Layer 2 protocol detail 
     * 
     */
    struct layer_2_data {
        std::string         title;
        l2_header_type_t    header_type;  
        std::string         dest_mac;
        std::string         src_mac;
        std::uint16_t       type_id;
        std::uint32_t       length;
        std::uint32_t       sll_pkttype;

    }; // layer_2_data

    /**
     * @brief OSI Layer 3 protocol detail 
     * 
     */
    struct layer_3_data {
        std::string         title;
        l3_header_type_t    header_type;
        std::string         src_ip;
        std::string         dst_ip;
        std::uint8_t        protocol_id;
        std::string         protocol;
        std::uint16_t       identification;
        std::uint32_t       length;
    }; // layer_3_data

    /**
     * @brief OSI Layer 4 protocol detail 
     * 
     */
    struct layer_4_data {
        std::string         title;
        l4_header_type_t    header_type;
        std::uint16_t       src_port;
        std::uint16_t       dst_port;
        std::uint32_t       length;
    }; // layer_4_data

    /**
     * @brief OSI L2-L4 protocol detail 
     * 
     */
    struct parsed_data {
        layer_2_data layer_2;
        layer_3_data layer_3;
        layer_4_data layer_4;

    }; // parsed_data

}; // namespace packet_parser

// Layer 2
inline std::ostream& operator <<(std::ostream& os, const packet_parser::layer_2_data& data)
{
    using namespace std;
    os << left << "\n\nLayer 2 Parser Result:\n"
        << left << setw(40) << data.title << "\n"
        << left << setw(33) << "\t->Source Address: "
        << right << setw(40) << data.src_mac << "\n";

    if (data.header_type == packet_parser::l2_header_type_t::ethernet) {
        os << left << setw(33) << "\t->Destination Address: "
            << right << setw(40) <<  data.dest_mac << "\n";
    } else {
        os << left << setw(33) << "\t->Packet Type:: " 
            << right << setw(40) << data.sll_pkttype << "\n";
    }
        
    os << left << setw(33) << "\t->Type Id: "
        << right << setw(40) << hex << showbase << data.type_id;

    return os;
}

// Layer 3
inline std::ostream& operator <<(std::ostream& os, const packet_parser::layer_3_data& data)
{
    using namespace std;

    os << left << "\n\nLayer 3 Parser Result:\n"
        << left << setw(40) << data.title << '\n'
        << left << setw(33) << "\t->Destination: "
        << right << setw(40) << data.dst_ip << '\n'
        << left << setw(33) << "\t->Source: "
        << right << setw(40) << data.src_ip << '\n'
        << left << setw(33) << "\t->L4 Protocol: "
        << right << setw(40) << data.protocol << '\n'
        << left << setw(33) << "\tIdentification: "
        << right << setw(40) << data.identification;

    return os; 
}

inline std::ostream& operator <<(std::ostream& os, const packet_parser::layer_4_data& data)
{
    using namespace std;

    os << left << "\n\nLayer 4 Parser Result:\n"
        << left << setw(40) << data.title << '\n'
        << left << setw(33) << "\t->Destination Port: "
        << std::dec << std::noshowbase 
        << right << setw(40) << data.dst_port << '\n'
        << left << setw(33) << "\t->Source Port: " 
        << right << setw(40) << data.src_port;

    return os;
}


inline std::ostream& operator <<(std::ostream& os, const packet_parser::parsed_data& data)
{
    using namespace std;
    
    cout << data.layer_2 << data.layer_3 << data.layer_4 << endl;
   
    return os;
}


