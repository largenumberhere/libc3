

target("libc3")

    before_build(function(target) 
        if target:is_arch("x86_64") and target:is_plat("linux") then
            target:add("files", "./src_platform/x86_64-gnu-linux/*.cpp")
        else 
        error("unsupported platform")
        end
    end)

    set_kind("static")
    add_files("src/*/*.cpp")
    set_languages("cxx23")
    add_headerfiles("include/mangled.hpp")



    
