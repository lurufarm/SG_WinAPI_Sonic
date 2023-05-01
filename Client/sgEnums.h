#pragma once

enum class eSceneType
{
	Title,
	//StageSelect,
	Play,
	Play2,
	Ending,
	End,
};

enum class eLayerType
{
	BG,
	BG2,
	hideMonster,
	hideObjects,
	MapObjects,
	MapDeco,
	Ground,
	Monster,
	RMonster,
	Bullet,
	Bomb,
	Item,
	Ring,
	Effect2,
	Player,
	Effect,
	Boss,
	Water,
	mEffect,
	ForeObject,
	UI,
	End,

};

enum class eLayerType_intro
{
	intro_bg,
	intro_sonic,
	intro_object,
	intro_object2,
	intro_Effect,
	intro_UI,
	End,

};

enum class eComponentType
{
	Transform,
	Collider,
	Rigidbody,
	SpriteRenderer,
	Animator,
	Audio,
	End,
};

enum class eSonicStateType
{
	Idle,
	Walk,
	Run,
	Crouch,
	Hurt,

	End,
};

