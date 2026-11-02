# shore-backend-mfc

The MFC peer backend for Shore. This package depends on the backend-neutral
`shore` core and requires a Visual Studio CMake generator with MFC installed.

```cmake
find_package(shore-backend-mfc CONFIG REQUIRED)
target_link_libraries(app PRIVATE shore-backend-mfc::shore-backend-mfc)
```

Construct the app with `shore::backend::mfc::CreateBackend()`. The repository
contains a standalone CMake package, a vcpkg port under `ports/shore-backend-mfc`,
and a Windows GitHub Actions build.
