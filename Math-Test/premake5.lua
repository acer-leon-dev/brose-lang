project "Math-Test"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"
    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin/obj/" .. outputdir .. "/%{prj.name}")
    
    includedirs {
        "%{wks.location}/Math-Compiler/include"
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