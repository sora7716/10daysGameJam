#include "Map.h"
#include "calc/Collision.h"
#include "Player.h"
#include <Novice.h>

//初期化
void Map::Initialize(const Vector2Int* mousePos, Player* player)
{
	//マップの行の要素数を指定
	map_.resize(kMaxMapSize.y);

	//マップの列の要素数を指定
	for (int y = 0; y < map_.size(); y++)
	{
		map_[y].resize(kMaxMapSize.x);
	}

	//マウスの座標
	mousePos_ = mousePos;

	//プレイヤーを受け取る
	player_ = player;
}

//更新
void Map::Update()
{
	for (std::list<ChunkTransitionData>::iterator it = chunkTransitionSwitchList_.begin(); it != chunkTransitionSwitchList_.end(); it++)
	{
		//マウスを設定
		it->switchResource->SetMousePos(*mousePos_);

		//更新
		it->switchResource->Update();

		//移動しているかどうか
		if (player_->IsMove())
		{
			if (it->isTransitionChunk)
			{
				SwapChunk(it->underChunk, it->upperChunk, it->begin);
			}
		}
		else
		{
			it->isTransitionChunk = it->switchResource->IsPressSwitch();
		}
	}

	for (std::list<ChunkInvertData>::iterator it = chunkInvertSwitchList_.begin(); it != chunkInvertSwitchList_.end(); it++)
	{
		//マウスを設定
		it->switchResource->SetMousePos(*mousePos_);

		//更新
		it->switchResource->Update();

		//移動しているかどうか
		if (player_->IsMove())
		{
			if (it->isInvertChunk)
			{
				InvertChunk(it->begin);
				it->isInvertChunk = false;
			}
		}
		else
		{
			it->isInvertChunk = it->switchResource->IsPressSwitch();
		}
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
				//衝突判定
				int useTex = -1;
				for (MapDrawData& mData : mapDrawData_)
				{
					AABB aabb =
					{
						.min =
						{
							static_cast<float>(mData.begin.x),static_cast<float>(mData.begin.y)
						},
						.max =
						{
							static_cast<float>(mData.begin.x + Chunk::kMaxWidth),static_cast<float>(mData.begin.y + Chunk::kMaxHeight)
						},

					};

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

	//チャンクの切り替え用スイッチ
	for (std::list<ChunkTransitionData>::iterator it = chunkTransitionSwitchList_.begin(); it != chunkTransitionSwitchList_.end(); it++)
	{
		if (!player_->IsMove()) 
		{
			it->switchResource->Draw();
		}
	}

	//チャンクの反転用スイッチ
	for (std::list<ChunkInvertData>::iterator it = chunkInvertSwitchList_.begin(); it != chunkInvertSwitchList_.end(); it++)
	{
		if (!player_->IsMove())
		{
			it->switchResource->Draw();
		}
	}
}

//終了
void Map::Finalize()
{
	for (std::list<ChunkTransitionData>::iterator it = chunkTransitionSwitchList_.begin(); it != chunkTransitionSwitchList_.end(); it++)
	{
		delete it->switchResource;
		it->switchResource = nullptr;
	}
	chunkTransitionSwitchList_.clear();
}

//チャンク切り替えスイッチの生成
void Map::CreateChunkTransitionSwitch(Chunk* upperChunk, Chunk* underChunk, const Vector2Int& begin,int* textureHandles)
{
	//上のチャンクの読み込み
	SetMap(upperChunk, begin);

	//下のチャンクの読み込み
	SetMap(underChunk, { begin.x,begin.y + Chunk::kMaxHeight + 1 });

	//反転スイッチの生成
	InitializeInvertSwitch({ begin.x,begin.y + Chunk::kMaxHeight + 1 }, textureHandles[static_cast<int>(SwitchTex::kInvert)]);

	//スイッチの生成と初期化
	GameSwitch* chunkChangeSwitch = new GameSwitch();
	chunkChangeSwitch->Initialize
	({
		static_cast<float>((begin.x + 2) * kBlockSize),
		static_cast<float>(begin.y * kBlockSize + Chunk::kMaxHeight * kBlockSize)

	 }, textureHandles[static_cast<int>(SwitchTex::kTransition)]
	);

	//リストに追加
	chunkTransitionSwitchList_.push_back(ChunkTransitionData(chunkChangeSwitch, upperChunk, underChunk, begin, false));
}

//チャンクの反転スイッチの生成
void Map::CreateChunkInvertSwitch(Chunk* chunk, const Vector2Int& begin, int textureHandle)
{
	//チャンクの読み込み
	SetMap(chunk, begin);

	//初期化
	InitializeInvertSwitch(begin,textureHandle);
}

//チャンクの反転スイッチの生成
void Map::InitializeInvertSwitch(const Vector2Int& begin, int textureHandle)
{
	//スイッチの生成と初期化
	GameSwitch* chunkInvertSwitch = new GameSwitch();
	chunkInvertSwitch->Initialize
	({
		static_cast<float>((begin.x + Chunk::kMaxWidth - 2) * kBlockSize),
		static_cast<float>((begin.y + Chunk::kMaxHeight + 1) * kBlockSize)
	}, textureHandle);

	//リストの追加
	chunkInvertSwitchList_.push_back(ChunkInvertData(chunkInvertSwitch, begin));
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
void Map::InvertChunk(const Vector2Int& pos)
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
void Map::SwapChunk(Chunk* under, Chunk* upper, const Vector2Int& begin)
{
	//下のチャンクを上のチャンクに変更
	SetMap(under, begin);
	//上のチャンクを下のチャンクに変更
	SetMap(upper, { begin.x,begin.y + Chunk::kMaxHeight + 1 });
}