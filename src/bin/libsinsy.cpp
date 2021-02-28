#include "sinsy.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <emscripten/bind.h>

using namespace emscripten;

int run_sinsy(std::string xmlContent) {
  sinsy::Sinsy sinsy;

  std::string config = "dic";
  std::string languages("j");
  // std::string voice("nitech_jp_song070_f001.htsvoice");
  std::string voice("tohoku-f01-happy.htsvoice");
  std::cout << "VOICE: " << voice << std::endl;
  std::vector<std::string> voices;
  voices.push_back(voice);

  std::cout << "LANGUAGES: " << languages << std::endl;
  if (!sinsy.setLanguages(languages, config)) {
    std::cout << "[ERROR] failed to set languages : " << languages
              << ", config dir : " << config << std::endl;
    return -1;
  }

  std::cout << "SETTING VOICES?>>?>: " << std::endl;
  if (!sinsy.loadVoices(voices)) {
    std::cout << "[ERROR] failed to load voices : " << voice << std::endl;
    return -1;
  }

  if (!sinsy.loadScoreFromMusicXMLData(xmlContent)) {
    std::cout << "[ERROR] failed to load score from MusicXML data"
              << std::endl;
    return -1;
  }

  sinsy::SynthCondition condition;
  condition.setSaveFilePath("out.wav");

  sinsy.synthesize(condition);

  return 0;
}

EMSCRIPTEN_BINDINGS(sinsy) {
    function("run_sinsy", &run_sinsy);
}
