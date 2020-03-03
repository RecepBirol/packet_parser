from _pcap_utility import ffi, lib

class Pcap_Interface:
    def __init__(self, interface_ptr):
        self._interface_ptr = interface_ptr
        self._data_link = lib.pcap_util_get_datalink(self._interface_ptr)
    
    def list_all_dev(self):
        lib.pcap_util_list_all_devs(self._interface_ptr)

    # overloaded start capture, start with python callback 
    def start_capture(self, callback_f=None):
        # with python callback
        if callback_f is not None:
            print("start with callback")
            lib.pcap_util_start_capture(self._interface_ptr, callback_f)
        # with default callback
        else:
            print("start with default callback")
            lib.pcap_util_start_capture_with_default_handler(self._interface_ptr)

    def get_datalink(self):
        return self._data_link

    def __del__(self):
        print("Pcap_Inteface.__del__")
        lib.pcap_util_delete_capture(self._interface_ptr)


class Pcap_Online(Pcap_Interface):
    def __init__(self, ifname):
        self._char_ptr_ifname = ffi.new("char[]", ifname.encode('UTF-8'))
        super().__init__(lib.pcap_util_new_online_capture(self._char_ptr_ifname))

    def __del__(self):
        print("Pcap_Online.__del__")
        super(Pcap_Online, self).__del__()

class Pcap_Offline(Pcap_Interface):
    def __init__(self, file_path):
        self._char_ptr_file_path = ffi.new("char[]", file_path.encode('UTF-8'))
        super().__init__(lib.pcap_util_new_offline_capture(self._char_ptr_file_path))

    def __del__(self):
        print("Pcap_Offline.__del__")
        super(Pcap_Offline, self).__del__()        


def main():
    pcap_online = Pcap_Online("wlp0s20f3")
    pcap_online.list_all_dev()
    #pcap_online.start_capture_with_default_callback()
  
    pcap_offline = Pcap_Offline("../../test_capture.pcap")
    pcap_offline.start_capture()

if __name__ == "__main__":
    main()