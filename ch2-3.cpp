#include <iostream>

/*****************************************/
/* Half-baked procedural vector class... */

// This is somehow supposed to be the "procedural" version of a class??
// Some of the commentary from Bjorne motivating the idea of classes
// implies that classes are the only way to couple data to operations
// on that data, but that's far from the truth. See any one of the many
// C collection libraries out there, including my own ccol!
// As far as I can tell, the main advantages OOP languages like C++ offer
// are mechanisms like interfaces and mix-ins, syntactic sugar like
// .<method> on an object to call associated methods, and an easier time
// generic programming (although that itself is a double-edged sword).
// Otherwise, you can still separate implementation from interface, have
// "private" invisible members and methods, and even do generic programming.

struct HalfBakedVector_S
{
   size_t sz;
   double * elements;
};

void VectorInit( HalfBakedVector_S&, size_t );
void VectorPrintToStdout( struct HalfBakedVector_S& self );
void VectorFree( struct HalfBakedVector_S& );
/*****************************************/
/*****************************************/

class Vector
{
   public:
      Vector(size_t sz):
         elements {new double[sz]},
         sz {sz}
         { }
      
      ~Vector()
      {
         delete[] elements;
      }
      
      double& operator[](int i)
      {
         return elements[i];
      }

      size_t Size()
      {
         return sz;
      }
      
      void Print()
      {
         for ( size_t i = 0; i < sz; i++ )
         {
            std::cout << elements[i] << " ";
         }
         std::cout << std::endl;
      }
      
   private:
      double * elements;
      size_t sz;
};

/*****************************************/

int main(void)
{
   /* Half-baked procedural vector class usage */
   struct HalfBakedVector_S vec1;
   VectorInit( vec1, 10 );
   // Print uninitialized elements of the vector...
   VectorPrintToStdout(vec1);
   VectorFree(vec1);

   /* First-draft of custom C++ vector class usage */
   Vector vec2(10);
   vec2.Print();
   // vec2's array will automatically be free'd when vec2 goes out of scope
   // and its destructor is called.
}

/*****************************************/
void VectorInit( struct HalfBakedVector_S& self, size_t sz )
{
   self.elements = new double[sz];
   self.sz = sz;
}

// Apparently, C++ lets you omit the `struct` keyword when declaring a struct
// type... As if it's an automatic typedef. I dislike that... But given how
// often aggergate types are typedef'd away in many places, this appeases
// that (laziness).
void VectorPrintToStdout( HalfBakedVector_S& self )
{
   for ( size_t i = 0; i < self.sz; i++ )
   {
      std::cout << self.elements[i] << " ";
   }
   std::cout << std::endl;
}

void VectorFree( struct HalfBakedVector_S& self )
{
   delete self.elements;
}
/*****************************************/
