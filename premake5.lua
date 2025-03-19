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

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

bin_dir = path.join("%{wks.location}", "bin")
obj_dir = path.join("%{wks.location}", "bin", "obj")

unittest_bin_dir = path.join(bin_dir, outputdir, "UnitTests")
unittest_obj_dir = path.join(obj_dir, outputdir, "UnitTests", "%{prj.location}")

tools_bin_dir = path.join(bin_dir, outputdir, "Tools")
tools_obj_dir = path.join(obj_dir, outputdir, "Tools", "%{prj.location}")

include "brose"

group "Tests"
   include "Tests/Unit/Lexer"
   -- include "Tests/Unit/Parser"
group ""