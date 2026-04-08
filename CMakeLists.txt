cmake_minimum_required(VERSION 3.15)
project(pycglib)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

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
# CGAL via FetchContent — pins exact version 6.1.1 on all platforms.
# CGAL 6.0+ is fully header-only, so no system install is needed.
# This replaces the old platform-specific find_package(CGAL) block.
#
# Why 6.1.1?
#   - Multipolygon_with_holes_2 requires CGAL >= 5.6
#   - 6.1.1 is the latest stable release (Jan 2026), header-only
#   - Avoids manylinux system CGAL being too old (~5.2)
#   - Same version on Linux/Windows/macOS — no more surprises
# ============================================================
include(FetchContent)

FetchContent_Declare(
    CGAL
    URL      https://github.com/CGAL/cgal/releases/download/v6.1.1/CGAL-6.1.1-library.tar.xz
    URL_HASH SHA256=37e9fffe48a83209b070e1914c6aa0a7bae8076749712ab78b53245e176e0e0e
)

# CGAL 6 is header-only — skip building any CGAL libs
set(CGAL_DO_NOT_WARN_ABOUT_CMAKE_BUILD_TYPE TRUE)

FetchContent_MakeAvailable(CGAL)

# GMP and MPFR are still needed as system libs (arithmetic backend)
find_package(GMP  REQUIRED)
find_package(MPFR REQUIRED)

# ============================================================
# BUILD THE PYTHON MODULE
# GLOB_RECURSE automatically picks up all .cpp files under src/
# No need to manually list new files here ever again.
#
# Structure:
#   src/
#   ├── wrapper.cpp               ← pybind11 bindings
#   ├── core/
#   │   ├── points.cpp
#   │   ├── polygon2.cpp          ← new
#   │   └── ...
#   ├── distance/
#   │   └── distance.cpp
# ============================================================
file(GLOB_RECURSE ALL_SOURCES "src/pycglib/*.cpp")

pybind11_add_module(pycglib_core ${ALL_SOURCES})

# src/ as include root so headers resolve as "core/points.h" etc.
target_include_directories(pycglib_core PRIVATE src/pycglib)

# Link CGAL (header-only target) + GMP/MPFR
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