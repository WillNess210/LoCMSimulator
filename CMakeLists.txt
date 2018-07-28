project(LoCM)

add_executable(LoCM main.cpp)

find_package(SFML 2 REQUIRED network audio graphics window system)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(LoCM sfml-graphics sfml-window sfml-system ${SFML_DEPENDENCIES})

  