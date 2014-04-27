#include "../vintage.h"
#define VINTAGE_CPI_TRK2_LEN 3392625
struct vintage_track vintage_cpi_trk2 = {
	.name = "Zikr Us Pariwash Ka",
	.len  = VINTAGE_CPI_TRK2_LEN,
	.data = {
#include "trk2data.h"
	}
};
