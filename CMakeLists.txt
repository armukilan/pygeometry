cmake_minimum_required(VERSION 3.15)
project(pycglib)
# ============================================================
# WHAT IS THIS FILE?
# Generic build file that works on any OS automatically.
# No hardcoded paths. All paths come from environment variables
# set by GitHub Actions and cibuildwheel.
# ============================================================
# Find Python automatically - scikit-build-core handles this
find_package(Python REQUIRED COMPONENTS Interpreter Development.Module)
# Find pybind11 automatically
find_package(pybind11 CONFIG REQUIRED)
# ============================================================
# FIND CGAL - Works on any OS automatically
# Each platform sets its own paths via environment variables
# in GitHub Actions before this runs.
#
# SUPPORTED PLATFORMS:
#   Windows  : CGAL installed via vcpkg
#   Linux    : CGAL installed via dnf inside manylinux_2_28
#   Mac      : CGAL installed via homebrew
#
# UNSUPPORTED PLATFORMS:
#   Windows 32-bit
#   Linux 32-bit
#   Alpine Linux (musllinux)
#   Ubuntu 18.04 and older (glibc < 2.28)
#   CentOS/RHEL 7 and older (Boost too old)
#   macOS < 11.0
# ============================================================
if(WIN32)
    find_package(CGAL REQUIRED HINTS
        "$ENV{CMAKE_PREFIX_PATH}/share/cgal"
        "C:/vcpkg/installed/x64-windows/share/cgal"
        "$ENV{CGAL_DIR}"
    )
elseif(APPLE)
    # Mac - CGAL installed via homebrew
    find_package(CGAL REQUIRED HINTS
        "/opt/homebrew/lib/cmake/CGAL"
        "/opt/homebrew/share/cgal"
        "/usr/local/lib/cmake/CGAL"
        "/usr/local/share/cgal"
        "$ENV{CGAL_DIR}"
    )
else()
    # Linux - CGAL installed via dnf inside manylinux_2_28 container
    find_package(CGAL REQUIRED HINTS
        "/usr/local/lib64/cmake/CGAL"
        "/usr/local/lib/cmake/CGAL"
        "/usr/lib/x86_64-linux-gnu/cmake/CGAL"
        "/usr/share/cgal"
        "/usr/lib64/cmake/CGAL"
        "$ENV{CGAL_DIR}"
    )
endif()
# ============================================================
# BUILD THE PYTHON MODULE
# GLOB_RECURSE automatically picks up all .cpp files under src/
# No need to manually list new files here ever again.
# Just create your .cpp file anywhere under src/ and it gets
# included automatically on next build.
#
# Structure:
#   src/
#   ├── wrapper.cpp               ← pybind11 bindings
#   ├── core/
#   │   ├── points.cpp
#   │   └── orientation.cpp
#   ├── distance/
#   │   └── distance.cpp
#   ├── triangulation/            ← future
#   ├── convex_hull/              ← future
#   └── polygon/                  ← future
# ============================================================
# file(GLOB_RECURSE ALL_SOURCES "src/*.cpp")
file(GLOB_RECURSE ALL_SOURCES "src/pycglib/*.cpp")

pybind11_add_module(pycglib_core ${ALL_SOURCES})

# src/ as include root so headers resolve as "core/points.h" etc.
# target_include_directories(pycglib_core PRIVATE src)
target_include_directories(pycglib_core PRIVATE src/pycglib)

# Link CGAL
target_link_libraries(pycglib_core PRIVATE CGAL::CGAL)
# ============================================================
# INSTALL
# Places the compiled .pyd/.so file inside the
# pycglib package folder so Python can find it
# ============================================================
install(TARGETS pycglib_core
    DESTINATION pycglib
    COMPONENT python_modules
)