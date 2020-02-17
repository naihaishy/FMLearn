//
// Created by naihai on 2020/1/29.
// main entry for fmlearn train in command line

#include "common/log.h"
#include "core/model.h"
#include "data/data.h"

#include <ctime>

#include "cli/cmdline.h"

int main(int argc, char* argv[]) {
  Logging::SetLevel(0);
  CmdLine cmd_line;
  cmd_line.SetTrain();

  if (cmd_line.Parse(argc, argv)) {

    CliTrainParam* param = cmd_line.GetCliParam()->GetTrainParam();
    LogInfo(param->to_string());

    // 构造DMatrix
    DMatrix* train_data = new DMatrix(param->train_file, true);
    int n_features = train_data->GetNumFeatures();

    auto fm = new FactorizationMachine(param->task,
                                       n_features,
                                       param->n_factors,
                                       param->learning_rate,
                                       param->reg_w0,
                                       param->reg_W,
                                       param->reg_V,
                                       param->init_mean,
                                       param->init_stddev,
                                       param->norm,
                                       !param->quiet);
    // fit
    fm->Initialize();
    time_t start_time = time(nullptr);
    fm->Fit(train_data, param->n_epoch, param->n_thread > 1, param->n_thread);
    time_t end_time = time(nullptr);
    LogInfo("FactorizationMachine Fit done, cost " +
        std::to_string((end_time - start_time)) + " s");
    // save model
    fm->GetModel()->Save(param->model_file);
  } else {
    LogError("FMLearn command line parameter parse failed");
    exit(1);
  }

  return 0;
}