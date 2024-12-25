include_directories(${CMAKE_SOURCE_DIR}/src/draw_board
)

find_package(Qt5 COMPONENTS OpenGL REQUIRED)

set(DRAW_BOARD_SOURCES
	CDrawBoardWidget.cpp
	DrawWidget.cpp
	shape/content_edit.cpp
	shape/ellipse_shape.cpp
	shape/line_shape.cpp
	shape/rectangle_shape.cpp
	shape/base_shape.cpp
	shape/text_shape.cpp
	shape/custom_line_shape.cpp
	shape/auto_size_widget.cpp
)

add_library(draw_board STATIC ${DRAW_BOARD_SOURCES})


target_link_libraries(draw_board PRIVATE Qt5::OpenGL)