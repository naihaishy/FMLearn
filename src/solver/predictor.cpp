//
// Created by naihai on 2020/2/19.
//

#include "solver/predictor.h"

#include "data/data.h"
#include "common/check.h"

void Predictor::Predict() {
  DMatrix* data = new DMatrix();
  reader_->Read(data);

  out_.clear();
  loss_->Predict(data, *model_, out_);
}
void Predictor::Initialize(DataReader* reader,
                           Loss* loss,
                           FMModel* model,
                           std::string& out_file) {

  CHECK_FALSE(reader == nullptr);
  CHECK_FALSE(loss == nullptr);
  CHECK_FALSE(model == nullptr);
  CHECK_FALSE(out_file.empty());

  reader_ = reader;
  loss_ = loss;
  model_ = model;
  out_file_ = out_file;
}
