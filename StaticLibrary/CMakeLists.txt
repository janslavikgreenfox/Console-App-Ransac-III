# library/CMakeLists.txt
set(LIBRARY_SOURCES
    src/Column.cpp
    src/CommandLineParser.cpp
    src/LeastSquaresFitStrategy.cpp
    src/LinearModel.cpp
    src/RANSACFitStrategy.cpp
    src/Table.cpp
    src/TableBuilder.cpp
    src/TableExport.cpp
)

set(LIBRARY_HEADERS
    include/Column.h
    include/CommandLineParser.h
    include/Common.h
    include/ILinearModelFitStrategy.h
    include/LeastSquaresFitStrategy.h
    include/LinearModel.h
    include/RANSACFitStrategy.h
    include/Table.h
    include/TableBuilder.h
    include/TableExport.h
    include/TableFacade.h
)

add_library(MyLibrary STATIC ${LIBRARY_SOURCES} ${LIBRARY_HEADERS})

target_include_directories(MyLibrary PUBLIC include)