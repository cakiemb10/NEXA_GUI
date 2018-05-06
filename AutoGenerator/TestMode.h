// Define this when unit testing
//#define DGT_UNIT_TEST_MODE

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#ifdef DGT_UNIT_TEST_MODE //&& !defined(__cplusplus)
#define private public
#define protected public


#endif  /* DGT_UNIT_TEST_MODE */