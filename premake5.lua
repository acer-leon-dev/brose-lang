-- premake5.lua
workspace "Mathlang"
   architecture "x64"
   configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Brose"

group "Tests"
   include "Tests"
group ""