/**
 * ____________________________________________________________________________
 * 
 * l3_parser class declaration. parse ipv4 adn ipv6 headers.
 * 
 * @file        l3_parser.hpp
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

namespace packet_parser {

    struct layer_3_data;

    /**
     * @brief OSI Layer 3 protocol parser
     * 
     */
    class l3_parser {
    public:
        /**
         * @brief Parse OSI Layer 3 data of given payload
         * 
         * @param payload Payload containing OSI Layer 3 header and its' payload 
         * @param l3_data Argument to store L3 parsing result
         * @param length Length of the payload
         * 
         * @return boolean indicating parsing status
         */
        bool parse_packet(const std::uint8_t* payload, layer_3_data& l3_data, std::uint32_t length);
    }; // class l3_parser
}; // namespace parser
