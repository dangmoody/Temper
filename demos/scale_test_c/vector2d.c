#include "vector2d.h"
#include <math.h>

//==========================================================

vector2d Vector2D_Add( vector2d A, vector2d B ){
	return ( vector2d ) { A.x + B.x, A.y + B.y };
}

//==========================================================

vector2d Vector2D_Sub( vector2d A, vector2d B ){
	return ( vector2d ) { A.x - B.x, A.y - B.y };
}

//==========================================================

vector2d Vector2D_Mul( vector2d A, vector2d B ){
	return ( vector2d ) { A.x* B.x, A.y* B.y };
}

//==========================================================

vector2d Vector2D_Div( vector2d A, vector2d B ){
	return ( vector2d ) { A.x / B.x, A.y / B.y };
}

//==========================================================

vector2d Vector2D_Normalize( vector2d vector ){
	float length = Vector2D_GetLength( vector );
	return ( vector2d ) {vector.x / length, vector.y / length};
}

//==========================================================

float Vector2D_GetLength( vector2d vector ){
	return sqrtf( ( vector.x * vector.x ) + ( vector.y * vector.y ) );
}

//==========================================================