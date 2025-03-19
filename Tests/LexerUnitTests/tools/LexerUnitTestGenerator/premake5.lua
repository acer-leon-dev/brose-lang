project "LexerUnitTestGenerator"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"
    targetdir ("../bin/" .. outputdir .. "/%{prj.name}")
    objdir ("../bin/obj/" .. outputdir .. "/%{prj.name}")
    targetname "generateunittest"

    includedirs {
        "%{wks.location}/Brose/include"
    }

    files {
        "**.cpp" 
    }

    links {
        "Brose"
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"