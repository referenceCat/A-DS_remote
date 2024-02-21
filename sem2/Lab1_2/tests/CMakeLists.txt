
add_executable(lab1_sem2_main main.cpp)
find_package(PkgConfig REQUIRED)

pkg_check_modules(allegro-5 REQUIRED allegro-5 allegro_image-5 allegro_font-5 allegro_primitives-5 allegro_ttf-5)

include_directories(${PROJECT_SOURCE_DIR})

set(ALLEGRO5_LIBRARIES, "allegro_image,allegro_primitives;allegro;impl")
message("PROJECT_SOURCE_DIR = ${PROJECT_SOURCE_DIR}")
message("ALLEGRO5_LIBRARIES = ${allegro-5_LIBRARIES}")
message("ALLEGRO5_INCLUDE_DIRS = ${allegro-5_INCLUDE_DIRS}")
target_link_libraries(lab1_sem2_main ${allegro-5_LIBRARIES})
target_include_directories(lab1_sem2_main PUBLIC ${allegro-5_INCLUDE_DIRS})


#target_link_libraries(lab1_sem2_main PUBLIC impl)