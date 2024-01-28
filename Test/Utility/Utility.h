#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include "../Const/Const.h"

static std::vector<float> InvMatrix2x2(std::vector<float> mat)
{
	const float det = (1 / (mat[0] * mat[3] - mat[1] * mat[2]));

	return std::vector<float>
	{
		det * mat[3],
		det * -mat[1],
		det * -mat[2],
		det * mat[0]
	};
}

static sf::Vector2f CartesianToIsometric(sf::Vector2f vec, float size) 
{
	return sf::Vector2f 
	{
		(vec.x * 0.5f * size) + (vec.y * (-0.5f) * size),
		(vec.x * 0.25f * size) + (vec.y * 0.25f * size)
	};
}

static sf::Vector2f IsometricToCartesian(sf::Vector2f vec, float size) 
{
	std::vector<float> mat
	{
		0.5f * size,
		-0.5f * size,
		0.25f * size,
		0.25f * size
	};

	mat = InvMatrix2x2(mat);

	return sf::Vector2f
	{
		vec.x * mat[0] + vec.y * mat[1],
		vec.x * mat[2] + vec.y * mat[3]
	};
}

struct WrapVector2i
{
	sf::Vector2i v;
	bool operator==(const WrapVector2i& pt2) const
	{
		return this->v.x == pt2.v.x && this->v.y == pt2.v.y;
	}
};

struct WrapVector2iHasher
{
	bool operator()(const WrapVector2i& vec) const
	{
		return std::hash<int>()(vec.v.x) ^ std::hash<int>()(vec.v.y);
	}
};