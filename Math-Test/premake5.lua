project "Math-Test"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"
    targetdir "bin/%{cfg.buildcfg}"
    objdir "bin-int/%{cfg.buildcfg}"
    
    includedirs {
        "{wks.location}/Math-Compiler/include"
    }

    files {
        "**.cpp" 
    }

    links {
        "Math-Compiler"
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"