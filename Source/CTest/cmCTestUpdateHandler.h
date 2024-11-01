/* Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
   file Copyright.txt or https://cmake.org/licensing for details.  */
#pragma once

#include "cmConfigure.h" // IWYU pragma: keep

#include <string>
#include <utility>
#include <vector>

#include "cmCTestGenericHandler.h"

class cmCTest;

/** \class cmCTestUpdateHandler
 * \brief A class that handles ctest -S invocations
 *
 */
class cmCTestUpdateHandler : public cmCTestGenericHandler
{
public:
  using Superclass = cmCTestGenericHandler;

  /*
   * The main entry point for this class
   */
  int ProcessHandler() override;

  cmCTestUpdateHandler(cmCTest* ctest);

  enum
  {
    e_UNKNOWN = 0,
    e_CVS,
    e_SVN,
    e_BZR,
    e_GIT,
    e_HG,
    e_P4,
    e_LAST
  };

private:
  // Some structures needed for update
  struct StringPair : public std::pair<std::string, std::string>
  {
  };
  struct UpdateFiles : public std::vector<StringPair>
  {
  };

  // Determine the type of version control
  int DetermineType(const char* cmd, const char* type);

  // The VCS command to update the working tree.
  std::string UpdateCommand;
  std::string SourceDirectory;
  int UpdateType = e_CVS;

  int DetectVCS(const std::string& dir);
  bool SelectVCS();

  friend class cmCTestUpdateCommand;
};
