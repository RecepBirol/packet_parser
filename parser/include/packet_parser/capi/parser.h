/**
 * ____________________________________________________________________________
 * 
 * C API for parser library. parse raw network data from layer2
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

#pragma once 

#ifdef __cplusplus
    extern "C" {
#endif // __cplusplus

#include <stdint.h>

typedef struct parser parser;

/**
 * @brief Construct a new parser object
 * @return parser* pointer to the newly constructed parser object
*/
parser* packet_parser_new_parser(void);

/**
 * @brief Delete a parser object
 * @param p pointer to the parser object
*/
void packet_parser_delete_parser(parser* p);

/**
 * @brief parse given packet
 * @param p pointer to the parser object
 * @param packet pointer to the captured packet to be parsed
 * @param pkt_len lenght of the packet
 * @param data_link data link of the packet to determine l2 header type
*/
void packet_parser_process_packet(
    parser* p, 
    uint8_t* packet,
    uint32_t pkt_len,
    int32_t data_link);


#ifdef __cplusplus
    }
#endif //__cplusplus 