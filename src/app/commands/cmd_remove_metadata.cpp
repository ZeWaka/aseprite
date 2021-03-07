// Aseprite
// Copyright (C) 2021 Igara Studio S.A.
//
// This program is distributed under the terms of
// the End-User License Agreement for Aseprite.

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "app/app.h"
#include "app/commands/command.h"
#include "app/context_access.h"
#include "app/modules/editors.h"
#include "app/ui/editor/editor.h"

#include "app/file/file.h"
#include "app/file/file_format.h"
#include "app/file/file_formats_manager.h"
#include "dio/detect_format.h"

#include "app/file/png_options.h"

namespace app {

class RemoveMetadataCommand : public Command {
public:
  RemoveMetadataCommand();

protected:
  bool onEnabled(Context* context) override;
  void onExecute(Context* context) override;
};

RemoveMetadataCommand::RemoveMetadataCommand()
  : Command(CommandId::RemoveMetadata(), CmdUIOnlyFlag)
{
}

bool RemoveMetadataCommand::onEnabled(Context* context)
{
  return context->checkFlags(ContextFlags::ActiveDocumentIsWritable |
                              ContextFlags::HasActiveSprite);
}

void RemoveMetadataCommand::onExecute(Context* context)
{

  ContextReader reader(context);
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

Command* CommandFactory::createRemoveMetadataCommand()
{
  return new RemoveMetadataCommand;
}

} //namespace app
