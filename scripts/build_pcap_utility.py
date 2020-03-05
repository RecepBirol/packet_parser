from cffi import FFI
import path

prj_root_path = path.Path("../").abspath()
prj_build_path = prj_root_path.joinpath("build")
lib_path = prj_build_path.joinpath("pcap_utility/libpacket_parser.pcap_utility.a")
include_path = prj_root_path.joinpath("pcap_utility/include/pcap_util/capi")


ffi_builder = FFI()


# cdef() expects a single string declaring the C types, functions and
# globals needed to use the shared object. It must be in valid C syntax.
# TODO header dosyasi okunarak buraya verilebilir.
ffi_builder.cdef("""
    
    
    struct pcap_pkthdr {
        int caplen;
        ...;};
        
    typedef unsigned char u_char;
    typedef struct pcap_interface pcap_interface;


    extern "Python" void pcap_handler_callback(u_char*, const struct pcap_pkthdr *, const u_char *);

    pcap_interface* pcap_util_new_online_capture(char* interface_name);
    pcap_interface* pcap_util_new_offline_capture(char* file_path);
    void pcap_util_delete_capture(pcap_interface* pc);
    void pcap_util_list_all_devs(pcap_interface* pc);
    void pcap_util_start_capture(pcap_interface* pc,
        void(*)(u_char*, const struct pcap_pkthdr *, const u_char *));
    void pcap_util_start_capture_with_default_handler(pcap_interface* pc);
    int pcap_util_get_datalink(pcap_interface* pc);
""")

# set_source() gives the name of the python extension module to
# produce, and some C source code as a string.  This C code needs
# to make the declarated functions, types and globals available,
# so it is often just the "#include".

ffi_builder.set_source("_pcap_utility",
"""
    #include <pcap_utility.h>     // header of the library
    #include <pcap.h>
""",
    extra_objects=[lib_path],
    include_dirs=[include_path],
    libraries=['stdc++','pcap']
)

if __name__ == "__main__":
    ffi_builder.compile(verbose=True)
