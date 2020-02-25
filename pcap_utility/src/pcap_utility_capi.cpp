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

#include <pcap_util/capi/pcap_utility.h>

#include <pcap_util/pcap_interface.hpp>
#include <pcap_util/pcap_offline.hpp>
#include <pcap_util/pcap_online.hpp>

#include <pcap.h>

extern "C" {
    pcap_interface* pcap_util_new_online_capture(char* interface_name) {
        pcap_util::pcap_online* new_pcap =
            new pcap_util::pcap_online(interface_name);
        
        return reinterpret_cast<pcap_interface*>(new_pcap);
    }

    pcap_interface* pcap_util_new_offline_capture(char* file_path) {
        pcap_util::pcap_offline* new_pcap = 
            new pcap_util::pcap_offline(file_path);

        return reinterpret_cast<pcap_interface*>(new_pcap);
    }


    void pcap_util_delete_online_capture(pcap_interface* pc) {
        delete reinterpret_cast<pcap_util::pcap_interface*>(pc);
    }

    void pcap_util_list_all_devs(pcap_interface* pc) {
        pcap_util::pcap_interface* pcap =   
            reinterpret_cast<pcap_util::pcap_interface*>(pc);

        return pcap->list_all_devs();
    }

    void pcap_util_start_capture(pcap_interface* pc, pcap_handler handler) {
        pcap_util::pcap_interface* pcap =   
            reinterpret_cast<pcap_util::pcap_interface*>(pc);

        return pcap->start(handler);
    }

    void pcap_util_start_capture_with_default_handler(pcap_interface* pc) {
        pcap_util::pcap_interface* pcap =   
            reinterpret_cast<pcap_util::pcap_interface*>(pc);

        return pcap->start();
    }
} // extern "C"