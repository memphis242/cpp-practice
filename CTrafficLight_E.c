#include "CTrafficLight_E.h"
#include <cstdio>

#ifdef __cplusplus
extern "C" {
#endif

const char * CTrafficLight_E_ToString(enum CTrafficLight_E light)
{
   switch ( light )
   {
      case Green:
         return "Green (0)";
      
      case Yellow:
         return "Yellow (1)";

      case Red:
         return "Red (2)";

      default:
         static char str[12];
         sprintf( str, "Unknown: %d", (int)light );
         return (const char *)str;
   }
}

#ifdef __cplusplus
}
#endif
