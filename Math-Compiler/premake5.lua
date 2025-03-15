project "Math-Compiler"
    kind "StaticLib"
    language "C++"
    cppdialect "C++23"
    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin/obj/" .. outputdir .. "/%{prj.name}")

    pchheader "PCH.hpp"
    pchsource "PCH.cpp"

    includedirs {
        "include",
        "src"
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