#include "CppTrafficLight_E.hpp"
#include <iostream>

// Prefix Increment
CppTrafficLight_E& operator ++ (CppTrafficLight_E& light)
{
   switch( light )
   {
      case CppTrafficLight_E::Green:
         light = CppTrafficLight_E::Yellow;
         break;

      case CppTrafficLight_E::Yellow:
         light = CppTrafficLight_E::Red;
         break;

      case CppTrafficLight_E::Red:
         // Wrap back around
         light = CppTrafficLight_E::Green;
         break;
      
      default:
         // TODO: Throw exception: Invalid operation on traffic light enum
         break;
   }
   return light;
}

// Postfix Increment
CppTrafficLight_E operator ++ (CppTrafficLight_E& light, int)
{
   CppTrafficLight_E old = light;
   ++light;
   return old;
}

std::ostream& operator << ( std::ostream& os, CppTrafficLight_E light )
{
   switch ( light )
   {
      case CppTrafficLight_E::Green:
         return os << "Green (0)";

      case CppTrafficLight_E::Yellow:
         return os << "Yellow (1)";

      case CppTrafficLight_E::Red:
         return os << "Red (2)";
      
      default:
         return os << "Unknown";
   }
}
