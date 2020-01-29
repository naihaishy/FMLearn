//
// Created by naihai on 2020/1/29.
// main entry for fmlearn prediction in command line

#include "cmdline.h"
#include <iostream>
#include <src/common/log.h>
#include <src/data/data.h>
#include <src/core/model.h>

int main(int argc, char* argv[]) {
  CmdLine cmd_line;
  cmd_line.SetPredict();

  if (cmd_line.Parse(argc, argv)) {
    // 构造DMatrix
    CliPredictionParam * param = cmd_line.GetCliParam()->GetPredictionParam();

    DMatrix* test_data = new DMatrix(param->test_file,
                                     param->file_format,
                                     param->file_sep,
                                      false);

    auto fm = new FactorizationMachine(param->model_file);

    // fit
    fm->Initialize();

    // predict
    std::vector<float> results = fm->Predict(test_data);

  } else {
    Logging::error("FMLearn command line parameter parse failed");
    exit(0);
  }

  return 0;
}

