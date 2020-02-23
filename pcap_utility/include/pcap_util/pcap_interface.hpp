/**
 * ____________________________________________________________________________
 * pcap interface declaration. read and capture pcap files
 * 
 * @file        pcap_interface.hpp
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

#include <pcap_util/pcap_fwd.hpp>
#include <memory>
#include <string>

namespace pcap_util {

    /**
     * @brief Abstract pcap packet capture interface
     */
    class pcap_interface {
    public:
        // pcap handler callback function
        using callback_fn = 
            void(*)(u_char*, const struct pcap_pkthdr*, const u_char*);
        
        using pcap_file_ptr = std::unique_ptr<pcap_t, void(*)(pcap_t*)>;
        using pcap_if_ptr = std::unique_ptr<pcap_if_t, void(*)(pcap_if_t*)>;
      
        /**
         * @brief Construct a new pcap interface object
         * 
         * @param pcap_handle The actual pcap capture interface provided by the implementation
         */
        pcap_interface(pcap_t* pcap_handle);

        /**
         * @brief Destroy the pcap interface object
         */
        virtual ~pcap_interface();
   
        /**
         * @brief Default packet handler callback function
         * 
         * @param args   extra arguments
         * @param header pcap packet header of the captured packet 
         * @param packet packet payload 
         */
        static void def_packet_callback(
                    u_char* args,
                    const struct pcap_pkthdr* header,
                    const u_char* packet);
        
        /**
         * @brief Start capturing packets (with default packet callback)
         */
        void start();
        
        /**
         * @brief Start capturing packets from the interface. The captured packets will be
         * passed to given callback function.
         * 
         * @param callback The callback function to invoke on packet processing
         */
        void start(callback_fn callback);

        /**
         * @brief List all available devices on the interface
         * 
         */
        void list_all_devs(void) const;
        
        /**
         * @brief Open the interface represented by the parameter.
         * 
         * @param interface_name Name of the interface to be opened
         * 
         * @return pcap_t* Pointer to the opened interface
         */
        virtual pcap_t* open(std::string interface_name) = 0;

    protected:
        pcap_if_ptr all_if_devs;
        // std::string file_name;
        pcap_file_ptr pcap_handle;
    };
};