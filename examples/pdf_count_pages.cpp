#include "../src/PDFDocument.hpp"
#include <iostream>
using namespace std;
using namespace MuPDF;

int main(int argc, char **argv) {
  assert(argc > 1);
  PDFDocument doc{argv[1]};
  cout << "File: " << doc.getFileFullPath() << endl;
  cout << "Pages: " << doc.countPages() << endl;
  return 0;
}
