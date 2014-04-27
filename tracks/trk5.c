#include "../vintage.h"
#define VINTAGE_CPI_TRK5_LEN 858054
struct vintage_track vintage_cpi_trk5 = {
	.name = "Interrupt 0xbb",
	.len  = VINTAGE_CPI_TRK5_LEN,
	.data = {
#include "trk5data.h"
	}
};
