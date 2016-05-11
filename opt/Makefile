CXX_X86=g++
CXX_ARM=gcc-linaro-4.9-2014.11-x86_64_arm-linux-gnueabihf/bin/arm-linux-gnueabihf-g++
EIGEN_SOURCE=eigen3

test_eigen: test_eigen.cpp
	$(CXX_X86) test_eigen.cpp -o test_eigen_x86 -O3 -I$(EIGEN_SOURCE)
	$(CXX_ARM) test_eigen.cpp -o test_eigen_arm -static -O3 -mfpu=neon -mcpu=cortex-a9 -mfloat-abi=hard -I$(EIGEN_SOURCE)
