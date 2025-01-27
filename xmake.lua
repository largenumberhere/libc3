add_plugindirs("xmake_plugins")


function setupTest() 
    add_deps("libc3")
    set_kind("binary")
    set_default(false)
end

target("libc3")    
    add_headerfiles("./libc3/include/sys.hpp")    
    print(is_arch("x86_64"), is_plat("linux"))
    if is_arch("x86_64") and is_plat("linux") then
        add_files("./libc3/src_platform/x86_64-gnu-linux/*.cpp")
    end
    set_kind("static")
    add_files("libc3/src/**.cpp")

    set_languages("cxx23", "c11")
    add_headerfiles("./libc3/include/mangled.hpp")
    add_headerfiles("./libc3/include/unmangled.hpp") 
    

-- test with standard library
target("strlen1a")
    setupTest()
    add_files("./unit_tests/strlen1a.c")
    add_tests("strlen1a", {pass_outputs="ok"})
    add_headerfiles("./libc3/include/mangled.hpp")
    -- add_ldflags("-stdlib=libstdc++", {force = true})
    
-- test without standard library
target("strlen1b")
    setupTest()
    
    add_ldflags("-nostdlib")
    add_ldflags("-nostartfiles")
    add_ldflags("-ffreestanding")

    add_files("./unit_tests/strlen1b.c")

    add_tests("strlen1b")
    add_tests("strlen1b", {pass_outputs="ok"})
    

