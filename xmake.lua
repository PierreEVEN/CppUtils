add_rules("mode.debug", "mode.release")
add_rules("plugin.vsxmake.autoupdate")

set_languages("c99", "cxx17")

set_project("cpputils")
set_allowedmodes("debug", "release")
set_defaultmode("debug")
set_warnings("allextra")
set_optimize("aggressive")

target("cpputils")
	set_kind("static")
	add_headerfiles("include/(**.hpp)")
	add_includedirs("include", {public = true})
	add_files("src/**.cpp")
	set_runtimes(is_mode("debug") and "MTd" or "MT")
