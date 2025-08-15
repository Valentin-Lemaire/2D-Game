#include "file_extraction.h"
#include <fstream>
#include <iostream>

std::vector<std::vector<int>> file_to_matrix(const std::string& filename) {
    std::vector<std::vector<int>> matrix;
    std::ifstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return matrix;
    }
    
    std::string line;
    while (std::getline(file, line)) {
        std::vector<int> row;
        for (char c : line) {
            if (c == '0' || c == '1') {
                row.push_back(c - '0');
            }
        }
        if (!row.empty()) {
            matrix.push_back(row);
        }
    }
    
    file.close();
    return matrix;
} 