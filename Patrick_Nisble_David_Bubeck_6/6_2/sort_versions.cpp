
#include <vector>
#include <string>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <iostream>

#include "sort_versions.hpp"

// shorthand
typedef std::vector<int> vNum;

/// splits a given version string at "."
/// \param version to be split
/// \return orderd in subversion
vNum split_version(std::string version);

/// comparison between two version strings
/// \param v1
/// \param v2
/// \return
bool version_less(std::string v1, std::string v2);

int main() {
    std::sort(versions.begin(), versions.end(), version_less);

    std::cout << "{ ";
    for (auto elem: versions) {
        std::cout << elem << " ";
    }
    std::cout << "}";
}

vNum split_version(std::string version) {
    vNum vList;

    bool terminate = false;
    do {
        auto pos = version.find(".");

        if (pos == std::string::npos) {
            pos = version.length();
            terminate = true;
        }

        vList.push_back(std::stoi(version));

        version = std::string(version.begin() + pos + !terminate, version.end());

    } while (!terminate);

    return vList;
}

bool version_less(std::string v1, std::string v2){
    vNum vList1 = split_version(v1);
    vNum vList2 = split_version(v2);

    unsigned long maxSubVer = std::max(vList1.size(), vList2.size());
    vList1.resize(maxSubVer, 0);
    vList2.resize(maxSubVer, 0);

    for (int i = 0; i < maxSubVer; i++) {
        if (vList1[i] < vList2[i]) {
            return true;
        } else if (vList1[i] > vList2[i]) {
            return false;
        }
    }

    return false;
}
