/**
 * ____________________________________________________________________________
 * 
 * l4_parser class declaration. parse TCP and UDP headers
 * 
 * @file        l4_parser.hpp
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

    struct layer_4_data;

    /**
     * @brief OSI Layer 4 protocol parser
     * 
     */
    class l4_parser {
    public:
        /**
         * @brief Parse OSI Layer 4 data of given payload
         * 
         * @param payload Payload containing OSI Layer 4 header and its' payload 
         * @param l3_data Argument to store L4 parsing result
         * @param length Length of the payload
         * 
         * @return boolean indicating parsing status
         */
        bool parse_packet(const std::uint8_t* payload, layer_4_data& l4_data,std::uint32_t length);
    }; // class l4_parser
}; // namespace parser
