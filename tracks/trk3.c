#include "../vintage.h"
#define VINTAGE_CPI_TRK3_LEN 7152046
struct vintage_track vintage_cpi_trk3 = {
	.name = "Sad Jalwa Roo Baroo",
	.len  = VINTAGE_CPI_TRK3_LEN,
	.data = {
#include "trk3data.h"
	}
};
