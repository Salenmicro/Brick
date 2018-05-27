#include <fstream>

#include "brick.hpp"
#include "test_utils.hpp"
#include "gtest/gtest.h"

template <class T>
using tree = brick::tree::tree<T>;

std::string test_data_dir = "../test/data";

TEST(ReadAST, WhoCares) {
  std::ifstream input_file(test_data_dir + "/a.ast");
  tree<std::string> t = brick::io::read_ast<std::string>(input_file);
  tree<std::string> correct("+");
  correct.add_child("1").add_child("2");
  ASSERT_TRUE(t == correct);
}

TEST(WriteAST, SimpleCase) {
  std::string tmp_file = test_data_dir + "/tmp.ast";
  std::string correct_file = test_data_dir + "/a.ast";
  std::ofstream output_file(tmp_file);
  tree<std::string> t("+");
  t.add_child("1").add_child("2");
  bool write_success = brick::io::write_ast(t, output_file);
  ASSERT_TRUE(write_success);
  bool identical = brick::test::files_identical(correct_file, tmp_file);
  ASSERT_TRUE(identical);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  if (argc == 2) {
    test_data_dir = argv[1];
  }
  return RUN_ALL_TESTS();
}