project(LoCM)

add_executable(LoCM sources/main.cpp)

# like
add_executable(AI sources/AI.cpp)
add_executable(AI_enemy sources/AI_enemy.cpp)

#and then  LoCM will launch both binaries and then provide them with inputs
#have any examples i can look at?

find_package(SFML 2 REQUIRED network audio graphics window system)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(LoCM sfml-graphics sfml-window sfml-system ${SFML_DEPENDENCIES})

  