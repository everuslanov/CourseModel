#include "headers/data/requirement.h"

Requirement::Requirement(int questionID, int responseID)
    : questionID_(questionID), responseID_(responseID) {}

int Requirement::questionID() const { return questionID_; }

int Requirement::responseID() const { return responseID_; }
