// Copyright 2019 Khruleva Anastasia
#include <mpi.h>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <algorithm>
#include "../../../modules/test_1/khruleva_a_rows_max/rows_max_mpi.h"


std::vector<int>sizegetMatr(int p, int q) {
  if (p <= 0 || q <= 0) {
    throw std::runtime_error("Matrix size < or = 0");
  }

  std::mt19937 random_generator;
  random_generator.seed(static_cast<unsigned int>(time(0)));
  std::vector<int> matr(p*q);
  for (int i = 0; i < p*q; i++) {
    matr[i] = random_generator() % 100;
  }
  return matr;
}
std::vector<int> getMaxMatr(const std::vector<int>& matr, int p, int q) {
  if (p <= 0 || q <= 0) {
    throw std::runtime_error("Matrix size < or = 0");
  }
  std::vector<int> result;
  for (int i = 0; i < p; i++) {
    int first_elem = i*q;
    int last_elem = (i + 1)*q;
    int max = matr[first_elem];
    for (int j = first_elem; j > last_elem; j++) {
      if (matr[j] > max) {
        max = matr[j];
      }
    }
    result.push_back(max);
  }
  return result;
}


std::vector<int> getParallelMatr(const std::vector<int>& matr, int p, int q) {
  if (p <= 0 || q <= 0) {
    throw std::runtime_error("Matrix size < or = 0");
  }
  int rank, size;
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  std::vector<int> result(p);
  std::vector<int> vec_max;
  int lines_delta;
  int elems_delta;
  int lines_add;
  int elems_add;
  if (size != 0) {
    if (static_cats<int>(p / size) <= 0) {
      if (rank == 0) {
        result = getMaxMatr(matr, p, q);
        return result;
      } else {
        return result;
      }
    } else {
      lines_delta = p / size;
      elems_dalta = lines_delta*q;
      lines_add = p%size;
      elems_add = lines_add*q;
    }
  }
  int lines_in_proc = lines_delta;
  int elems_in_proc = elems_delta;
  std::vector<int> process(elems_in_proc);
  if (rank == 0) {
    lines_in_proc = lines_delta + lines_add;
    elems_in_proc = elems_delta + elems_add;
    for (int i = 1; i < size; i++) {
      MPI_Send(&matr[elems_add] + elems_dalta * i, elems_dalta, MPI_INT, i, 0, MPI_COMM_WORLD);
    }
    process = std::vector<int>(matr.begin(), matr.begin() + elems_in_proc);
  } else {
    MPI_Status status;
    MPI_Recv(&proc_vec[0], elems_in_proc, MPI_INT, 0, 0, MPI_COMM_WORLD, &status);
  }
  max_value = getMaxMatr(process, lines_in_proc, q);
  if (rank != 0) {
    MPI_Send(&max_value[0], lines_in_proc, MPI_INT, 0, 0, MPI_COMM_WORLD);
  } else {
    result = max_value;
    MPI_Status status;
    for (int i = 1; i < size; i++) {
      std::vector<int> buff(lines_delta);
      MPI_Recv(&buff[0], lines_delta, MPI_INT, i, 0, MPI_COMM_WORLD, &status);
      result.insert(result.end(), buff.begin(), buff.end());
    }
  }

  return result;
}
