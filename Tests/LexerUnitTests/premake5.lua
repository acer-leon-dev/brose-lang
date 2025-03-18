project "LexerUnitTests"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"
    targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
    objdir ("%{wks.location}/bin/obj/" .. outputdir .. "/%{prj.name}")
    targetname "LexerUnitTests"

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