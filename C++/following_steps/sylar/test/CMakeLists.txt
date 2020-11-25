include(GoogleTest)
find_package(GTest CONFIG REQUIRED)



set(
	TESTS
	LogTest.cc
	ConfigTest.cc
)


AddTest("sylar" "sylar" "../sylar/" ${TESTS})