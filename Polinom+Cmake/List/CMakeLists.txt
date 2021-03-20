file(GLOB hdrs "*.h*") 
file(GLOB srcs "*.cpp")

add_library(${List} STATIC ${srcs} ${hdrs})