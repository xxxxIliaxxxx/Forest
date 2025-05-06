add_subdirectory(SDL)
add_subdirectory(SDL_ttf)
add_subdirectory(SDL_image)
add_subdirectory(globals)
add_subdirectory(functions)
add_subdirectory(forest_classes)

add_library (MyLib STATIC forest_classes/forest_classes.cpp functions/functions.cpp)

target_include_directories(MyLib PUBLIC "SDL/include/")
target_include_directories(MyLib PUBLIC "SDL_image/include/SDL3_image/")
target_include_directories(MyLib PUBLIC "SDL_ttf/include/SDL3_ttf/")

target_include_directories(${PROJECT_NAME} PUBLIC "SDL/include/")
target_include_directories(${PROJECT_NAME} PUBLIC "SDL_image/include/SDL3_image/")
target_include_directories(${PROJECT_NAME} PUBLIC "SDL_ttf/include/SDL3_ttf/")

target_include_directories(${PROJECT_NAME} PUBLIC globals)
target_include_directories(${PROJECT_NAME} PUBLIC functions)
target_include_directories(${PROJECT_NAME} PUBLIC forest_classes)
target_include_directories(${PROJECT_NAME} PUBLIC SDL)
target_include_directories(${PROJECT_NAME} PUBLIC SDL_image)
target_include_directories(${PROJECT_NAME} PUBLIC SDL_ttf)



target_link_libraries(${PROJECT_NAME} PUBLIC SDL3::SDL3)
target_link_libraries(${PROJECT_NAME} PUBLIC SDL3_ttf::SDL3_ttf)
target_link_libraries(${PROJECT_NAME} PUBLIC SDL3_image::SDL3_image)

#target_link_libraries(${PROJECT_NAME} PUBLIC globals)
#target_link_libraries(${PROJECT_NAME} PUBLIC functions)

target_link_libraries(${PROJECT_NAME} PUBLIC MyLib)

