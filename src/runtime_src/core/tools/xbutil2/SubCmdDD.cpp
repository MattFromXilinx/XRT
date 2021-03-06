/**
 * Copyright (C) 2019-2020 Xilinx, Inc
 *
 * Licensed under the Apache License, Version 2.0 (the "License"). You may
 * not use this file except in compliance with the License. A copy of the
 * License is located at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */

// ------ I N C L U D E   F I L E S -------------------------------------------
// Local - Include Files
#include "SubCmdDD.h"
#include "tools/common/XBUtilities.h"
namespace XBU = XBUtilities;

// 3rd Party Library - Include Files
#include <boost/program_options.hpp>
#include <boost/format.hpp>
namespace po = boost::program_options;

// System - Include Files
#include <iostream>

// ----- C L A S S   M E T H O D S -------------------------------------------

SubCmdDD::SubCmdDD(bool _isHidden, bool _isDepricated, bool _isPreliminary)
    : SubCmd("dd", 
             "Perform block reads or writes to-device-from-file or from-device-to-file")
{
  const std::string longDescription = "Perform block read or writes to-device-from-file or from-device-to-file.";
  setLongDescription(longDescription);
  setExampleSyntax("");
  setIsHidden(_isHidden);
  setIsDeprecated(_isDepricated);
  setIsPreliminary(_isPreliminary);
}

void
SubCmdDD::execute(const SubCmdOptions& _options) const
// Reference Command:  dd -i inputFile -o outputFile -b blockSize -c count -p blocksToSkip -e seek
    /*
     * do_dd
     *
     * Perform block read or writes to-device-from-file or from-device-to-file.
     *
     * Usage:
     * dd -d0 --if=in.txt --bs=4096 --count=16 --seek=10
     * dd -d0 --of=out.txt --bs=1024 --count=4 --skip=2
     * --if : specify the input file, if specified, direction is fileToDevice
     * --of : specify the output file, if specified, direction is deviceToFile
     * --bs : specify the block size OPTIONAL defaults to value specified in 'dd.h'
     * --count : specify the number of blocks to copy
     *           OPTIONAL for fileToDevice; will copy the remainder of input file by default
     *           REQUIRED for deviceToFile
     * --skip : specify the source offset (in block counts) OPTIONAL defaults to 0
     * --seek : specify the destination offset (in block counts) OPTIONAL defaults to 0
     */

{
  XBU::verbose("SubCommand: dd");
  // -- Retrieve and parse the subcommand options -----------------------------
  std::string sInputFile;
  std::string sOutputFile;
  std::string sBlockSize;
  std::string sCount;
  std::string sSkip;
  std::string sSeek;
  bool help = false;

  po::options_description ddDesc("Options");
  ddDesc.add_options()
    ("help", boost::program_options::bool_switch(&help), "Help to use this sub-command")
    ("if,i", boost::program_options::value<std::string>(&sInputFile), "Input file, if specified, direction is fileToDevice")
    ("of,o", boost::program_options::value<std::string>(&sOutputFile), "Output file, if specified, direction is deviceToFile")
    ("bs,b", boost::program_options::value<std::string>(&sBlockSize), "Block size, default value: 4096 Bytes")
    ("count,c", boost::program_options::value<std::string>(&sCount), "Number of blocks to copy.\n"
                                                                     "  Optional for file-to-device; will copy the remainder of the input file.\n"
                                                                     "  Required for device-to-file.")
    ("skip,p", boost::program_options::value<std::string>(&sSkip), "Source offset (in block counts)")
    ("seek,e", boost::program_options::value<std::string>(&sSeek), "Destination offset (in block counts)")
  ;

  // Parse sub-command ...
  po::variables_map vm;

  try {
    po::store(po::command_line_parser(_options).options(ddDesc).run(), vm);
    po::notify(vm); // Can throw
  } catch (po::error& e) {
    std::cerr << "ERROR: " << e.what() << std::endl << std::endl;
    printHelp(ddDesc);
    // Re-throw exception
    throw;
  }

  // Check to see if help was requested or no command was found
  if (help == true)  {
    printHelp(ddDesc);
    return;
  }

  // -- Now process the subcommand --------------------------------------------
  XBU::verbose(boost::str(boost::format(" InputFile: %s") % sInputFile.c_str()));
  XBU::verbose(boost::str(boost::format("OutputFile: %s") % sOutputFile.c_str()));
  XBU::verbose(boost::str(boost::format(" BlockSize: %s") % sBlockSize.c_str()));
  XBU::verbose(boost::str(boost::format("     Count: %s") % sCount.c_str()));
  XBU::verbose(boost::str(boost::format("      Skip: %s") % sSkip.c_str()));
  XBU::verbose(boost::str(boost::format("      Seek: %s") % sSeek.c_str()));


  XBU::error("COMMAND BODY NOT IMPLEMENTED.");
  // TODO: Put working code here
}

