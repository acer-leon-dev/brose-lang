project "LexerUnitTestGenerator"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++23"
    targetdir( tools_bin_dir )
    objdir( tools_obj_dir )
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