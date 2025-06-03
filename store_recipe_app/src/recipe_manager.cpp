#include "recipe_manager.hpp"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cctype>
#include <sstream>

RecipeManager::RecipeManager(const std::string &filePath)
    : filePath_(filePath)
{
}

void RecipeManager::load()
{
    recipes_.clear();
    std::ifstream in(filePath_);
    if (!in)
        return;

    std::string line;
    std::vector<std::string> block;
    while (std::getline(in, line))
    {
        if (line.empty())
        {
            if (!block.empty())
            {
                recipes_.push_back(parseRecipeBlock(block));
                block.clear();
            }
        }
        else
        {
            block.push_back(line);
        }
    }
    if (!block.empty())
        recipes_.push_back(parseRecipeBlock(block));
}

void RecipeManager::save() const
{
    std::ofstream out(filePath_, std::ios::trunc);
    for (const auto &r : recipes_)
    {
        for (auto &line : serializeRecipe(r))
            out << line << "\n";
        out << "\n";
    }
}

Recipe RecipeManager::parseRecipeBlock(const std::vector<std::string> &block) const
{
    // block[0] = "Name:"     (with trailing colon)
    // block[1] = "<N> Ingredients"
    // block[2..] = "      -ingredient"
    std::string name = block[0].substr(0, block[0].size() - 1);
    int count = std::stoi(block[1]);
    std::vector<std::string> ing;
    for (int i = 2; i < 2 + count && i < (int)block.size(); ++i)
    {
        std::string line = block[i];
        auto pos = line.find('-');
        if (pos != std::string::npos)
            ing.push_back(line.substr(pos + 1));
    }
    return Recipe(name, ing);
}

std::vector<std::string> RecipeManager::serializeRecipe(const Recipe &r) const
{
    std::vector<std::string> out;
    out.push_back(r.name() + ":");
    out.push_back(std::to_string(r.ingredientCount()) + " Ingredients");
    for (auto &ing : r.ingredients())
        out.push_back("      -" + ing);
    return out;
}

void RecipeManager::display(const std::string &searchTerm) const
{
    std::string low = searchTerm;
    std::transform(low.begin(), low.end(), low.begin(), ::tolower);
    for (const auto &r : recipes_)
    {
        std::string nameLow = r.name();
        std::transform(nameLow.begin(), nameLow.end(), nameLow.begin(), ::tolower);
        if (low.empty() || nameLow.find(low) != std::string::npos)
        {
            std::cout << "\033[96m" << r.name() << ":\033[0m\n";
            for (auto &ing : r.ingredients())
                std::cout << "   - " << ing << "\n";
            std::cout << "\n";
        }
    }
}

void RecipeManager::add(const Recipe &recipe)
{
    recipes_.push_back(recipe);
    save();
}

void RecipeManager::edit(int index, const Recipe &updated)
{
    if (index >= 0 && index < (int)recipes_.size())
    {
        recipes_[index] = updated;
        save();
    }
}

void RecipeManager::remove(int index)
{
    if (index >= 0 && index < (int)recipes_.size())
    {
        recipes_.erase(recipes_.begin() + index);
        save();
    }
}

std::vector<std::string> RecipeManager::listNames() const
{
    std::vector<std::string> names;
    for (auto &r : recipes_)
        names.push_back(r.name());
    return names;
}
