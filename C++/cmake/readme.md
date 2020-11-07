### AddSingleExeFile.cmake

useful when you have lots of single file target like union test.

use like blow or you can see `../lib/boost` to figure how to use.

``` cmake

AddFilesTo(
  ALGORITHM
  "clamp.cpp"
  "equal.cpp"
)

foreach(FILEPATH ${ALGORITHM_FILES})
  get_filename_component(FILE_NAME ${FILEPATH} NAME_WE)
  add_executable(${FILE_NAME} ${FILEPATH})
  target_include_directories(${FILE_NAME} PRIVATE ${YOUR_LIBS})
endforeach()

#or

AddExeFromFilesWithInclude("${BOOST_INCLUDE_DIRS}" "" ${ALGORITHM_FILES})
#without include require
AddExeFromFiles("${Boost_LIBRARIES}" ${ALGORITHM_FILES})

```

**notion: include and lib should surround  with "", cause there may be more than one lib/include needed**

