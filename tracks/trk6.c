#include "../vintage.h"
#define VINTAGE_CPI_TRK6_LEN 13025371
struct vintage_track vintage_cpi_trk6 = {
	.name = "Approximating the Circumference of the Earth",
	.len  = VINTAGE_CPI_TRK6_LEN,
	.data = {
#include "trk6data.h"
	}
};
