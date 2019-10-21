// Copyright 2019 Khruleva Anastasia
#include <gtest-mpi-listener.hpp>
#include <gtest/gtest.h>
#include <vector>
#include "./rows_max_mpi.h"

TEST(Parallel_Operations_MPI, Test_negative_value) {
  int rank;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  if (rank == 0) {
    ASSERT_ANY_THROW(getMatr(10, -7));
  }

 TEST(Parallel_Operations_MPI, Test_Zero) {
    int rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    if (rank == 0) {
      ASSERT_ANY_THROW(getMatr(0, 0));
    }

 TEST(Parallel_Operations_MPI, Test_parallel_sequental_small_size) {
      MPI_Comm_rank(MPI_COMM_WORLD, &rank);
      std::vector<int> w;
      std::vector<int> v;
      const int a = 5;
      const int b = 5;
      if (rank == 0) {
        w = getMart(a, b);
        v1 = getSequentialMax(w, a, b);
      }
      std::vector<int> v2 = getParallelMax(w, a, b);
      if (rank == 0) {
        ASSERT_EQ(v2, v1);
      }
    }

    TEST(Parallel_Operations_MPI, Test_parallel_sequental_big_size) {
      MPI_Comm_rank(MPI_COMM_WORLD, &rank);
      std::vector<int> w;
      std::vector<int> v1;
      const int a = 100;
      const int b = 100;
      if (rank == 0) {
        w = getMart(a, b);
      }
      std::vector<int> v2 = getParallelMax(w, a, b);
      if (rank == 0) {
        v1 = getSequentialMax(w, a, b);
        ASSERT_EQ(v2, v1);
      }
    }

    TEST(Parallel_Operations_MPI, Test_Correct_Solve) {
      int rank;
      MPI_Comm_rank(MPI_COMM_WORLD, &rank);
      const int p = 3;
      const int q = 4;
      if (rank == 0) {
        std::vector<int> first_matr = { 1, 7, 6, 4, 8, 2, 5, 9, 4, 3, 11, 1 };
        std::vector<int> first_max_matr = getMaxMatr(global_vec, p, q);
        std::vector<int> correct_vect = { 7, 9, 11 };
        ASSERT_EQ(correct_vect, first_max_matr);
      }
    }

    int main(int argc, char** argv) {
      ::testing::InitGoogleTest(&argc, argv);
      MPI_Init(&argc, &argv);

      ::testing::AddGlobalTestEnvironment(new GTestMPIListener::MPIEnvironment);
      ::testing::TestEventListeners& listeners =
        ::testing::UnitTest::GetInstance()->listeners();

      listeners.Release(listeners.default_result_printer());
      listeners.Release(listeners.default_xml_generator());

      listeners.Append(new GTestMPIListener::MPIMinimalistPrinter);
      return RUN_ALL_TESTS();
    }
