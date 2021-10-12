#include <fstream>
#include <stdio.h>
#include <stdlib.h>

// iofile
template<typename data_T>
void LoadBinToArray(std::string& file_path, data_T* data_m, uint32_t nums,
                    uint32_t dims, bool non_header = false) {
  std::ifstream file_reader(file_path.c_str(), std::ios::binary);
  if (!non_header) {
    uint32_t nums_r, dims_r;
    file_reader.read((char*) &nums_r, sizeof(uint32_t));
    file_reader.read((char*) &dims_r, sizeof(uint32_t));
    if ((nums != nums_r) || (dims != dims_r)) {
      printf(
          "Error, file size is error, file name: %s, nums_r: %u, dims_r: %u\n",
          file_path.c_str(), nums_r, dims_r);
      exit(1);
    }
  }

  file_reader.read((char*) data_m, nums * dims * sizeof(data_T));
  file_reader.close();
  printf("Load %u * %u data from %s done.\n", nums, dims, file_path.c_str());
}

template<typename data_T>
void WriteBinToArray(std::string& file_path, data_T* data_m, uint32_t nums,
                     uint32_t dims, bool non_header = false) {
  std::ofstream file_writer(file_path.c_str(), std::ios::binary);
  if (!non_header) {
    file_writer.write((char*) &nums, sizeof(uint32_t));
    file_writer.write((char*) &dims, sizeof(uint32_t));
  }

  file_writer.write((char*) data_m, nums * dims * sizeof(data_T));
  file_writer.close();
  printf("Write %u * %u data to %s done.\n", nums, dims, file_path.c_str());
}