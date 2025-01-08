add_rules("mode.debug", "mode.release")
set_languages("c99")

target("c_hashmap")
    set_kind("binary")
    add_files("src/*.c")
    add_includedirs("./include")

for _, file in ipairs(os.files("tests/test_*.c")) do
     local name = path.basename(file)
     target(name)
        set_kind("binary")
        set_default(false)
        add_includedirs("./include")
        add_files("src/*.c|main.c")
        add_files("tests/" .. name .. ".c")
        add_tests("default")
end