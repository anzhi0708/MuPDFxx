#include "../src/PDFDocument.hpp"
#include <iostream>
#include <cstdio>
using namespace std;
using namespace MuPDF;

int main(int argc, char **argv) {
  assert(argc > 1);
  PDFDocument doc{argv[1]};
  cout << "File: " << doc.getFileFullPath() << endl;
  cout << "Pages: " << doc.countPages() << endl;
  // Getting the 1st page
  PDFPage first_page = doc.loadPageAtIndex(0);

  printf("X0: %f, X1: %f, Y0: %f, Y1: %f\n", first_page.getX0(), first_page.getX1(), first_page.getY0(), first_page.getY1());

  /* Getting rectangle {float, float, float, float} as a std::tuple
   *
   
  first_page.getRectAsTuple();

   *
   */

  fz_rect rect = first_page.getFitzRect();
  printf("x0: %f, y0: %f, x1: %f, y1: %f\n", rect.x0, rect.y0, rect.x1, rect.y1);

  return 0;
}
