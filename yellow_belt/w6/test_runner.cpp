//
// Created by dkushn on 29.08.19.
//

#include "test_runner.h"

void Assert(bool b, const string& hint) {
    AssertEqual(b, true, hint);
}
