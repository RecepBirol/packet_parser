/**
 * ____________________________________________________________________________
 * 
 * C API implementation of parser library. parse raw network data from layer2
 * to layer4
 * 
 * @file        parser.h
 * @author      Recep Birol Gül <rgul@nettsi.com>
 * @date        24.01.2020
 * 
 * @copyright   2020 NETTSI Informatics Technology Inc.
 * 
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 * ____________________________________________________________________________
 */

#include <packet_parser/capi/parser.h>
#include <packet_parser/parser.hpp>


extern "C" {
    parser* packet_parser_new_parser(void) {
        packet_parser::parser* new_parser = new packet_parser::parser();
        return reinterpret_cast<parser*>(new_parser);
    }


    void packet_parser_delete_parser(parser* p) {
        delete reinterpret_cast<packet_parser::parser*>(p);
    }

    void packet_parser_process_packet(
        parser* p, 
        uint8_t* packet,
        uint32_t pkt_len,
        int32_t data_link)
    {
        packet_parser::parser* parser =
            reinterpret_cast<packet_parser::parser*>(p);
        
        parser->process_packet(packet, pkt_len, data_link);
    }


} // extern "C"
