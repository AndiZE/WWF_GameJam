#include "TileDirection.h"

ETileDirection UTileDirectionExtension::GetOpposite(ETileDirection Direction) {
	return (int)Direction < 2 ? ETileDirection((int)Direction + 2) : ETileDirection((int)Direction - 2);
}