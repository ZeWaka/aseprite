// Aseprite
// Copyright (C) 2021 Igara Studio S.A.
//
// This program is distributed under the terms of
// the End-User License Agreement for Aseprite.

#ifndef APP_CMD_REMOVE_METADATA_H_INCLUDED
#define APP_CMD_REMOVE_METADATA_H_INCLUDED
#pragma once

#include "app/cmd.h"

namespace app {
namespace cmd {

  class RemoveMetadata : public Cmd {
  public:
    RemoveMetadata();

  protected:
    void onExecute() override;
  };

} // namespace cmd
} // namespace app

#endif  // CMD_REMOVE_METADATA_H_INCLUDED