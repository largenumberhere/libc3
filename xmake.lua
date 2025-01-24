add_plugindirs("xmake_plugins")


target("libc3")    
    on_build(function(target) 
        if target:is_arch("x86_64") and target:is_plat("linux") then
            target:add("files", "./libc3/src_platform/x86_64-gnu-linux/*.cpp")
        else 
        error("unsupported platform")
        end
    end)
    add_cxxflags("gcc::-ffreestanding -nostdlib -nostartfiles")
    set_kind("static")
    add_files("libc3/src/*/*.cpp")
    set_languages("cxx23")
    add_headerfiles("./libc3/include/mangled.hpp")
    add_headerfiles("./libc3/include/unmangled.hpp")
    

target("tests")
    add_deps("libc3")
    set_kind("binary")
    set_default(false)
    add_headerfiles()
    
    add_tests("./unit_tests/*.cpp")
    
    

