//
// Created by naihai on 2020/2/19.
//

#include "solver/predictor.h"

#include "data/data.h"
#include "common/check.h"

void Predictor::Predict() {
  auto data = new DMatrix();
  reader_->Initialize();
  reader_->Read(data);
  out_.clear();
  loss_->Predict(data, *model_, out_);

  // 保存结果
  if (!out_file_.empty()) {
    std::ofstream ofs(out_file_);
    for (auto res:out_) ofs << std::to_string(res) << std::endl;
    ofs.flush();
    ofs.close();
  }
}
void Predictor::Initialize(DataReader* reader,
                           Loss* loss,
                           FMModel* model,
                           std::string& out_file) {

  CHECK_FALSE(reader == nullptr);
  CHECK_FALSE(loss == nullptr);
  CHECK_FALSE(model == nullptr);

  reader_ = reader;
  loss_ = loss;
  model_ = model;
  out_file_ = out_file;
}
