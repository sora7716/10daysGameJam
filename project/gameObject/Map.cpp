#include "Map.h"
#include <Novice.h>

//初期化
void Map::Initialize()
{
	//マップの行の要素数を指定
	map_.resize(kMaxMapSize.y);

	//マップの列の要素数を指定
	for (int y = 0; y < map_.size(); y++)
	{
		map_[y].resize(kMaxMapSize.x);
	}
}

//描画
void Map::Draw()
{
	for (int y = 0; y < map_.size(); y++)
	{
		for (int x = 0; x < map_[y].size(); x++)
		{
			if (map_[y][x] == static_cast<int>(BlockType::kBlock))
			{
				/*Novice::DrawBox(
					x * kBlockSize,
					y * kBlockSize, kBlockSize, kBlockSize, 0.0f, WHITE, kFillModeWireFrame
				);*/
				/*static int i = 0;
				if (y > mapDrawData_[i].begin.y + Chunk::kMaxHeight)
				{
					i++;
				}*/

				int useTex = -1;
				for (MapDrawData& mData : mapDrawData_)
				{
					if (y >= mData.begin.y && y < mData.begin.y + Chunk::kMaxHeight)
					{
						if (x >= mData.begin.x && x < mData.begin.x + Chunk::kMaxWidth)
						{
							useTex = mData.textureHandle;
						}
					}
				}

				Novice::DrawSprite
				(
					x * kBlockSize,
					y * kBlockSize,
					useTex,
					1.0f, 1.0f, 0.0f, WHITE
				);
			}

#ifdef _DEBUG
			if (map_[y][x] == static_cast<int>(BlockType::kBlank))
			{
				Novice::DrawBox
				(
					x * kBlockSize,
					y * kBlockSize, kBlockSize, kBlockSize, 0.0f, 0x00000055, kFillModeWireFrame
				);
			}
#endif // _DEBUG
		}
	}
}

//mapのセッター
void Map::SetMap(const Chunk* chunk, const Vector2Int& begin)
{
	for (int y = 0; y < Chunk::kMaxHeight; y++)
	{
		for (int x = 0; x < Chunk::kMaxWidth; x++)
		{
			map_[y + begin.y][x + begin.x] = chunk->GetChunk()[y][x];
		}
	}
	mapDrawData_.push_back({ begin,chunk->GetTextureHandle() });
}

//逆転
void Map::FlipChunk(const Vector2Int& pos)
{
	int tmp = {};
	for (int y = 0; y < Chunk::kMaxHeight; y++)
	{
		for (int x = 0; x < Chunk::kMaxWidth; x++)
		{
			Vector2Int inverse = { (Chunk::kMaxWidth - 1) - x,(Chunk::kMaxHeight - 1) - y };

			if (y < inverse.y || (y == inverse.y && x < inverse.x))
			{
				tmp = map_[pos.y + y][pos.x + x];
				map_[pos.y + y][pos.x + x] = map_[pos.y + inverse.y][pos.x + inverse.x];
				map_[pos.y + inverse.y][pos.x + inverse.x] = tmp;
			}
		}
	}
}

//切り替え
void Map::SwapChunk(Chunk* under, Chunk* top, const Vector2Int& underChunkPos)
{
	//下のチャンクを上のチャンクに変更
	SetMap(top, underChunkPos);
	//上のチャンクを下のチャンクに変更
	SetMap(under, { underChunkPos.x,underChunkPos.y - Chunk::kMaxHeight });
}


