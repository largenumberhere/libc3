add_plugindirs("xmake_plugins")


function setupTest() 
    add_deps("libc3")
    set_kind("binary")
    set_default(false)
end

target("libc3")    
    if is_arch("x86_64") and is_plat("linux") then
        add_files("./libc3/src_platform/x86_64-gnu-linux/*.cpp")
    end

    add_cxxflags("gcc::-ffreestanding -nostdlib -nostartfiles")
    set_kind("static")
    add_files("libc3/src/*/*.cpp")
    set_languages("cxx23", "c11")
    add_headerfiles("./libc3/include/mangled.hpp")
    add_headerfiles("./libc3/include/unmangled.hpp") 


target("strlen1a")
    setupTest()
    add_files("./unit_tests/strlen1a.c")
    add_tests("strlen1a", {pass_outputs="ok"})
    add_headerfiles("./libc3/include/unmangled.hpp") 

target("strlen1b")
    setupTest()
    add_cxxflags("gcc::-ffreestanding -nostdlib -nostartfiles")
    add_files("./unit_tests/strlen1b.c")
    before_build(function(target) 
        target:add("cxxflags","gcc::-ffreestanding -nostdlib -nostartfiles")
    end)
    
    on_test(function(target)
        
        
        -- os.run("echo")
        print(os.run(target:targetfile()))
        -- print("ok")
        -- os.run("")
        return true 
    end)
    add_tests("strlen1b")

    -- add_tests("strlen1b", {pass_outputs="ok"})
    

