#pragma once

#include "BlockBase.h"

enum class eHatenaState {
	COIN = 0,	//コイン
	ITEM,		//スーパーキノコ、ファイアフラワー
	UP,			//１アップキノコ
	STAR,		//スター
};

class Hatena :public BlockBase
{
public:
	std::vector<int> anim_img;		// アニメーション画像
	float anim_time;
	int anim_count;
	int move_count;
	bool is_animation;
	int empty_image;
	eHatenaState type;
	bool is_empty;

public:
	Hatena();
	~Hatena();

public:
	virtual void Initialize() override;
	virtual void Update(float delta_second) override;
	virtual void Draw(const Vector2D camera_pos) const override;
	virtual void Finalize() override;
	virtual void OnHitCollision(GameObject* hit_object) override;
	void SetType(eHatenaState type);

private:
	void AnimationControl(float delta_second);
	void CreateItem(GameObject* player);
};

