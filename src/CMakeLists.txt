add_executable(${PROJECT_NAME}
    main.cpp
    application.h
    application.cpp
    window/window.h
    window/window.cpp
    context/renderer.h
    context/opengl_renderer.cpp
    context/imgui_context.cpp
    context/pixel_context.cpp
    )

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(${PROJECT_NAME} imgui_glfw)
target_link_libraries(${PROJECT_NAME} stb_image)

find_package(GLEW REQUIRED)
target_link_libraries(${PROJECT_NAME} GLEW::GLEW)
