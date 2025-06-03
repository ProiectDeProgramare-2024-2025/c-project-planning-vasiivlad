
#ifndef RECIPE_MANAGER_HPP
#define RECIPE_MANAGER_HPP

#include "recipe.hpp"
#include <string>
#include <vector>

class RecipeManager {
public:
    explicit RecipeManager(const std::string& filePath);

    // load from disk
    void load();

    // save all recipes back to disk
    void save() const;

    // operations
    void display(const std::string& searchTerm = "") const;
    void add(const Recipe& recipe);
    void edit(int index, const Recipe& updated);
    void remove(int index);

    // helper to list recipe names
    std::vector<std::string> listNames() const;

private:
    std::string              filePath_;
    std::vector<Recipe>      recipes_;

    // internal parsing helpers
    Recipe    parseRecipeBlock(const std::vector<std::string>& block) const;
    std::vector<std::string> serializeRecipe(const Recipe& r) const;
};

#endif // RECIPE_MANAGER_HPP
