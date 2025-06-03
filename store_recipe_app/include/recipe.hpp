// recipe.hpp
#ifndef RECIPE_HPP
#define RECIPE_HPP

#include <string>
#include <vector>

class Recipe {
public:
    Recipe(const std::string& name = "",
           const std::vector<std::string>& ingredients = {});

    // Accessors
    const std::string&    name()        const;
    int                    ingredientCount() const;
    const std::vector<std::string>& ingredients() const;

    // Mutators
    void setName(const std::string& newName);
    void setIngredients(const std::vector<std::string>& newIngredients);

private:
    std::string              name_;
    std::vector<std::string> ingredients_;
};

#endif // RECIPE_HPP
