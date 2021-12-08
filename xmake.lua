add_rules("mode.debug", "mode.release")
add_rules("plugin.vsxmake.autoupdate")

target(cpputils)
	set_kind("static")
	add_headerfiles("include/**.hpp")
	add_includedirs("include", {public = true})
	add_files("src/**.cpp")