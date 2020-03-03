from _parser import ffi, lib

class Parser:

    def __init__(self):
        self._parser_ptr = lib.packet_parser_new_parser()

    def process_packet(self, packet, pkt_len, data_link):
        packet_uint8_t_ptr = ffi.cast("uint8_t*",packet)
        lib.packet_parser_process_packet(self._parser_ptr, packet_uint8_t_ptr, pkt_len, data_link)

    def __del__(self):
        print("Parser.__del__")
        lib.packet_parser_delete_parser(self._parser_ptr)


def main():
    parser = Parser()
    

if __name__ == "__main__":
    main()