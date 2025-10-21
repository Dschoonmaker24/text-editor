add_executable(TextEditorApplication)

target_sources(TextEditorApplication PRIVATE
	"EntryPoint.cpp"
	"Application.hpp"
	"Application.cpp"
)

target_link_libraries(TextEditorApplication SDL3::SDL3)
target_link_libraries(TextEditorApplication freetype)