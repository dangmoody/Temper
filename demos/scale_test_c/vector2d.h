#ifndef VECTOR2D_HEADER
#define VECTOR2D_HEADER

typedef struct vector2d
{
	float x, y;
}vector2d;

vector2d Vector2D_Add( vector2d A, vector2d B );
vector2d Vector2D_Sub( vector2d A, vector2d B );
vector2d Vector2D_Mul( vector2d A, vector2d B );
vector2d Vector2D_Div( vector2d A, vector2d B );
vector2d Vector2D_Normalize( vector2d vector );
float Vector2D_GetLength( vector2d vector );

#endif //VECTOR2D_HEADER