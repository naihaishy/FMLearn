//
// Created by naihai on 2020/1/28.
//

#include "score/score.h"

void Score::Initialize(HyperParam* hyper_param) {
  hyper_param_ = hyper_param;
}

Score::~Score() {
  delete hyper_param_;
  hyper_param_ = nullptr;
}
