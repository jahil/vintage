#include "../vintage.h"
#define VINTAGE_CPI_TRK4_LEN 10788741
struct vintage_track vintage_cpi_trk4 = {
	.name = "netcat",
	.len  = VINTAGE_CPI_TRK4_LEN,
	.data = {
#include "trk4data.h"
	}
};
