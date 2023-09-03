add_library(layer2 arp.c net.c dataFrame.c)

target_include_directories(layer2 PUBLIC .. ../utils ../layer3)