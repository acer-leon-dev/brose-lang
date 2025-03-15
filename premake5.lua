-- premake5.lua
workspace "Mathlang"
   architecture "x64"
   configurations { "Debug", "Release" }

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

include "Math-Compiler"
include "Math-Test"