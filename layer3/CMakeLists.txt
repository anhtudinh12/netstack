add_library(layer3 route.c)

target_include_directories(layer3 PUBLIC .. ../utils ../layer2)