//
// Created by naihai on 2020/2/20.
//

#include "solver/solver.h"
#include "solver/trainer.h"
#include "solver/predictor.h"

void Solver::Initialize(int argc, char** argv) {
  if (hyper_param_->is_train) {
    InitTrain();
  } else {
    InitPredict();
  }
}

void Solver::SetTrain() {
  hyper_param_->is_train = true;
}

void Solver::SetPredict() {
  hyper_param_->is_train = false;
}

/**
 * 初始化训练
 */
void Solver::InitTrain() {


}

/**
 * 初始化预测
 */
void Solver::InitPredict() {

}

void Solver::Start() {
  if (hyper_param_->is_train) {
    StartTrain();
  } else {
    StartPredict();
  }
}

void Solver::StartTrain() {
  Trainer trainer;
  trainer.Train();
}
void Solver::StartPredict() {

}

