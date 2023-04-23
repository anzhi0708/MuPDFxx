#include "../pdf/Document.cpp"
#include <iostream>
using namespace std;
using namespace MuPDF;

int main(int argc, char **argv) {
  assert(argc > 1);
  PDFDocument doc{argv[1]};
  cout << "Pages: " << doc.countPages() << endl;
  return 0;
}
