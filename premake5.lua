-- premake5.lua
workspace "brose"
   architecture "x64"

   configurations { 
      "Debug",
      "Release"
   
   }

   flags {
      "MultiProcessorCompile"
   }
   
brose_include_dir = path.join("%{wks.location}", "brose", "include")

outputdir = string.lower("%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}")

include "brose"

group "Tests"
   include "Tests/Unit/Lexer"
   -- include "Tests/Unit/Parser"
group ""