import pcap_utility
import parser


pcap_offline = pcap_utility.Pcap_Offline("../../test_capture.pcap")
packet_parser = parser.Parser()
data_link = pcap_offline.get_datalink()


# start capture metoduna vermek icin python callback'i
# pcap_build dosyasinda cdef icinde extern "Python" ile tanimlandi
# implementasyonu bu sekilde yapiliyor
# lib.callback_name seklinede fonksiyon pointeri olarak c fonksiyonuna parametre gecilebilir.
@pcap_utility.ffi.def_extern()
def pcap_handler_callback(args, pcap_headr, packet):
    pkt_len = pcap_headr.caplen
    packet_parser.process_packet(packet, pkt_len, data_link)



def main():
    #pcap_offline = pcap_utility.Pcap_Offline("../../test_capture.pcap")
    pcap_offline.start_capture(pcap_utility.lib.pcap_handler_callback)


if __name__ == "__main__":
    main()