cmake_minimum_required(VERSION 3.5.0)

project(netstack VERSION 1.0.0)
    

add_subdirectory(layer2)
add_subdirectory(layer3)
# add_subdirectory(layer4)
add_subdirectory(tap)
add_subdirectory(utils)

add_executable(netstack main.c)

target_include_directories(netstack PUBLIC layer2 layer3 layer4 tap utils)
target_link_libraries(netstack tap layer2 layer3 utils)