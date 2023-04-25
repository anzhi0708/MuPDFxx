extern "C" {
#include <mupdf/fitz.h>
#include <mupdf/pdf/document.h>
#include <mupdf/pdf/page.h>
}
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <tuple>

// attributes: snake_case
// methods:    lowerCamelCase

namespace MuPDF {

class PDFPage {
public:
  PDFPage(pdf_page *page_ptr) {
    this->pdf_page_ptr = page_ptr;
    this->index = -1;
  }
  PDFPage(int index, pdf_page *page_ptr) {
    assert(index >= 0);
    this->index = index;
    this->pdf_page_ptr = page_ptr;
  }
  pdf_page *getPointer() { return this->pdf_page_ptr; }
  void setFitzRect(fz_rect rect) {
    this->rect = rect;
    this->x0 = rect.x0;
    this->x1 = rect.x1;
    this->y0 = rect.y0;
    this->y1 = rect.y1;
  }
  fz_rect getFitzRect() { return this->rect; }
  std::tuple<float, float, float, float> getRectAsTuple() {
    return std::make_tuple(this->x0, this->y0, this->x1, this->y1);
  }
  float getX0() { return this->x0; }
  float getY0() { return this->y0; }
  float getX1() { return this->x1; }
  float getY1() { return this->y1; }

private:
  int index;
  pdf_page *pdf_page_ptr;
  fz_rect rect;
  float x0;
  float y0;
  float x1;
  float y1;
};

class PDFDocument {
public:
  PDFDocument(const char *file_path) {
    this->ctx = fz_new_context(nullptr, nullptr, FZ_STORE_UNLIMITED);
    if (fz_file_exists(ctx, file_path)) {
      this->file_full_path = file_path;
      this->doc = pdf_open_document(ctx, file_path);
      this->n_pages = pdf_count_pages(ctx, doc);
    } else {
      fz_drop_context(this->ctx);
      std::cerr << "File not found." << std::endl;
      std::cerr << file_path << " not found" << std::endl;
      throw std::runtime_error("PDF file not found.");
    }
  }
  ~PDFDocument() {
    pdf_drop_document(this->ctx, this->doc);
    fz_drop_context(this->ctx);
  }
  size_t countPages() { return this->n_pages; }
  const char *getFileFullPath() { return this->file_full_path; }
  PDFPage loadPageAtIndex(int num) {
    assert(this->ctx != nullptr && this->doc != nullptr &&
           "context / document object not found");
    assert(this->n_pages != 0 && "this document has 0 pages");
    assert(num >= 0 && "negative page number is not allowed");
    assert(num < this->n_pages && "page number too large");
    pdf_page *target_page = pdf_load_page(this->ctx, this->doc, num);
    auto page_obj = PDFPage(num, target_page);
    page_obj.setFitzRect(
        fz_bound_page(this->ctx, (fz_page *)(page_obj.getPointer())));
    return page_obj;
  }
  PDFPage *getAllPages() {
    assert(this->ctx != nullptr && this->doc != nullptr);
    this->all_pages = (PDFPage *)malloc(sizeof(PDFPage) * this->n_pages);
    for (int i = 0; i < this->n_pages; ++i) {
      this->all_pages[i] = this->loadPageAtIndex(i);
    }
    return this->all_pages;
  }

private:
  const char *file_full_path;
  fz_context *ctx;
  pdf_document *doc;
  size_t n_pages;
  PDFPage *all_pages;
  void dropPage(PDFPage *page) {
    fz_drop_page(this->ctx, (fz_page *)(page->getPointer()));
  }
};

} // namespace MuPDF
