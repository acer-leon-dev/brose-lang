-- premake5.lua
workspace "Brose"
   architecture "x64"

   configurations { 
      "Debug",
      "Release"
   
   }

   flags {
      "MultiProcessorCompile"
   }
   
outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Brose"

group "Tests"
   include "Tests"
group ""