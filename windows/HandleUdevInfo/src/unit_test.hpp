#pragma once

#include "gtest/gtest.h"
#pragma comment(lib, "src/library/gtestlib/gtest.lib")
#include "handle_udevice_info.hpp"


void unit_test(int argc, char* argv[])
{
	testing::InitGoogleTest(&argc, argv);
	RUN_ALL_TESTS();
	return;
}