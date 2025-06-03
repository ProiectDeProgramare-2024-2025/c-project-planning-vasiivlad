#include "recipe.hpp"

Recipe::Recipe(const std::string& name,
               const std::vector<std::string>& ingredients)
  : name_(name), ingredients_(ingredients)
{}

const std::string& Recipe::name() const {
    return name_;
}

int Recipe::ingredientCount() const {
    return static_cast<int>(ingredients_.size());
}

const std::vector<std::string>& Recipe::ingredients() const {
    return ingredients_;
}

void Recipe::setName(const std::string& newName) {
    name_ = newName;
}

void Recipe::setIngredients(const std::vector<std::string>& newIngredients) {
    ingredients_ = newIngredients;
}
