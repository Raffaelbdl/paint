add_executable(${PROJECT_NAME}
    main.cpp
    application.h
    application.cpp
    
    window/opengl_window.h
    window/opengl_window.cpp
    window/imgui/imgui_context.h
    window/imgui/opengl3_glfw_context.h
    window/imgui/opengl3_glfw_context.cpp

    paint/imgui_paint.h
    paint/imgui_paint.cpp
    paint/brush/brush.h
    paint/brush/brush.cpp

    paint/widgets/widget.h
    paint/widgets/canvas/canvas.h
    paint/widgets/canvas/canvas.cpp
    paint/widgets/canvas/onclick_state.cpp
    paint/widgets/canvas/colorpick_state.cpp
    paint/widgets/canvas/draw_state.cpp
    paint/widgets/canvas/idle_state.cpp
    
    paint/widgets/tools.h
    paint/widgets/tools.cpp

    graphics/framebuffer.h
    graphics/framebuffer.cpp

    types.h
    )

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_LIST_DIR})

target_link_libraries(${PROJECT_NAME} imgui_glfw)
target_link_libraries(${PROJECT_NAME} stb_image)

find_package(GLEW REQUIRED)
target_link_libraries(${PROJECT_NAME} GLEW::GLEW)

target_link_libraries(${PROJECT_NAME} statemachine)