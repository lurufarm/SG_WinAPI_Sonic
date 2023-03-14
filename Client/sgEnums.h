#pragma once

enum class eSceneType
{
	Title,
	//StageSelect,
	Play,
	Ending,
	End,
};

enum class eLayerType
{
	BG,
	BG2,
	MapObjects,
	MapDeco,
	Monster,
	Item,
	Ring,
	Player,
	Effect,
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

