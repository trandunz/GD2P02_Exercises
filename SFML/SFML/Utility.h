#pragma once
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <vector>
#include <iostream>

template<typename T>
inline void CleanupVector(std::vector<T*> _vector)
{
    for (auto& item : _vector)
    {
        if (item)
            delete item;
        item = nullptr;
    }
    _vector.clear();
    _vector.resize(0);
}

template<typename T>
inline void CleanupVector(std::vector<T> _vector)
{
    _vector.clear();
    _vector.resize(0);
}



