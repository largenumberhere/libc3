add_plugindirs("xmake_plugins")

includes("./unit_tests")
includes("./libc3")

target("all")
    set_kind("static")
    add_deps("unit_tests")


target("unit_tests")
    set_kind("static")
    add_headerfiles("libc3/include/mangled.hpp")
    
