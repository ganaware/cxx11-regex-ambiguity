// -*- mode: c++; tab-width: 4; -*-
#ifdef USE_BOOST
#	include <boost/regex.hpp>
namespace rns = boost;
#else
#	include <regex>
namespace rns = std;
#endif
#include <iostream>

void answer(const std::string &result,
			const std::string &expected_true,
			const std::string &expected_false) {
	if (result == expected_true) {
		std::cout << "true" << std::endl;
	} else if (result == expected_false) {
		std::cout << "false" << std::endl;
	} else {
		std::cout << "unexpected result:" << std::endl << result << std::endl;
	}
}

int main() {
	// http://stackoverflow.com/questions/11959918/matching-beginning-of-line-using-libc-regex-library-c11/11962425
	{
		std::cout << "(1) Does '^' match newlines ?" << std::endl;
		rns::regex rx("^.");
		std::string s = "1234\n5678";
		answer(rns::regex_replace(s, rx, "X"),
			   "X234\nX678", "X234\n5678");
	}
	{
		std::cout << "(2) Does '$' match newlines ?" << std::endl;
		rns::regex rx(".$");
		std::string s = "1234\n5678";
		answer(rns::regex_replace(s, rx, "X"),
			   "123X\n567X", "1234\n567X");
	}
	{
		std::cout << "(3) Does '.' match newlines ?" << std::endl;
		rns::regex rx(".");
		std::string s = "1234\n5678";
		answer(rns::regex_replace(s, rx, "X"),
			   "XXXXXXXXX", "XXXX\nXXXX");
	}
	// http://stackoverflow.com/questions/17609325/on-libc-why-does-regex-matchtournament-regextourtotournament-fail
	{
		std::cout << "(4) Does a regex_match works as if the pattern was followed by \\z of Perl ?" << std::endl;
		rns::cmatch m;
		const char s[] = "tournament";
		if (rns::regex_match(s, m, rns::regex("tour|to|tournament"))) {
			std::cout << "true" << std::endl;
		} else {
			std::cout << "false" << std::endl;
		}
	}
	return 0;
}

// libstdc++ r203261
//
//		$ <path-to-4.8.1>/g++ -std=c++11 -static test.cpp && ./a.out
//		(1) Does '^' match newlines ?
//		false
//		(2) Does '$' match newlines ?
//		false
//		(3) Does '.' match newlines ?
//		false
//		(4) Does a regex_match works as if the pattern was followed by \z of Perl ?
//		true

// libc++ r192176
//
//		$ export DYLD_LIBRARY_PATH=<path-to-libcxx>/lib
//		$ clang++ -std=c++11 -stdlib=libc++ -nostdinc++ -I<path-to-libcxx>/include -L<path-to-libcxx>/lib test.cpp && ./a.out
//		(1) Does '^' match newlines ?
//		false
//		(2) Does '$' match newlines ?
//		false
//		(3) Does '.' match newlines ?
//		false
//		(4) Does a regex_match works as if the pattern was followed by \z of Perl ?
//		false

// boost 1.53
//
//		$ g++ -DUSE_BOOST test.cpp -llibboost_regex-mt && ./a.exe
//		(1) Does '^' match newlines ?
//		true
//		(2) Does '$' match newlines ?
//		true
//		(3) Does '.' match newlines ?
//		true
//		(4) Does a regex_match works as if the pattern was followed by \z of Perl ?
//		true

// Visual Studio Express 2013 RC
//
//		(1) Does '^' match newlines ?
//		true
//		(2) Does '$' match newlines ?
//		true
//		(3) Does '.' match newlines ?
//		false
//		(4) Does a regex_match works as if the pattern was followed by \z of Perl ?
//		true
