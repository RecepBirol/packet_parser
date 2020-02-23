/**
 * ____________________________________________________________________________
 * 
 * l2_parser class declaration. parse ethernet and
 * linux_cooked_ssl header.
 * 
 * @file        l2_parser.hpp
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

namespace packet_parser {
    struct layer_2_data;

    /**
     * @brief OSI layer 2 protocol parser
     */
    class l2_parser {        
    public: 
        /**
         * @brief Parse OSI layer 2 protocol of given payload.
         * 
         * @param packet Payload to be parsed
         * @param l2_data Layer 2 parse result
         * @param pkt_len Length of the payload
         * 
         * @return boolean indicating parsing status
         */
        bool parse_packet(const std::uint8_t* packet, layer_2_data& l2_data, std::uint32_t pkt_len);
    }; // class l2_parser
}; // namespace parser
