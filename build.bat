if exist build\ (
    cmake --build build
    build\Debug\game.exe
) else (
    cmake -S . -B build
    cmake --build build
    build\Debug\game.exe
)