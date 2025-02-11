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

-- on_config(registerTests)

-- local function registerTests()
--     local endswith = function(str, suffix) 
--         return string.sub(str, -#suffix) == suffix 
--     end
    
--     local lines = function(str) 
--         return string.gmatch(str, "[^\r\n]+")
--     end
    
--     local function createMangledUnitTest(name) 
--         target(name)
--             setupTest()
--             add_files("./unit_tests/"..name..".c" )
--             add_tests(name, {pass_outputs= "ok"})
--             add_headerfiles("./libc3/include/mangled.hpp")
--     end
        

--     root_path = "./unit_tests/"
--     mangled_suffix = "a.c"
    
--     -- get source files
--     files = os.iorunv("find", {root_path})
--     print("found" .. tostring(files))
--     for file_path in lines(files) do 
--         if (endswith(file_path, mangled_suffix)) then
--             without_file_extension = string.sub(file_path, 0, -3)
--             createMangledUnitTest(without_file_extension)
--         else
--             print("warning: b tests are unimplemented")
--         end

--     end
-- end

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
    add_ldflags("-g")
    add_cflags("-g")
    add_cxxflags("-g")




-- test with standard library
target("strlen1a")
    setupTest()

    add_files("./unit_tests/strlen1a.c" )
    add_tests("strlen1a", {pass_outputs="ok"})
    add_headerfiles("./libc3/include/mangled.hpp")
    -- add_ldflags("-stdlib=libstdc++", {force = true})
    

target("fgetc1a")
    setupTest()

    add_files("./unit_tests/fgetc1a.c")
    add_tests("fgetc1a", {pass_outputs="ok"})
    add_headerfiles("./libc3/include/mangled.hpp")

    
target("malloc1a")
    setupTest()

    add_files("./unit_tests/malloc1a.c")
    add_tests("malloc1a", {pass_outputs="ok"})
    add_headerfiles("./libc3/include/mangled.hpp")


target("strcmp1a")
    setupTest()

    add_files("./unit_tests/strcmp1a.c")
    add_tests("strcmp1a", {pass_outputs="ok"})
    add_headerfiles("./libc3/include/mangled.hpp")

target("strncmp1a")
    setupTest()

    add_files("./unit_tests/strncmp1a.c")
    add_tests("strncmp1a", {pass_outputs="ok"})
    add_headerfiles("./libc3/include/mangled.hpp")


-- -- test without standard library
-- target("strlen1b")
--     setupTest()
--     add_headerfiles("./libc3/include/unmangled.hpp") 
--     add_ldflags("-nostartfiles", "-ffreestanding", "-nostdlib")
--     add_cflags("-ffreestanding", "-nostdlib")
--     add_files("./unit_tests/strlen1b.c")

--     add_tests("strlen1b")
--     add_tests("strlen1b", {pass_outputs="ok"})
