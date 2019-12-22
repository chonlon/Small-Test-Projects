set(
	GUISRC
	widget.ui
	widget.h
	widget.cpp
)

add_library(LIBGUI STATIC ${GUISRC})
target_link_libraries(LIBGUI Qt5::Widgets Qt5::Gui Qt5::Core)
