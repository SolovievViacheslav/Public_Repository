#include "build_time.h"
#define BULD_DATE_TIME_STR QString(" ")+"Build "+QString(__DATE__)+" "+QString(__TIME__)

QString get_build_dt()
{
    return BULD_DATE_TIME_STR;
}
//