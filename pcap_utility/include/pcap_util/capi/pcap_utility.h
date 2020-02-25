/**
 * ____________________________________________________________________________
 * C API of pcap utility classes
 * 
 * @file        pcap_interface.h
 * @author      Recep Birol Gül <rgul@nettsi.com>
 * @date        23.02.2020
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

struct pcap_pkthdr;
typedef unsigned char u_char;
typedef struct pcap_interface pcap_interface;

/**
 * @brief pcap live packet capture interface C API wrapper,
 * construct a new pcap  online object
 * @param interface_name iterface device name to be opened
 * @return pacap_interface* pointer to the new object
 */
pcap_interface* pcap_util_new_online_capture(char* interface_name);

/**
 * @brief pcap offline packet capture interface C API wrapper,
 * construct a new pcap offline object
 * @param file_path path to the .pcap file to be opened
 * @return pcap_interface* pointer to the new object
 */
pcap_interface* pcap_util_new_offline_capture(char* file_path);

/**
 * @brief C API wrapper to delete pacap_interface objects
 * @param pc pointer to the pcap_interface object to be deleted
 * 
*/
void pcap_util_delete_online_capture(pcap_interface* pc);

/**
 * @brief list all available interface devices
 * @param pc pointer to the pcap_interface object
*/
void pcap_util_list_all_devs(pcap_interface* pc);

/**
 * @brief start capture from file or live interface device
 * @param pc pointer to the pcap_interface object
 * @param pcap_handler pointer to the callback function
*/
void pcap_util_start_capture(pcap_interface* pc,
    void(*)(u_char*, const struct pcap_pkthdr *, const u_char *));


/**
 * @brief start capture with default callback function provided by
 * pcap interface class
 * @param pc pointer to the pcap_interface object
*/
void pcap_util_start_capture_with_default_handler(pcap_interface* pc);


#ifdef __cplusplus
    }
#endif // __cplusplus
