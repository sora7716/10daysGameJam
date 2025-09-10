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
	//マップのリセット
	if (player_->IsReset())
	{
		MapReset();//マップのリセット
	}

	for (std::list<ChunkTransitionData>::iterator it = chunkTransitionSwitchList_.begin(); it != chunkTransitionSwitchList_.end(); it++)
	{
		//マウスを設定
		it->switchResource->SetMousePos(*mousePos_);

		//更新
		it->switchResource->Update();

		//移動しているかどうか
		if (player_->IsMove())
		{
			Vector2 segmentBegin =
			{
				static_cast<float>(it->begin.x * kBlockSize),
				static_cast<float>(it->begin.y * kBlockSize)
			};

			Vector2 segmentEnd =
			{
				segmentBegin.x,
				segmentBegin.y + static_cast<float>(Chunk::kMaxWidth * kBlockSize),
			};

			if (it->isTransitionChunk && IsCrossPlayerOfSegment(segmentBegin, segmentEnd))
			{
				SwapChunk(it->underChunk, it->upperChunk, it->begin);
				it->isTransitionChunk = false;
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
			Vector2 segmentBegin =
			{
				static_cast<float>(it->begin.x * kBlockSize),
				static_cast<float>(it->begin.y * kBlockSize)
			};

			Vector2 segmentEnd =
			{
				segmentBegin.x,
				segmentBegin.y + static_cast<float>(Chunk::kMaxWidth * kBlockSize),
			};

			if (it->isInvertChunk && IsCrossPlayerOfSegment(segmentBegin, segmentEnd))
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
				for (MapDrawData& mData : mapDrawDatas_)
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

	//下の境界線
	for (int i = 1; i < underBorderLines_.size(); i++)
	{
		Novice::DrawLine
		(
			static_cast<int>(underBorderLines_[i].segment.origin.x),
			static_cast<int>(underBorderLines_[i].segment.origin.y),
			static_cast<int>(underBorderLines_[i].segment.origin.x + underBorderLines_[i].segment.diff.x),
			static_cast<int>(underBorderLines_[i].segment.origin.y + underBorderLines_[i].segment.diff.y),
			RED
		);
	}
}

//終了
Map::~Map()
{
	for (std::list<ChunkTransitionData>::iterator it = chunkTransitionSwitchList_.begin(); it != chunkTransitionSwitchList_.end(); it++)
	{
		delete it->switchResource;
		it->switchResource = nullptr;
	}
	chunkTransitionSwitchList_.clear();

	for (std::list<ChunkInvertData>::iterator it = chunkInvertSwitchList_.begin(); it != chunkInvertSwitchList_.end(); it++)
	{
		delete it->switchResource;
		it->switchResource = nullptr;
	}
	chunkInvertSwitchList_.clear();
}

//二行のマップ生成
void Map::CreateTowLineMap(Chunk* upperChunk, Chunk* underChunk, const Vector2Int& begin, int* textureHandles, bool isInitialize)
{
	//上のチャンクの読み込み
	SetMap(upperChunk, begin, isInitialize);

	//下のチャンクの読み込み
	SetMap(underChunk, { begin.x,begin.y + Chunk::kMaxHeight + 1 }, isInitialize);

	//反転スイッチの生成
	InitializeInvertSwitch({ begin.x,begin.y + Chunk::kMaxHeight + 1 }, textureHandles[static_cast<int>(SwitchTex::kInvert)]);

	//スイッチの生成と初期化
	GameSwitch* chunkChangeSwitch = new GameSwitch();
	chunkChangeSwitch->Initialize
	({
		static_cast<float>((begin.x + 2) * kBlockSize),
		static_cast<float>(begin.y * kBlockSize + Chunk::kMaxHeight * kBlockSize)

		}, {32.0f, 32.0f}, textureHandles[static_cast<int>(SwitchTex::kTransition)]
	);

	//切り替えスイッチのリストに追加
	chunkTransitionSwitchList_.push_back(ChunkTransitionData(chunkChangeSwitch, upperChunk, underChunk, begin, false));
}

//一行のマップ生成
void Map::CreateOneLineMap(Chunk* chunk, const Vector2Int& begin, int textureHandle, bool isInitialize)
{
	//チャンクの読み込み
	SetMap(chunk, begin, isInitialize);

	//初期化
	InitializeInvertSwitch(begin, textureHandle);
}

//チャンクの反転スイッチの生成
void Map::InitializeInvertSwitch(const Vector2Int& begin, int textureHandle)
{
	//スイッチの生成と初期化
	GameSwitch* chunkInvertSwitch = new GameSwitch();
	chunkInvertSwitch->Initialize
	({
		  static_cast<float>((begin.x + 2) * kBlockSize),
		  static_cast<float>((begin.y + Chunk::kMaxHeight + 1) * kBlockSize - kBlockSize / 2)
		}, { 32.0f, 32.0f },textureHandle);

	//リストの追加
	chunkInvertSwitchList_.push_back(ChunkInvertData(chunkInvertSwitch, begin));
}

//下の境界線の設定
void Map::SettingUnderBorderLine()
{
	for (std::list<ChunkInvertData>::iterator it = chunkInvertSwitchList_.begin(); it != chunkInvertSwitchList_.end(); it++)
	{
		CreateUnderBorderLine(it->begin);
	}
}

//マップのリセット
void Map::MapReset()
{
	for (MapData mapData : mapDatas_)
	{
		SetMap(mapData.chunk, mapData.begin);
	}
}

//mapのセッター
void Map::SetMap(Chunk* chunk, const Vector2Int& begin, bool isInitialize)
{
	for (int y = 0; y < Chunk::kMaxHeight; y++)
	{
		for (int x = 0; x < Chunk::kMaxWidth; x++)
		{
			map_[y + begin.y][x + begin.x] = chunk->GetChunk()[y][x];
		}
	}
	//マップの描画用のリストに追加
	mapDrawDatas_.push_back({ begin,chunk->GetTextureHandle() });
	//初期化だったら
	if (isInitialize) {
		//マップデータのリストに追加
		mapDatas_.push_back({ chunk,begin });

	}
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

//ボーダーラインの生成
void Map::CreateUnderBorderLine(const Vector2Int& begin)
{
	//下の境界線
	BorderLine underBorderline =
	{
		.segment
		{
			.origin =
			 {
			   static_cast<float>((begin.x) * kBlockSize),
			   static_cast<float>(begin.y * kBlockSize)
			 },
			.diff = {0.0f,static_cast<float>(Chunk::kMaxHeight * kBlockSize)}
		},
		.isCrossed = false
	};

	//下のボーダーラインのリストに追加
	underBorderLines_.push_back(underBorderline);
}

//線にプレイヤーが重なったかどうか
bool Map::IsCrossPlayerOfSegment(const Vector2& segmentBegin, const Vector2& segmentEnd)
{
	Vector2 begin = segmentBegin;
	Vector2 end = segmentEnd;

	Vector2 beginToEnd = end - begin;
	Vector2 playerToBegin = (player_->GetPlayerData().gameObject.center + player_->GetPlayerData().gameObject.radius + Vector2(static_cast<float>(kBlockSize/2), 0.0f)) - begin;

	return beginToEnd.Cross(playerToBegin) < 0.0f;
}
