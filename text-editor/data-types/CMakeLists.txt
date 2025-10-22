target_sources(TextEditorApplication PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/DataTypes.hpp"
)

target_precompile_headers(TextEditorApplication PRIVATE
	"${CMAKE_CURRENT_SOURCE_DIR}/DataTypes.hpp"
)