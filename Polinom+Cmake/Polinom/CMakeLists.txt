file(GLOB hdrs "*.h*") 
file(GLOB srcs "*.cpp")

add_library(${Polinom} STATIC ${srcs} ${hdrs}) 