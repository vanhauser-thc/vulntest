# Little test programs to test static code analysis software

## Introduction

These small code pieces were used by me to analyse the detective abilities
of a few SCA solutions to identify security vulnerabilities in source code.
This was not a comprehensive test, but rather a quick analysis.

Initially I wanted to create sophisticated bugs and check if they can find
them but found out that even easy test cases can be too hard ;-)

The result of my testing can be read in the german article here:
[https://www.heise.de/hintergrund/Pruefstand-fuer-Testwerkzeuge-Codeanalyse-im-Praxiseinsatz-4679430.html?seite=all](https://www.heise.de/hintergrund/Pruefstand-fuer-Testwerkzeuge-Codeanalyse-im-Praxiseinsatz-4679430.html?seite=all)

## The test source code

Alphabetically:

 - andreas.cpp - hard coded credentials
 - bof.c - buffer overflow based on untrusted length information
 - confuse.cpp - type confusion vulnerability
 - double_free.cpp - copy of a CWE415 NIST test source code
 - encrypt.c - weak encryption mode
 - fdleak.c - leaking a file descriptor to a child process
 - hardcoded_password.c - hard coded credentials
 - ok.c - nothing wrong here, for testing false positives and standard "warnings"
 - ok2.c - nothing wrong here, for testing false positives and standard "warnings"
 - strcpy.c - standard strcpy buffer overflow (and format string vulnerability which was not the test target)
 - strcpy2.c - standard string copy via while-loop (and format string vulnerability which was not the test target)
 - tricky.c - buffer overflow based on untrusted length information
 - use_after_free.c - use after free vulnerability

## Results

All vendors reviewed the setup and verified that the results were real and not
based on a misconfiguration.
And yes, most of them were not happy with the results.

|   CODE/SOFTWARE    |Perforce Klocwork 19.01|Parasoft C/C++test 10.4.2|Mathworks Bugfinder R2019a (2)|Viva 64 PVS Studio|CodeQL Oct 2022|joern Oct 2022|semgrep Oct 2022|cppcheck 2.9|llvm 14 clang-analyzer|ChatGPT 3.5|
|:------------------:|:------:|:-------:|:--------|:-------------:|:------:|:------:|:------:|:------------:|:------------:|:-----:|
| andreas            | yes    | no      | no      | no            | no     | no     | no     | no           | no           | no    |
| bof                | yes    | no      | yes     | no            | yes    | no     | no     | no           | yes(3)       | yes   |
| confuse            | no     | no      | no      | no            | no     | no     | no     | no           | no           | yes   |
| double_free        | yes    | no      | no      | yes           | no     | no     | no     | no           | yes          | yes   |
| encrypt            | yes    | no      | yes     | no            | yes(1) | no     | no     | no           | no           | no    |
| fdleak             | no     | no      | no      | no            | no     | no     | no     | no           | no           | yes   |
| hardcoded_password | yes    | no      | no      | no            | no     | no     | no     | no           | no           | yes   |
| strcpy             | no     | yes     | no      | no            | yes(1) | no     | no     | no           | no           | yes   |
| strcpy2            | no     | no      | no      | no            | no     | no     | no     | no           | no           | yes   |
| tricky             |partial | no      | no      | yes           | no     | no     | no     | no           | no           | yes   |
| use_after_free     | yes    | yes     | yes     | yes           | no     | no     | yes    | yes          | yes          | yes   |

(1) Not in cpp-lgtm.qls but from cpp/ql/src/Security

(2) For Mathworks Bugfinder, there is also the Code Prover product which checks
    for robustness which includes buffer overruns. This might detect the buffer
    overflow bugs but is a seperate product that is not a SCA comparable to the
    others.

(3) with alpha.security checkers enabled
