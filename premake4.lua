solution "CatAGotchiSolution"
	configurations  {"Debug64","Release64"}

project "CatAGotchi"
	kind "ConsoleApp"
	language "C++"
	location "vsfiles"
	files 
	{
		"src/**.cc",
		"src/**.h"
	}
	includedirs
	{
		"src",
		"depen/sfml/include"
	}
	libdirs
	{
		"depen/sfml/lib"
	}
	links
	{

	}
	flags 
	{

	}
	defines
	{
		"SFML_STATIC"
	}

	configuration "Debug64"
		defines
		{
			"_DEBUG"
		}
		platforms "x64"
		targetdir "build/Debug64"
		flags "Symbols"
		links
		{
			"sfml-graphics-s-d",
			"sfml-window-s-d",
			"sfml-system-s-d",
			"opengl32",
			"freetype",
			"jpeg",
			"winmm",
			"gdi32",
			"sfml-audio-s-d",
			"openal32",
			"flac",
			"vorbisenc",
			"vorbisfile",
			"vorbis",
			"ogg"
		}

	configuration "Release64"
		defines
		{
			"NDEBUG"
		}
		platforms "x64"
		targetdir "build/Release64"
		flags "Optimize"
			links
		{
			"sfml-graphics-s",
			"sfml-window-s",
			"sfml-system-s",
			"opengl32",
			"freetype",
			"jpeg",
			"sfml-system-s",
			"winmm",
			"gdi32",
			"sfml-audio-s",
			"openal32",
			"flac",
			"vorbisenc",
			"vorbisfile",
			"vorbis",
			"ogg"
		}

