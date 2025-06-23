#include "CppTrafficLight_E.hpp"
#include <iostream>

CppTrafficLight_E begin(CppTrafficLight_E)
{
   return CppTrafficLight_E::Green;
}

CppTrafficLight_E end(CppTrafficLight_E)
{
   return CppTrafficLight_E::NumOfTrafficLightOptions;
}

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

CppTrafficLight_E begin(void)
{
   return CppTrafficLight_E::Green;
}

CppTrafficLight_E end(void)
{
   return CppTrafficLight_E::Red;
}

CppTrafficLight_E operator * ( CppTrafficLight_E light )
{
   return light;
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

      case CppTrafficLight_E::NumOfTrafficLightOptions:
         return os << "Number of Traffic Light Options (3)";
      
      default:
         return os << "Unknown";
   }
}

