extern "C" {
#include <mupdf/fitz.h>
#include <mupdf/pdf/document.h>
}
#include <iostream>
#include <stdexcept>

namespace MuPDF {

class PDFDocument {

public:
  PDFDocument(const char *file_name) {
    ctx = fz_new_context(nullptr, nullptr, FZ_STORE_UNLIMITED);
    if (fz_file_exists(ctx, file_name)) {
      this->file_name = file_name;
      doc = pdf_open_document(ctx, file_name);
      this->n_pages = fz_count_pages(ctx, (fz_document *)doc);
    } else {
      fz_drop_context(this->ctx);
      std::cerr << "File not found:\n" << file_name << " not found" << std::endl;
      throw std::runtime_error("PDF file not found.");
    }
  }
  ~PDFDocument() {
    fz_drop_document(this->ctx, (fz_document *)this->doc);
    fz_drop_context(this->ctx);
  }
  size_t countPages() { return this->n_pages; }
  const char *getFileName() { return this->file_name; }

private:
  const char *file_name;
  size_t n_pages;
  pdf_document *doc;
  fz_context *ctx;
};

} // namespace MuPDF
