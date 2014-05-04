#include <string>
#ifdef __cplusplus
extern "C" {  // only need to export C interface if
              // used by C++ source code
#endif

__declspec( dllimport ) int run(const char * path);

#ifdef __cplusplus
}
#endif