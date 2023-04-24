extern "C" {
#include <mupdf/fitz.h>
#include <mupdf/pdf/document.h>
#include <mupdf/pdf/page.h>
}
#include <iostream>
#include <stdexcept>

namespace MuPDF {

class PDFDocument {

public:
  PDFDocument(const char *file_path) {
    ctx = fz_new_context(nullptr, nullptr, FZ_STORE_UNLIMITED);
    if (fz_file_exists(ctx, file_path)) {
      this->file_full_path = file_path;
      doc = pdf_open_document(ctx, file_path);
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

private:
  const char *file_full_path;
  size_t n_pages;
  pdf_document *doc;
  fz_context *ctx;
};

} // namespace MuPDF
