#include "../src/PDFDocument.hpp"
#include <cstdio>
#include <iostream>
using namespace std;
using namespace MuPDF;

int main(int argc, char **argv) {
  assert(argc > 1);
  PDFDocument doc{argv[1]};
  cout << "File: " << doc.getFileFullPath() << endl;
  cout << "Pages: " << doc.countPages() << endl;

  // These 2 functions are the same.
  // Getting the 1st page
  PDFPage first_page = doc.loadPageAtIndex(0);
  // Getting the 3rd page (page at index 2)
  PDFPage third_page = doc.page(2);

  puts("=== Page 1 ===");

  printf("X0: %f; X1: %f; Y0: %f; Y1: %f\n", first_page.getX0(),
         first_page.getX1(), first_page.getY0(), first_page.getY1());

  puts("=== Page 3 ===");

  printf("X0: %f, Y0: %f; X1: %f, Y1: %f\n", third_page.x0, third_page.y0,
         third_page.x1, third_page.y1);

  return 0;
}
