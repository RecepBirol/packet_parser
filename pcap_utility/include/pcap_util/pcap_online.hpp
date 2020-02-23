/**
 * ____________________________________________________________________________
 * pcap online class decleration. capture packet from interfase as online
 * 
 * @file        pcap_online.hpp
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

#include <pcap_util/pcap_interface.hpp>
#include <pcap_util/pcap_fwd.hpp>

#include <string>

namespace pcap_util {

    /**
     * @brief Pcap live packet capture interface
     * 
     */
    class pcap_online : public pcap_interface{

    public:
        /**
         * @brief Construct a new pcap online object
         * 
         * @param dev_name Device name to be opened
         */
        pcap_online(std::string dev_name);

        /**
         * @brief Destroy the pcap online object
         */
        ~pcap_online();

        /**
         * @brief Open a physical device
         * 
         * @param dev_name Device name to be opened
         * @return pcap_t* Pointer to the opened pcap interface
         */
        pcap_t* open(std::string dev_name) override;
    private:
        const std::string dev_name;
    };
};

