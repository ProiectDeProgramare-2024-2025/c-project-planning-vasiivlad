#include "recipe_manager.hpp"
#include <iostream>
#include <vector>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << "Usage:\n";
        std::cerr << "  .\\recipe_manager.exe add <Name> <IngCount> <Ing1> ...\n";
        std::cerr << "  .\\recipe_manager.exe edit <Index> <NewName> <NewCount> <NewIng1> ...\n";
        std::cerr << "  .\\recipe_manager.exe delete <Index>\n";
        return 1;
    }

    RecipeManager mgr("recipes.txt");
    mgr.load();

    std::string cmd = argv[1];

    if (cmd == "add") {
        if (argc < 4) {
            std::cerr << "Usage: .\\recipe_manager.exe add <Name> <IngCount> <Ing1> ...\n";
            return 1;
        }
        std::string name = argv[2];
        int count = std::stoi(argv[3]);
        std::vector<std::string> ings;
        for (int i = 0; i < count && 4 + i < argc; ++i)
            ings.push_back(argv[4 + i]);
        mgr.add(Recipe(name, ings));
    } else if (cmd == "edit") {
        if (argc < 5) {
            std::cerr << "Usage: .\\recipe_manager.exe edit <Index> <NewName> <NewCount> <NewIng1> ...\n";
            return 1;
        }
        int idx = std::stoi(argv[2]) - 1;
        std::string name = argv[3];
        int count = std::stoi(argv[4]);
        std::vector<std::string> ings;
        for (int i = 0; i < count && 5 + i < argc; ++i)
            ings.push_back(argv[5 + i]);
        mgr.edit(idx, Recipe(name, ings));
    } else if (cmd == "delete") {
        if (argc != 3) {
            std::cerr << "Usage: .\\recipe_manager.exe delete <Index>\n";
            return 1;
        }
        int idx = std::stoi(argv[2]) - 1;
        mgr.remove(idx);
    } else {
        std::cerr << "Unknown command for recipe_manager.exe: " << cmd << "\n";
        return 1;
    }

    return 0;
}
