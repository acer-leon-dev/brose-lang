project "LexerUnitTestGenerator"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"
    targetdir ( "%{wks.location}/bin/" .. outputdir .. "/Tools/%{prj.name}" )
    objdir ( "%{wks.location}/bin/obj/" .. outputdir .. "/Tools/%{prj.name}" )
    targetname "generate-unit-test-lexer"

    pchheader "pch.hpp"
    pchsource "src/pch.cpp"

    includedirs {
        brose_include_dir,
        "src"
    }

    files {
        "src/**.hpp",
        "src/**.cpp" 
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