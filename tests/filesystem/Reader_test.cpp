#include <gtest/gtest.h>
#include <string>

#include <filesystem/Reader.hpp>

#include <testutils/TempDir.hpp>
#include <testutils/TempTextFile.hpp>

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