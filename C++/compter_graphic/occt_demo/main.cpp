#include <iostream>
#include <filesystem>
#include <string>
#include <STEPCAFControl_Reader.hxx>
#include <TDocStd_Application.hxx>
#include <TDocStd_Document.hxx>
#include <argparse.hpp>
#include <regex>
#include <XCAFDoc_DocumentTool.hxx>
#include <XCAFDoc_ShapeTool.hxx>
#include <XCAFDoc_Color.hxx>
#include <TDataStd_Name.hxx>
#include <exception>
#include <TDF_ChildIterator.hxx>
#include "StepReader.hpp"


int main(int argc, char **argv) {
  argparse::ArgumentParser program("demo", "0.0.1");
  program.add_argument("-i").required().help("specify the input step type module file");
  program.add_argument("-o")
          .help("result output file");

  try {
    program.parse_args(argc, argv);
  } catch (const std::runtime_error &err) {
    std::cout << err.what() << std::endl;
    std::cout << program;
    exit(0);
  }

  std::string input_file_name = program.get<std::string>("-i");
  std::string output_file_name;
  std::ostream *out = nullptr;
  try {
    output_file_name = program.get<std::string>("-o");
    out = new std::ofstream(output_file_name, std::ios::app | std::ios::binary);
  } catch (...) {
    out = &std::cout;
  }

  std::regex regStp(".+\\.ste?pz?$", std::regex_constants::icase);
  if (!std::regex_match(input_file_name, regStp)) {
    std::cout << "Invalid step file ext.";
  }
  StepReader stepReader(input_file_name);
  if (!stepReader.parse()) {
    return -1;
  }


  *out << stepReader;
  if (!output_file_name.empty()) {
    delete out;
  }

  return 0;
}
