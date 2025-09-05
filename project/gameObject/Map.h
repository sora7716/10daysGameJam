#pragma once
#include <vector>
#include "Vector2.h"
#include "Chunk.h"

enum class BlockType
{
	kBlank,
	kBlock,
};

class Map
{
public://定数

	static inline const int kBlockSize = 32;

private://メンバ変数

	Vector2 origin_ = {};
	std::vector<std::vector<int>>map_;

public://メンバ関数

	void Draw();

	void SetMap(const std::array<std::array<int, Chunk::kMaxWidth>, Chunk::kMaxHeight>&chunk);

	void SetOrigin(const Vector2& origin) { origin_ = origin; };

};

