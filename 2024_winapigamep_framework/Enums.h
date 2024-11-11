#pragma once
enum class LAYER
{
	DEFAULT,
	BACKGROUND,
	PLAYER,
	ENEMY,
	BOSS,
	PROJECTILE,
	// UI
	END = 30
};

enum class PEN_TYPE
{
	HOLLOW, RED, GREEN,
	BLUE, YELLOW, END
};

enum class BRUSH_TYPE
{
	HOLLOW, RED, GREEN,
	BLUE, YELLOW, END
};


enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	END,
};

enum class BOSS_STATE
{
	PAWN, BISHOP, KNIGHT, ROOK, QUEEN, KING
};
