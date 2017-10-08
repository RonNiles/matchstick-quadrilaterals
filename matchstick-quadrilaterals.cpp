
/* compute number of nondegenerate quadrilaterals of perimeter n modulo "gentle pushing"  
   per James East set description */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

/* these represent the "white balls" which partition the "red balls" */
const unsigned nsetbits = 3;

/* this represents the total number of red and white balls for partitioning, it's actually n-1 where n is the 
   perimiter of the quadrilateral */
unsigned ntotbits;


/* the string contains only zeros and ones, where ones are white balls and zeros are red balls */
bool process_string(const std::string &nd) {
   std::vector<unsigned> sides;
   sides.push_back(0);
   for (std::string::const_iterator i = nd.begin(); i != nd.end(); ++i) {
      ++sides.back();
      if (*i == '1') {
         sides.push_back(0);
      }
   }
   ++sides.back();
   /* "sides" now contains an element of a,b,c,d in Z+,a+b+c+d=n, where n is the perimiter of the quadrilateral */

   /* filter out anything except for a quadrilateral in canonical form */
   /* check for d >=a,b,c */
   unsigned sum=0;
   for (unsigned i=0;i<3;++i) {
      if (sides[3] < sides[i]) return false;
      sum += sides[i];
   }

   /*check for a+b+c >d */
   if (sum <= sides[3]) return false;

   /* check for a<=c<d or a<=b<=c==d */
   bool good = false;
   if (sides[0]<=sides[2] && sides[2] < sides[3]) good = true;
   if (sides[0]<=sides[1] && sides[1] <=sides[2] && sides[2] == sides[3]) good = true;
   if (!good) return false;

   return true;
}

unsigned compute_quadrilaterals(unsigned perimeter) {
   std::string nd;

   ntotbits = perimeter-1;
   nd.append(ntotbits - nsetbits, '0');
   nd.append(nsetbits, '1');

   unsigned total_quadrilaterals = 0;
   do {
      if (process_string(nd)) ++total_quadrilaterals;
   } while(next_permutation(nd.begin(), nd.end()));
   return total_quadrilaterals;
}

int main(int argc, char *argv[]) {
   try {
      ntotbits--;
      for (unsigned perimeter=4; perimeter<=50;++perimeter) {
         unsigned nq = compute_quadrilaterals(perimeter);
         std::cout << "Total for n=" << perimeter << ": " << nq << std::endl;
      }
   } catch (std::exception &x) {
      std::cout << std::endl << x.what() << std::endl;
      return 1;
   }
   return 0;
}
