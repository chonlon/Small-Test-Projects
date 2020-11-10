AddFilesTo(
	CONV
	conv_i2i.cpp
	conv_str.cpp
	conv_try.cpp
)

AddExeFromFiles("${LinkLibs}" ${CONV_FILES})