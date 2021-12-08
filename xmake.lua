add_rules("mode.debug", "mode.release")
add_rules("plugin.vsxmake.autoupdate")

set_languages("c99", "cxx17")

target("cpputils")
	set_kind("static")
	add_includedirs("include", {public = true})
	add_files("src/**.cpp")