#include "Map.h"
#include <Novice.h>

void Map::Draw()
{
	for (int y = 0; y < map_.size(); y++)
	{
		for (int x = 0; x < map_[y].size(); x++)
		{

			if (map_[y][x] == static_cast<int>(BlockType::kBlock))
			{
				Novice::DrawBox(
					static_cast<int>(origin_.x) + x * kBlockSize,
					static_cast<int>(origin_.y) + y * kBlockSize, kBlockSize, kBlockSize, 0.0f, WHITE, kFillModeWireFrame);
			}
		}
	}
}

void Map::SetMap(const std::array<std::array<int, Chunk::kMaxWidth>, Chunk::kMaxHeight>& chunk)
{

	map_.resize(map_.size()+Chunk::kMaxHeight);

	for (int y = 0; y < Chunk::kMaxHeight; y++)
	{
		map_[y].resize(map_[y].size()+Chunk::kMaxWidth);

		for (int x = 0; x < Chunk::kMaxWidth * 3; x++)
		{
			if (x < 5)
			{
				map_[y][x] = chunk1->GetChunk()[y][x];
			}
			else if (x < 10)
			{
				map_[y][x] = chunk2->GetChunk()[y][x - Chunk::kMaxWidth];
			}
			else
			{
				map_[y][x] = chunk3->GetChunk()[y][x - Chunk::kMaxWidth * 2];
			}
		}
	}

}
