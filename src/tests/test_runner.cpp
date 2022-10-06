#include "gtest/gtest.h"

int main(int argc, char **argv) {

    testing::InitGoogleTest(&argc, argv);
    if (RUN_ALL_TESTS()) {
        std::cout << "Some tests have failed :(\n"
                  << "Get back to work!"
                  << "\n";
    }

    return 0;
}
