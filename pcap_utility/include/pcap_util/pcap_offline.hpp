/**
 * ____________________________________________________________________________
 * pcap offline class decleration. open pcap file offline
 * 
 * @file        pcap_offline.hpp
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

namespace pcap_util {

    /**
     * @brief Pcap file reader packet capture interface implementation
     */
    class pcap_offline : public pcap_interface {
    public:
        /**
         * @brief Construct a new pcap offline object
         * 
         * @param file_name Pcap file name
         */
        pcap_offline(std::string file_name);

        /**
         * @brief Destroy the pcap offline object
         */
        ~pcap_offline();

        /**
         * @brief Open a pcap file
         * 
         * @param file Pcap file name
         * @return pcap_t* Pointer to the opened pcap file
         */
        pcap_t* open(std::string file) override;
    private:
        std::string file_name;
    };
};