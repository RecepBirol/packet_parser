from cffi import FFI
import path

prj_root_path = path.Path("../").abspath()
prj_build_path = prj_root_path.joinpath("build")
lib_path = prj_build_path.joinpath("parser/libpacket_parser.lib.a")
include_path = prj_root_path.joinpath("parser/include/packet_parser/capi")

print(include_path)
print(lib_path)


ffi_builder = FFI()

# cdef() expects a single string declaring the C types, functions and
# globals needed to use the shared object. It must be in valid C syntax.
ffi_builder.cdef("""
    typedef struct parser parser;
    parser* packet_parser_new_parser(void);
    void packet_parser_delete_parser(parser* p);
    void packet_parser_process_packet(parser* p,
        uint8_t* packet, uint32_t pkt_len, int32_t data_link);
""")

# set_source() gives the name of the python extension module to
# produce, and some C source code as a string.  This C code needs
# to make the declarated functions, types and globals available,
# so it is often just the "#include".

ffi_builder.set_source("_parser",
"""
    #include <parser.h>     // header of the library
""",
    extra_objects=[lib_path],
    include_dirs=[include_path],
    libraries=['stdc++']
)

if __name__ == "__main__":
    ffi_builder.compile(verbose=True)
