/**
 * ____________________________________________________________________________
 * pcap header forward decleration
 * 
 * @file        pcap_fwd.hpp
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

struct pcap_pkthdr;
struct pcap;
struct pcap_if;

using pcap_if_t = pcap_if;
using pcap_t = pcap;