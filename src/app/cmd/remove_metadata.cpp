// Aseprite
// Copyright (C) 2001-2015  David Capello
//
// This program is distributed under the terms of
// the End-User License Agreement for Aseprite.

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "app/cmd/remove_metadata.h"

#include "app/context_access.h"
#include "app/modules/editors.h"
#include "app/ui/editor/editor.h"

#include "app/file/file.h"
#include "app/file/file_format.h"
#include "app/file/file_formats_manager.h"
#include "dio/detect_format.h"

#include "app/file/png_options.h"

namespace app {
namespace cmd {

using namespace doc;

RemoveMetadata::RemoveMetadata()
{
}

void RemoveMetadata::onExecute()
{
  Context* ctx = context();
  ContextReader reader(ctx);
  Doc* document(reader.document());

  // Could also just do the dynamic pointer cast here, but less extensible.

  const std::string& filename = document->filename();

  dio::FileFormat dioFormat = dio::detect_format(filename);
  FileFormat* ff = FileFormatsManager::instance()->getFileFormat(dioFormat);

  if (ff->support(FILE_SUPPORT_METADATA)) {
    
    // Not sure how to properly do an interface for supporting clearing metadata based on this flag.
    // Just hardcoding PNGs for now...

    if (dioFormat == dio::FileFormat::PNG_IMAGE) {
      auto opts = std::dynamic_pointer_cast<PngOptions>(document->formatOptions());
      if (!opts) {
        // If the document doesn't have format options (or the type
        // doesn't matches T), we create default format options for
        // this file.
        opts = std::make_shared<PngOptions>();
      }

      opts->clearMetadata();
    }

  }
  return;
}

} // namespace cmd
} // namespace app
