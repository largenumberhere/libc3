includes("../libc3")

target("strlen1")
    set_kind("binary")
    add_files("strlen1.cpp")
    add_deps("libc3")
    -- add_headerfiles("../libc3/include/mangled.hpp")
    