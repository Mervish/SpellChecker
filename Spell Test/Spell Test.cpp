//#include <string>
//#include <optional>

#include "pch.h"
#include "CppUnitTest.h"



using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace SpellTest
{
	TEST_CLASS(SpellTest)
	{
	public:
		TEST_METHOD(DicTest1)
		{
			std::string base("grep");
			std::string dict("great");

			Assert::IsFalse(StringLibrary::match(base, dict).has_value());
		}

		TEST_METHOD(DicTest2)
		{
			std::string base("get");
			std::string dict("great");

			Assert::IsTrue(StringLibrary::match(base, dict).has_value());
		}

		TEST_METHOD(DicTest3)
		{
			std::string base("e");
			std::string dict("set");

			Assert::IsTrue(StringLibrary::match(base, dict).has_value());
		}

		TEST_METHOD(DicTest4)
		{
			std::string base("hte");
			std::string dict("the");

			Assert::IsTrue(StringLibrary::match(base, dict).has_value());
		}

		TEST_METHOD(DicTest5)
		{
			std::string base("get");
			std::string dict("getup");

			Assert::IsFalse(StringLibrary::match(base, dict).has_value());
		}

		TEST_METHOD(DicTest6)
		{
			std::string base("sctio");
			std::string dict("section");

			Assert::IsTrue(StringLibrary::match(base, dict).has_value());
		}

		TEST_METHOD(DicTest7)
		{
			//surprisingly diffirent case from DicTest4
			std::string base("teh");
			std::string dict("the");

			Assert::IsTrue(StringLibrary::match(base, dict).has_value());
		}


		TEST_METHOD(DicTest8)
		{
			//Checking last symbol handling
			std::string base("aetoqn");
			std::string dict("abetroqs");

			Assert::IsFalse(StringLibrary::match(base, dict).has_value());
		}
			

		TEST_METHOD(DicTest99)
		{
			SpellChecker dictionary;
			std::string base("mainy");
			dictionary.setWords(std::vector<std::string> { "mainly", "main" });

			Assert::IsTrue(dictionary.correct(base) == "{main mainly}");
		}

		TEST_METHOD(FullTest1)
		{
			std::string input = "rain spain plain plaint pain main mainly the in on fall falls his was===hte rame in pain fells mainy oon teh lain was hints pliant===";
			std::string final = "the {rame?} in pain falls {main mainly} on the plain was {hints?} plaint";
			DataHandler handler(move(input));
			if (handler.isInitialised()) {
				Assert::AreEqual(handler.checkSpelling(), final);
			}
			else {
				Assert::Fail(L"Failed to initialise");
			}
		}

		//Case sensitivity compare
		TEST_METHOD(FullTest2)
		{
			std::string input = "Quick brown fox jumps over the long fence===Quic brow fx jmusp oVer teh longf ence ===";
			std::string final = "Quick brown fox {jmusp?} oVer the long fence";
			DataHandler handler(move(input));
			if (handler.isInitialised()) {
				Assert::AreEqual(handler.checkSpelling(), final);
			}
			else {
				Assert::Fail(L"Failed to initialise");
			}
		}
	};
}
