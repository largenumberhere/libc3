add_plugindirs("xmake_plugins")
set_policy("check.auto_ignore_flags", false)

function setupTest()
    add_deps("libc3")
    set_kind("binary")
    add_cflags("-g")
    add_ldflags("-g")
    add_cxxflags("-g")
    set_default(false)
end

target("libc3")   

    if is_arch("x86_64") and is_plat("linux") then
        add_files("./libc3/src_platform/x86_64-gnu-linux/*.cpp")
    end
    add_headerfiles("./libc3/include/sys.hpp")    
    add_headerfiles("./libc3/include/helpers.hpp")
    add_headerfiles("./libc3/include/ints.hpp")
    add_headerfiles("./libc3/include/mangled.hpp")

    set_kind("static")
    add_files("libc3/src/**.cpp")
    
    add_cxxflags("-ffreestanding", "-nostdlib", "-nostartfiles")
    add_cflags("-ffreestanding", "-nostdlib", "-nostartfiles")
    set_languages("cxx23", "c11") 
    

-- test with standard library
target("strlen1a")
    setupTest()
    add_headerfiles("./libc3/include/sys.hpp")    
    add_headerfiles("./libc3/include/helpers.hpp")
    add_headerfiles("./libc3/include/ints.hpp")

    add_files("./unit_tests/strlen1a.c")
    add_tests("strlen1a", {pass_outputs="ok"})
    add_headerfiles("./libc3/include/mangled.hpp")
    -- add_ldflags("-stdlib=libstdc++", {force = true})
    
-- -- test without standard library
-- target("strlen1b")
--     setupTest()
--     add_headerfiles("./libc3/include/unmangled.hpp") 
--     add_ldflags("-nostartfiles", "-ffreestanding", "-nostdlib")
--     add_cflags("-ffreestanding", "-nostdlib")
--     add_files("./unit_tests/strlen1b.c")

--     add_tests("strlen1b")
--     add_tests("strlen1b", {pass_outputs="ok"})
    
target("malloc1a")
    setupTest()
    add_headerfiles("./libc3/include/sys.hpp")    
    add_headerfiles("./libc3/include/helpers.hpp")
    add_headerfiles("./libc3/include/ints.hpp")

    add_files("./unit_tests/malloc1a.c")
    add_tests("malloc1a", {pass_outputs="ok"})
    add_headerfiles("./libc3/include/mangled.hpp")
