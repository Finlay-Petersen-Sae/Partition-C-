solution "AITestbed"
   configurations { "Debug", "Release" }
   platforms {"native", "x64", "x32"}

project "AITestbed"
   kind "ConsoleApp"
   language "C++"
   includedirs { "./imgui/" }
   files { "main.cpp", "TiledWorldGenerator.cpp",  "TiledWorldGenerator.h", "Tile.cpp", "TiledWorldGenerator.cpp", "imgui_impl_glfw.cpp", "./imgui/imgui.cpp", "./imgui/imgui_draw.cpp", "./imgui/imgui_demo.cpp" }

   configuration { "linux" }
      links {"glfw3"}

   configuration { "windows" }
      links {"glfw3", "gdi32", "opengl32", "imm32"}

   configuration { "macosx" }
      links {"glfw"}
      linkoptions { "-framework OpenGL", "-framework Cocoa", "-framework IOKit", "-framework CoreVideo" }

   configuration "Debug"
      defines { "_DEBUG" }
      flags { "Symbols", "ExtraWarnings"}

   configuration "Release"
      flags { "Optimize" }
      defines { "NDEBUG" }
      flags { "Optimize", "ExtraWarnings"}

   configuration "gmake"
      buildoptions { "-std=c++0x" }