#include "../vintage.h"
#define VINTAGE_CPI_TRK1_LEN 6409107
struct vintage_track vintage_cpi_trk1 = {
	.name = "Ishq Main Ji Ko",
	.len  = VINTAGE_CPI_TRK1_LEN,
	.data = {
#include "trk1data.h"
	}
};
