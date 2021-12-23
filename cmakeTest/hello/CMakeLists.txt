aux_source_directory(. DIR_HELLO_SRCS)
add_library(HE ${DIR_HELLO_SRCS})

set (X, "Hello")

install(TARGETS HE DESTINATION lib)
install(FILES hello.h DESTINATION include)