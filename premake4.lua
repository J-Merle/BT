solution "Blanco_Tower"
	configurations {"Debug", "Release"}

	project "Blanco_Tower"
		kind "ConsoleApp"
		language "C++"
		files { "**.h", "**.cpp" }
		includedirs { "./thirdparty/include"}

		configuration "Debug"
			defines {"DEBUG"}
			flags {"Symbols"}
			linkoptions{ "`sdl2-config --cflags --libs`"}

		configuration "Release"
			defines {"NDEBUG"}
			flags {"Optimize"}
