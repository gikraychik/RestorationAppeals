#include <string>
#include "params.h"
#ifdef __cplusplus
extern "C" {  // only need to export C interface if
              // used by C++ source code
#endif

__declspec( dllexport ) void run(char *path, params_time *pt);
__declspec( dllexport ) void testing(my_test *t);

#ifdef __cplusplus
}
#endif