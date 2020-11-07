AddFilesTo(
	FUTURE
	"future1.cpp"
	"future2.cpp"
)

AddExeFromFiles("${LinkLibs}" ${FUTURE_FILES})