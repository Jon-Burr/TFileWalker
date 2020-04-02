#include <boost/program_options.hpp>
#include <iostream>
#include <fstream>

#include "TFileWalker/Walker.h"
#include "TFileWalker/OutputHandler.h"
#include "TFileWalker/FileHandler.h"
#include "TFileWalker/RuleParser.h"

int main(int argc, char* argv[]) {
  std::string config; //> Optionally read command-line options from a config file
  std::string output; //> The output file location
  bool overwrite{false}; //> Allow overwriting the output file
  std::vector<std::string> inputFiles; //> The input files
  std::string inTxt; //> A text file containing a list of input files
  std::string rulesTxt; //> A text file containing a list of rules
  std::string inputLoc; //> The path all inputs are relative to
  bool noFileNameInRules; //> Is the input filename specified in the rules

  namespace po = boost::program_options;
  po::options_description desc("Allowed options");
  desc.add_options()
    ("config,c", po::value(&config), "Optionally read options from a config file")
    ("output,o", po::value(&output)->default_value("hist-out.root"), "The output ROOT file location")
    ("overwrite,w", po::bool_switch(&overwrite), "Enable overwriting of the output file")
    ("inTxt,I", po::value(&inTxt), "Text file containing inputs")
    ("rules,R", po::value(&rulesTxt), "Text file containing a list of targets")
    ("in-loc", po::value(&inputLoc)->default_value(""), "The location for input files")
    ("no-file-name-in-rules", po::bool_switch(&noFileNameInRules), "Rules do not reference the input file name")
    ("help,h", "Print this message and exit");
  po::options_description hidden("Hidden options");
  hidden.add_options()
    ("inputFiles", po::value(&inputFiles) );
  po::positional_options_description positional;
  positional.add("inputFiles", -1);
  po::variables_map vm;
  po::options_description allOptions;
  allOptions.add(desc).add(hidden);
  po::store(po::command_line_parser(argc, argv).options(allOptions).positional(positional).run(), vm);
  po::notify(vm);
  if (vm.count("config") ) {
    std::ifstream ifs(config);
    po::store(po::parse_config_file(ifs, allOptions), vm);
    po::notify(vm);
  }
  if (vm.count("help") ) {
    std::cout << desc << std::endl;
    return 0;
  }

  // Prepare input
  if (!inTxt.empty() ) {
    std::string line;
    std::ifstream inTxtFin(inTxt);
    if (!inTxtFin.is_open() ) {
      std::cerr << "Failed to open input text file " << inTxt << std::endl;
      return 1;
    }
    while (std::getline(inTxtFin, line) )
      if (!line.empty() )
        inputFiles.push_back(line);
  }

  TFileWalker::FileHandler inputHandler(inputLoc, "READ");

  TFileWalker::Walker walker(
      TFileWalker::RuleParser::parseFile(rulesTxt, !noFileNameInRules),
      TFileWalker::OutputHandler(output, overwrite ? "RECREATE" : "CREATE") );

  for (const std::string& fileName : inputFiles)
    walker.walk(inputHandler, fileName);

  walker.outputHandler().write();
}
