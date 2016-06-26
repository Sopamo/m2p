add_library(lodepng
           lodepng.cpp)

add_executable(m2p
               main.cpp)

target_link_libraries(m2p LINK_PUBLIC lodepng ${SODIUM_LIBRARIES})

install(TARGETS m2p
        DESTINATION "bin"
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE)
