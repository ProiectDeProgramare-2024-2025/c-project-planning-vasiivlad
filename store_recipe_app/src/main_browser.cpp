#include "recipe_manager.hpp"
#include <iostream>

#ifdef _WIN32
#include <windows.h>

// Enable ANSI escape codes in Windows terminal
void enableVirtualTerminal()
{
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE)
        return;

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode))
        return;

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
}
#endif

int main(int argc, char *argv[])
{
#ifdef _WIN32
    enableVirtualTerminal();
#endif

    if (argc < 2)
    {
        std::cerr << "\033[91mUsage: recipe_browser.exe view [searchTerm]\033[0m\n";
        return 1;
    }

    std::string cmd = argv[1];
    if (cmd == "view")
    {
        std::string term = (argc > 2 ? argv[2] : "");
        RecipeManager mgr("recipes.txt");
        mgr.load();
        mgr.display(term);
    }
    else
    {
        std::cerr << "\033[91mUnknown command: " << cmd << "\033[0m\n";
        return 1;
    }

    return 0;
}
