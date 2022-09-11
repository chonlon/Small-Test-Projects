add_requires("gtest 1.12.0", {alias = "gtest"})
add_requires("argparse")
add_requires("rapidjson")
add_requires("conan::zlib 1.2.11", {alias = "zlib"})

target("test")
    set_kind("binary")
    add_files("test.cc")
    add_packages("gtest")

target("hello")
    set_kind("binary")
    add_files("hello.cc")
    set_languages("c99", "c++20")

target("argparse")
    set_kind("binary")
    add_files("arg.cc")
    add_packages("argparse")

target("mixed")
    set_kind("binary")
    add_files("mixed.cc")
    add_packages("zlib", "rapidjson")

