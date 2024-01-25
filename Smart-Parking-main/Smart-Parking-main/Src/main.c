
#include "MCAL/MCAL.h"
#include "HAL/HAL.h"
#include "APP/SmartParking.h"

int main(void)
{
	MCAL_init();
	HAL_init();
	SmartParking_init();
	SmartParking_main();
}
