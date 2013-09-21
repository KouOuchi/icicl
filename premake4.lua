local action = premake.action.current()

if string.startswith(_ACTION, "vs") then
  function premake.vs200x_vcproj_symbols(cfg)
    return 3
  end
end

solution "icicl"
  objdir(_ACTION)
  targetdir(_ACTION)

if string.startswith(_ACTION, "vs") then
  platforms { "x32", "x64" }

  configuration "x32"
    targetdir(_ACTION .. "/x32")
    libdirs("$(ProjectDir)" .. _ACTION .. "/x32")

  configuration "x64"
    targetdir(_ACTION .. "/x64")
    libdirs("$(ProjectDir)" .. _ACTION .. "/x64")

  configurations { "Debug", "Release", "DebugStatic", "ReleaseStatic" }

  configuration "DebugStatic" targetsuffix "_sd"
  configuration "ReleaseStatic" targetsuffix "_s"
  configuration "Debug" targetsuffix "_d"
else
  configurations { "Debug", "Release" }
    defines { "BOOST_ALL_DYN_LINK=1" }

  configuration "Debug" targetsuffix "_d"
end

project "icicl_lib"
  kind "StaticLib"
  language "C++"
  files { "src/**.*" }
  includedirs { "include", os.getenv("BOOST") }
  libdirs { os.getenv("BOOST") .. "/stage/x64/lib" }
  --buildoptions { "" }
  targetname "icicl"
  defines { "USE_ICICL" }
  flags { "NoPCH", "NoMinimalRebuild" }

  configuration "Debug*"
    defines { "_DEBUG" }
    flags { "Symbols" }

  configuration "Release*"
    defines { "NDEBUG" }
    flags { "Optimize" }

  configuration "*Static"
    flags { "StaticRuntime" }

  configuration "vs*"
    defines { "_CRT_SECURE_NO_WARNINGS", "_ITERATOR_DEBUG_LEVEL=0" }

project "icicl_test"
  kind "ConsoleApp"
  language "C++"
  files { "test/**.*" }
  includedirs { "include", os.getenv("BOOST") }
  links { "icicl_lib" }
  defines { "USE_ICICL" }
  libdirs { os.getenv("BOOST") .. "/stage/x64/lib" }

if not string.startswith(_ACTION, "vs") then
  links { "boost_system", "pthread", "boost_thread", "boost_regex", "boost_log", "boost_log_setup", "boost_filesystem", "boost_date_time", "boost_exception" }
end

  configuration "Debug*"
    defines { "_DEBUG" }
    flags { "Symbols" }
    links { "icicl_d" }

  configuration "Release*"
    defines { "NDEBUG" }
    flags { "Optimize" }
          links { "icicl" }

  configuration "vs*"
    defines { "_CRT_SECURE_NO_WARNINGS", "_ITERATOR_DEBUG_LEVEL=0" }

