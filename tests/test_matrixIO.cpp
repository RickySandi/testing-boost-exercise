#include <Eigen/Dense>
#include <boost/test/unit_test.hpp>
#include <cstdio>
#include <fstream>
#include "../src/matrixIO.hpp"

BOOST_AUTO_TEST_SUITE(matrixIO_tests)

BOOST_AUTO_TEST_CASE(test_openData)
{
  std::string   filename = "test_data.txt";
  std::ofstream outfile(filename);
  outfile << "1.0, 2.0" << std::endl;
  outfile << "3.0, 4.0" << std::endl;
  outfile.close();

  int             size   = 2;
  Eigen::MatrixXd result = matrixIO::openData(filename, size);

  BOOST_REQUIRE_EQUAL(result.rows(), 2);
  BOOST_REQUIRE_EQUAL(result.cols(), 2);

  BOOST_CHECK_CLOSE(result(0, 0), 1.0, 0.001);
  BOOST_CHECK_CLOSE(result(0, 1), 2.0, 0.001);
  BOOST_CHECK_CLOSE(result(1, 0), 3.0, 0.001);
  BOOST_CHECK_CLOSE(result(1, 1), 4.0, 0.001);

  std::remove(filename.c_str());
}

BOOST_AUTO_TEST_SUITE_END()