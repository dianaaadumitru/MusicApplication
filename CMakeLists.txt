cmake_minimum_required(VERSION 3.17)
project(a89_913_Dumitru_Diana_1)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

set(QT_VERSION 5)
set (CMAKE_PREFIX_PATH C:\\Qt\\5.15.2\\mingw81_32\\lib\\cmake)
find_package(Qt5Widgets REQUIRED)

include_directories(domain)
include_directories(iterator)
include_directories(repo)
include_directories(service)
include_directories(tests)
include_directories(ui)
include_directories(utils)
include_directories(validator)
include_directories(undo)
include_directories(redo)

add_executable(a10_913_Dumitru_Diana_1
        domain/domain.cpp
        domain/domain.h
        dynamic_vector/array.cpp
        dynamic_vector/array.h
        iterator/iterator.cpp
        iterator/iterator.h
        repo/CSVRepo.cpp
        repo/CSVRepo.h
        repo/FileRepo.cpp
        repo/FileRepo.h
        repo/HTMLRepo.cpp
        repo/HTMLRepo.h
        repo/IFileRepo.h
        repo/repo.cpp
        repo/repo.h
        service/service.cpp
        service/service.h
        utils/utils.cpp
        utils/utils.h
        validator/validator.cpp
        validator/validator.h
        gui/tutorialModel.cpp
        gui/tutorialModel.h
        gui/NumericFilterProxyModel.h
        gui/NumericFilterProxyModel.cpp
        gui/PlayButtonDelegate.h
        gui/PlayButtonDelegate.cpp
        gui/gui2.cpp
        gui/gui2.h
        undo&redo/Action.cpp
        undo&redo/Action.h
        undo&redo/ActionAdd.cpp
        undo&redo/ActionAdd.h
        undo&redo/ActionRemove.cpp
        undo&redo/ActionRemove.h
        undo&redo/ActionUpdate.cpp
        undo&redo/ActionUpdate.h
        main.cpp)

target_link_libraries(a10_913_Dumitru_Diana_1 Qt5::Widgets)
