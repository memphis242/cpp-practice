#include <iostream>

enum class CppTrafficLight_E
{
   Green,
   Yellow,
   Red,
   NumOfTrafficLightOptions
};

// Iterator "free" functions
CppTrafficLight_E begin(CppTrafficLight_E);
CppTrafficLight_E end(CppTrafficLight_E);

// Overloaded operators
CppTrafficLight_E& operator ++ ( CppTrafficLight_E& ); // Prefix Increment
CppTrafficLight_E operator ++ ( CppTrafficLight_E&, int ); // Postfix Increment
CppTrafficLight_E operator * ( CppTrafficLight_E );
std::ostream& operator << ( std::ostream&, CppTrafficLight_E );
