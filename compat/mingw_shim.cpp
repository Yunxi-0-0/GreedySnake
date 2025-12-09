// Provide fallback definitions for MinGW/LLVM-mingw linking when __argc is missing
extern "C" {
    // Define __argc and __argv so that older or mismatched runtimes resolve
    int __argc = 0;
    char **__argv = nullptr;

    // Some object files reference the import pointer __imp___argc
    // Provide it pointing to our __argc variable.
    int * __imp___argc = &__argc;
}
