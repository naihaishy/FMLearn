//
// Created by naihai on 2020/1/28.
//

#ifndef FMLEARN_SCORE_FM_SCORE_H_
#define FMLEARN_SCORE_FM_SCORE_H_

#include "score/score.h"

/**
 * Usage :
 * FMScore *score = new FmScore();
 * score.CalGrad();
 */
class FmScore : public Score {
 public:
  ~FmScore() override;
  float Calculate(SparseRow* row, FMModel& model, float norm) override;
  void CalGrad(SparseRow* row, FMModel& model, float norm, float delta) override;
  std::string GetType() override { return type_; }

 private:
  std::string type_ = "FmScore";
};

#endif //FMLEARN_SCORE_FM_SCORE_H_
