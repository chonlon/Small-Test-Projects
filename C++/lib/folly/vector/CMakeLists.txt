AddFilesTo(
	FBVECTOR
	"fbvector.cpp"
    "fbvector_custom_alloctor.cpp"
    "small_vector.cpp"
)

AddExeFromFiles("${LinkLibs}" ${FBVECTOR_FILES})