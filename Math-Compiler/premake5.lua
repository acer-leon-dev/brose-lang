project "Math-Compiler"
    kind "StaticLib"
    language "C++"
    cppdialect "C++23"
    targetdir "bin/%{cfg.buildcfg}"
    objdir "bin-int/%{cfg.buildcfg}"

    pchheader "PCH.hpp"
    pchsource "PCH.cpp"

    includedirs {
        "include"
    }

    files { 
        "include/**.hpp", 
        "src/**.cpp" 
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"