//
// Created by naihai on 2020/1/29.
// main entry for fmlearn train in command line

#include "cmdline.h"
#include <iostream>
#include <src/data/data.h>
#include <src/core/model.h>
#include <src/common/log.h>

int main(int argc, char* argv[]) {
  CmdLine cmd_line;
  cmd_line.SetTrain();

  if (cmd_line.Parse(argc, argv)) {
    // 构造DMatrix
    CliTrainParam * param = cmd_line.GetCliParam()->GetTrainParam();
    Logging::info(param->to_string());
    DMatrix* train_data = new DMatrix(param->train_file,
                                      param->file_format,
                                      param->file_sep,
                                      true);
    int n_features = train_data->GetNumFeatures();
    std::cout << n_features << std::endl;

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
    fm->Fit(train_data, param->n_epoch);
    // save model
    fm->GetModel()->Save(param->model_file);
  } else {
    Logging::error("FMLearn command line parameter parse failed");
    exit(0);
  }

  return 0;
}