project "Brose"
    kind "StaticLib"
    language "C++"
    cppdialect "C++23"
    targetdir ( "%{wks.location}/bin/" .. outputdir .. "/%{prj.name}" )
    objdir ( "%{wks.location}/bin/obj/" .. outputdir .. "/%{prj.name}" )
    pchheader "pch.hpp"
    pchsource "pch.cpp"

    includedirs {
        "include",
        "src"
    }

    files { 
        "include/**.hpp", 
        "include/**.inl", 
        "src/**.hpp",
        "src/**.cpp" 
    }

    filter "configurations:Debug"
        defines { "DEBUG" }
        symbols "On"

    filter "configurations:Release"
        defines { "NDEBUG" }
        optimize "On"