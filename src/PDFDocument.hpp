extern "C" {
#include <mupdf/fitz.h>
#include <mupdf/pdf/document.h>
}

namespace MuPDF {

class PDFDocument {

public:
  pdf_document *doc;
  fz_context *ctx;
  char *file_name;
  PDFDocument(const char *file_name) {
    ctx = fz_new_context(nullptr, nullptr, FZ_STORE_UNLIMITED);
    if (fz_file_exists(ctx, file_name)) {
      stream = fz_open_file(ctx, file_name);
      doc = pdf_open_document_with_stream(ctx, stream);
      this->n_pages = fz_count_pages(ctx, (fz_document*)doc);
    }
  }
  ~PDFDocument() {
    fz_drop_document(this->ctx, (fz_document*)this->doc);
    fz_drop_stream(this->ctx, this->stream);
    fz_drop_context(this->ctx);
  }
  size_t countPages() { return this->n_pages; }

private:
  fz_stream *stream;
  size_t n_pages;
};

} // namespace MuPDF
