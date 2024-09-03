#include <gtest/gtest.h>
#include <string>

#include <filesystem/Reader.hpp>

#include <testutils/TempDir.hpp>
#include <testutils/TempTextFile.hpp>
#include <structures/FloatArray.hpp>

TEST(ReadStringTest, ReadsFileCorrectly) {
	// Create a temporary directory
	TempDir tempDir;

	// Create file for testing
	const char* fileContent = "abc";
	TempTextFile tempTextFile(tempDir, fileContent);

	// Read the temporary file
	std::string result;
	ASSERT_NO_THROW(result = filesystem::ReadTextFile(tempTextFile.GetPath()));
	// Make sure the file contents are read correctly
	EXPECT_EQ(result, fileContent);
}

TEST(ReadStringTest, ThrowsExceptionOnNonExistentFile) {
	// Create a temporary directory
	TempDir tempDir;

	// Path to non-existent file
	std::ostringstream oss;
	oss << tempDir.GetPath() << "non_existent.txt";

	// Try reading the file(should throw an exception)
	std::string result;
	ASSERT_THROW(result = filesystem::ReadTextFile(oss.str()), std::runtime_error);
}

TEST(ReadFloatArrayTest, ReadsObjectCorrectly) {
	// Create a temporary directory
	TempDir tempDir;

	// Create object file that contains 3 coordinates
	const char* fileContent1 = "3\n0.4 -0.3 1.0\n\0";
	TempTextFile obj1(tempDir, fileContent1);

	// Create object file that contains 5 coordinates on separate lines
	const char* fileContent2 = "5\n0.1 -0.2 0.5\n-1.0 0.7\n\0";
	TempTextFile obj2(tempDir, fileContent2);

	// Object 1
	FloatArray* result;
	ASSERT_NO_THROW(result = filesystem::ReadFloatArray(obj1.GetPath()));
	EXPECT_EQ(result->Length(), 3);

	// Check every float value
	const float* array1 = result->Ptr();
	EXPECT_EQ(array1[0], 0.4f);
	EXPECT_EQ(array1[1], -0.3f);
	EXPECT_EQ(array1[2], 1.0f);

	delete result;

	// Object 2
	ASSERT_NO_THROW(result = filesystem::ReadFloatArray(obj2.GetPath()));
	EXPECT_EQ(result->Length(), 5);

	// Check every float value
	const float* array2 = result->Ptr();
	EXPECT_EQ(array2[0], 0.1f);
	EXPECT_EQ(array2[1], -0.2f);
	EXPECT_EQ(array2[2], 0.5f);
	EXPECT_EQ(array2[3], -1.0f);
	EXPECT_EQ(array2[4], 0.7f);

	delete result;
}
