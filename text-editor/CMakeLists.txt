add_executable(TextEditorApplication)

target_sources(TextEditorApplication PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/EntryPoint.cpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Application.hpp"
	"${CMAKE_CURRENT_SOURCE_DIR}/Application.cpp"
)

target_include_directories(TextEditorApplication PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}"
)

add_subdirectory(data-types)
add_subdirectory(renderer)

target_link_libraries(TextEditorApplication SDL3::SDL3)
target_link_libraries(TextEditorApplication freetype)