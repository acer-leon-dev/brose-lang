project "UnitTest-Parser"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"
    targetdir ( "%{wks.location}/bin/" .. outputdir .. "/UnitTests" )
    objdir ( "%{wks.location}/bin/obj/" .. outputdir .. "/UnitTests/Lexer" )
    targetname "unit-test-parser"

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