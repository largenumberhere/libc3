task("lint")

    set_category("plugin")
    on_run(function(args) 
        -- Import parameter option module
        import("core.base.option")

        -- string helpers
        local lines = function(str) 
            return string.gmatch(str, "[^\r\n]+")
        end

        local endswith = function(str, suffix) 
            return string.sub(str, -#suffix) == suffix 
        end

        -- go to current project directory
        build_dir = "$(buildir)"
        os.cd(build_dir)
        os.cd("..")
        
        local args = option.get("contents")
        if args == nil then 
            -- get source files
            files = os.iorunv("find", {"."})
            
            cpp_files = {}
            for v in lines(files) do
                if endswith(v, ".cpp") or endswith(v, ".hpp") or endswith(v,".c") or endswith(v, ".h") then
                    table.insert(cpp_files, v)
                end
            end

            args = cpp_files
        end


        
        os.execv("clang-tidy", args)
        table.insert(args, "-i")
        
        print("formatting source files")
        os.execv("clang-format", args)
              

    end)

    set_menu {
        -- usage
        usage = "xmake lint"

        -- description
    ,   description = "Runs clang-tidy and clang-format -i on all the files in the current project."

        -- options
    ,   options = {
            {nil, "contents", "vs", nil, "A list of source code paths or nothing"}
        }
    }