//
// Created by kode.zhong on 2021/1/9.
//

#ifndef LOX_INTERPRETER_TEST_TESTLOX_TEST_LOX_H_
#define LOX_INTERPRETER_TEST_TESTLOX_TEST_LOX_H_
#include "gtest/gtest.h"

// The fixture for testing class Foo.
class OSTest : public ::testing::Test {

 protected:

  // You can do set-up work for each test here.
  OSTest();

  // You can do clean-up work that doesn't throw exceptions here.
  ~OSTest() override;

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:

  // Code here will be called immediately after the constructor (right
  // before each test).
  void SetUp() override;

  // Code here will be called immediately after each test (right
  // before the destructor).
  void TearDown() override;
};
#endif