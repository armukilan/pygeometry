cmake_minimum_required(VERSION 3.15)
project(pygeometry)

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
    # Windows - CGAL installed via vcpkg
    # VCPKG_ROOT is set by cibuildwheel environment on GitHub Actions
    set(VCPKG_ROOT "C:/vcpkg")
    set(CMAKE_TOOLCHAIN_FILE "${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake"
        CACHE STRING "Vcpkg toolchain file")
    set(CGAL_DIR "${VCPKG_ROOT}/installed/x64-windows/share/cgal"
        CACHE STRING "CGAL directory")
    find_package(CGAL REQUIRED HINTS
        "${VCPKG_ROOT}/installed/x64-windows/share/cgal"
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
# Add new .cpp files here as you add more CGAL functions:
# Example:
# pybind11_add_module(pygeometry_core
#     src/pygeometry/wrapper.cpp
#     cgal/distance.cpp
#     cgal/convex_hull.cpp   ← add new files here
# )
# ============================================================
pybind11_add_module(pygeometry_core
    src/pygeometry/wrapper.cpp
    cgal/distance.cpp
)

# Link CGAL
target_link_libraries(pygeometry_core PRIVATE CGAL::CGAL)

# ============================================================
# INSTALL
# Places the compiled .pyd/.so file inside the
# pygeometry package folder so Python can find it
# ============================================================
install(TARGETS pygeometry_core
    DESTINATION pygeometry
    COMPONENT python_modules
)