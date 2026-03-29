cmake_minimum_required(VERSION 3.15)
project(pygeometry)

# Find Python automatically - scikit-build-core handles this
find_package(Python REQUIRED COMPONENTS Interpreter Development.Module)

# Find pybind11 automatically
find_package(pybind11 CONFIG REQUIRED)

# ============================================================
# FIND CGAL - Works on any OS automatically
# Searches common install locations for each platform
# ============================================================
if(WIN32)
    # Windows - installed via vcpkg in GitHub Actions
    find_package(CGAL REQUIRED HINTS
        "C:/vcpkg/installed/x64-windows/share/cgal"
        "$ENV{CGAL_DIR}"
    )
elseif(APPLE)
    # Mac - installed via homebrew
    find_package(CGAL REQUIRED HINTS
        "/opt/homebrew/lib/cmake/CGAL"
        "/usr/local/lib/cmake/CGAL"
        "$ENV{CGAL_DIR}"
    )
else()
    # Linux - installed via apt-get
    find_package(CGAL REQUIRED HINTS
        "/usr/lib/x86_64-linux-gnu/cmake/CGAL"
        "/usr/share/cgal"
        "/usr/lib/cmake/CGAL"
        "$ENV{CGAL_DIR}"
    )
endif()

# ============================================================
# BUILD THE PYTHON MODULE
# Add new .cpp files here as you add more CGAL functions
# ============================================================
pybind11_add_module(pygeometry_core
    src/pygeometry/wrapper.cpp
    cgal/distance.cpp
)

# Link CGAL
target_link_libraries(pygeometry_core PRIVATE CGAL::CGAL)

# Install
install(TARGETS pygeometry_core
    DESTINATION pygeometry
    COMPONENT python_modules
)