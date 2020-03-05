/**
 * ____________________________________________________________________________
 * 
 * Declaration of parser class. parse raw network data from layer2
 * to layer4
 * 
 * @file        parser.hpp
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
#include <memory>

namespace packet_parser {

    class l2_parser;
    class l3_parser;
    class l4_parser;

    /**
     * @brief OSI Layer 2-Layer 4 parser
     */
    class parser {
    private:
        std::unique_ptr<l2_parser> layer_2;
        std::unique_ptr<l3_parser> layer_3;
        std::unique_ptr<l4_parser> layer_4;

    public:
        /**
         * @brief Construct a new parser object
         * 
         */
        parser();
        /**
         * @brief Destroy the parser object
         * 
         */
        ~parser() noexcept(true);

        /**
         * @brief Process a packet containing OSI L2-L4 data
         * 
         * @param packet Payload to be parsed
         * @param pkt_len Length of the payload
         * @param data_link Data link type
         */
        void process_packet(std::uint8_t* packet, std::uint32_t pkt_len, std::int32_t data_link);
        
        static std::uint32_t total_pkt_count;
    }; // class parser
}; // namespace parser
