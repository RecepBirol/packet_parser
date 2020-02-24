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


pcap_interface* pcap_util_new_online_capture(char* interface_name);
pcap_interface* pcap_util_new_offline_capture(char* file_path);
void pcap_util_delete_online_capture(pcap_interface* pc);
void pcap_util_list_all_devs(pcap_interface* pc);
void pcap_util_start_capture(pcap_interface* pc,
    void(*)(u_char*, const struct pcap_pkthdr *, const u_char *));

void pcap_util_start_capture_with_default_handler(pcap_interface* pc);


#ifdef __cplusplus
    }
#endif // __cplusplus
