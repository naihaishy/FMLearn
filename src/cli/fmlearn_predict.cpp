//
// Created by naihai on 2020/1/29.
// main entry for fmlearn prediction in command line

#include "common/log.h"
#include "common/utils.h"
#include "core/model.h"
#include "data/data.h"

#include "cli/cmdline.h"

int main(int argc, char* argv[]) {
  Logging::SetLevel(0);
  CmdLine cmd_line;
  cmd_line.SetPredict();

  if (cmd_line.Parse(argc, argv)) {
    // 构造DMatrix
    CliPredictionParam * param = cmd_line.GetCliParam()->GetPredictionParam();

    DMatrix* test_data = new DMatrix(param->test_file, false);

    auto fm = new FactorizationMachine(param->model_file);

    // fit
    fm->Initialize();

    // predict
    std::vector<float> results = fm->Predict(test_data);

    // save results to file
    SaveVectorToFile(results, param->output_file);

  } else {
    Logging::error("FMLearn command line parameter parse failed");
    exit(1);
  }

  return 0;
}

