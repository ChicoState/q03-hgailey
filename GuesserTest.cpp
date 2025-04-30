/**
 * Unit Tests for the class
**/

#include <gtest/gtest.h>
#include "Guesser.h"

class GuesserTest : public ::testing::Test
{
	protected:
		GuesserTest(){} //constructor runs before each test
		virtual ~GuesserTest(){} //destructor cleans up after tests
		virtual void SetUp(){} //sets up before each test (after constructor)
		virtual void TearDown(){} //clean up after each test, (before destructor)
};


/* FAILS: 
   Password of length < 3 -> remaining decremented when the password should be locked
                          -> password not locked when distance should be calculated as > 2
   Reseting remaining guesses to 3 after correct guess is not implemented
*/

// Example "smoke test" (can be deleted)
// PASS
TEST(GuesserTest, smoke_test)
{
  Guesser object("Secret");
  ASSERT_EQ( 1+1, 2 );
}

// Test to reassure that the class correctly matches a password on the first try
// PASS
TEST(GuesserTest, match_test)
{
  Guesser object("Secret");
  bool match = object.match("Secret");
  ASSERT_EQ(true, match);
}

// Test for if remaining decrements as expected after two incorrect guesses
// PASS
TEST(GuesserTest, remaining_test)
{
  Guesser object("Secret");
  object.match("Secre");
  object.match("Seeret");
  unsigned int remaining = object.remaining();
  ASSERT_EQ(1, remaining);
}

// Test for if password matches correctly after one incorrect guess
// PASS
TEST(GuesserTest, match_after_one_check)
{
  Guesser object("Secret");
  object.match("Secre");
  bool match = object.match("Secret");
  ASSERT_EQ(true, match);
}

// Test for if guess still matches after two incorrect tries
// PASS
TEST(GuesserTest, reset_test)
{
  Guesser object("Secret");
  object.match("Secre");
  object.match("Secret");
  bool match = object.match("Secret");
  ASSERT_EQ(true, match);
}

// Test for if remaining resets as expected after one wrong guess and one correct guess
// FAIL
TEST(GuesserTest, match_after_two_test)
{
  Guesser object("Secret");
  object.match("Secre");
  object.match("Secret");
  unsigned int remaining = object.remaining();
  ASSERT_EQ(3, remaining);
}

// Test for if brute force detection works as expected
// PASS
TEST(GuesserTest, brute_force_detection_test)
{
  Guesser object("Secret");
  object.match("Secretttt");
  bool match = object.match("Secret");
  ASSERT_EQ(false, match);
}

// Test for if character limitation works as expected for > 32
// PASS
TEST(GuesserTest, limit_length_test)
{
  Guesser object("012345678901234567890123456789012");
  bool match = object.match("01234567890123456789012345678901");
  ASSERT_EQ(true, match);
}

// Test for if three wrong guess locks the password
// PASS
TEST(GuesserTest, lock_after_three_test)
{
	Guesser object("Secret");
	object.match("Secrettt");
	object.match("Secre");
	object.match("Secreth");
	bool match = object.match("Secret");
  ASSERT_EQ(false, match);
}

// Test for if remaining never goes below zero
// PASS
TEST(GuesserTest, remaining_lower_bound_test)
{
	Guesser object("Secret");
	object.match("Secrettt");
	object.match("Secre");
	object.match("Secreth");
	object.match("Secrets");
	unsigned int remaining = object.remaining();
  ASSERT_EQ(0, remaining);
}

// Test for if remaining starts at 3
// PASS
TEST(GuesserTest, remaining_initial_value_test)
{
	Guesser object("Secret");
	unsigned int remaining = object.remaining();
  ASSERT_EQ(3, remaining);
}

// Test for matching an empty password
// PASS
TEST(GuesserTest, empty_password_match_test)
{
	Guesser object("");
	bool match = object.match("");
  ASSERT_EQ(true, match);
}

// Test for unsigned int / int issue when guess is shorter than password on matching
// PASS
TEST(GuesserTest, negative_difference_match_test)
{
	Guesser object("012345678901234567890123456789012");
	bool match = object.match("a");
  ASSERT_EQ(false, match);
}

// Test for unsigned int / int issue when guess is shorter than password on matching
// PASS
TEST(GuesserTest, negative_difference_remaining_test)
{
	Guesser object("012345678901234567890123456789012");
	object.match("a");
	int remaining = object.remaining();
  ASSERT_EQ(3, remaining);
}

// Test for unsigned int / int issue when guess is shorter than password lock
// PASS
TEST(GuesserTest, check_locked_after_long_test)
{
	Guesser object("012345678901234567890123456789012");
	object.match("a");
	bool match = object.match("01234567890123456789012345678901");
  ASSERT_EQ(false, match);
}

// Test for proper failing on original password after it should have been shortend
// PASS
TEST(GuesserTest, check_shortened_test)
{
	Guesser object("012345678901234567890123456789012");
	bool match = object.match("012345678901234567890123456789012");
  ASSERT_EQ(false, match);
}

// Test for if distance greater than two is properly detected on password on length 2
// FAIL
TEST(GuesserTest, check_lock_on_length2_test)
{
	Guesser object("01");
	object.match("012345678901234567890123456789012");
	bool match = object.match("01");
  ASSERT_EQ(false, match);
}

// Test for if remaining is not decremented when the password should just be locked due to long guess
// FAIL
TEST(GuesserTest, check_remaining_on_lock_test)
{
	Guesser object("01");
	object.match("012345678901234567890123456789012");
	int remaining = object.remaining();
  ASSERT_EQ(3, remaining);
}

// Test for if password is ever locked on an empty password when entering a long guess
// PASS
TEST(GuesserTest, check_lock_on_empty_test)
{
	Guesser object("");
	object.match("012345678901234567890123456789012");
	object.match("012345678901234567890123456789012");
	object.match("012345678901234567890123456789012");
	bool match = object.match("");
  ASSERT_EQ(false, match);
}


