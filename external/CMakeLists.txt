# opengl
find_package(OpenGL REQUIRED) # OpenGL::GL

# glfw
add_subdirectory(glfw-3.4) # glfw

# imgui
add_library(imgui_glfw STATIC
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_impl_glfw.cpp
    imgui/imgui_impl_opengl3.cpp
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui.cpp
    )
target_link_libraries(imgui_glfw PRIVATE glfw OpenGL::GL)
target_include_directories(imgui_glfw PUBLIC ${CMAKE_CURRENT_LIST_DIR}/imgui)

# stb_image
add_library(stb_image STATIC
    stb/stb_image.cpp
    stb/stb_image_write.cpp
    )
target_include_directories(stb_image PUBLIC ${CMAKE_CURRENT_LIST_DIR}/stb)

# statemachine
add_library(statemachine INTERFACE)
target_include_directories(statemachine INTERFACE ${CMAKE_CURRENT_LIST_DIR}/sm)