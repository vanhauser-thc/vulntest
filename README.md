# Little test programs to test static code analysis software

## Introduction

These small code pieces were used by me to analyse the detective abilities
of a few SCA solutions to identify security vulnerabilities in source code.
This was not a comprehensive test, but rather a quick analysis.

Initially I wanted to create sophisticated bugs and check if they can find
them but found out that even easy test cases can be too hard ;-)

The result of my testing can be read in the german article here:
[https://www.heise.de/hintergrund/Pruefstand-fuer-Testwerkzeuge-Codeanalyse-im-Praxiseinsatz-4679430.html](https://www.heise.de/hintergrund/Pruefstand-fuer-Testwerkzeuge-Codeanalyse-im-Praxiseinsatz-4679430.html)

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

|                    |Perforce|Parasoft |Mathworks|Viva64         |        |llvm          |
|   CODE/SOFTWARE    |Klocwork|C/C++test|Bugfinder|PVS Studio     |cppcheck|clang-analyzer|
|                    |19.01   |10.4.2   |R2019a   |7.01.30939.1042|1.90    |8             |
|:------------------:|:------:|:-------:|:--------|:-------------:|:------:|:------------:|
| andreas            | yes    | no      | no      | no            | no     | no           |
| bof                | yes    | no      | yes     | no            | no     | no           |
| confuse            | no     | no      | no      | no            | no     | no           |
| double_free        | yes    | no      | no      | yes           | no     | yes          |
| encrypt            | yes    | no      | yes     | no            | no     | no           |
| fdleak             | no     | no      | no      | no            | no     | no           |
| hardcoded_password | yes    | no      | no      | no            | no     | no           |
| strcpy             | no     | yes     | no      | no            | no     | no           |
| strcpy2            | no     | no      | no      | no            | no     | no           |
| tricky             |partial | no      | no      | yes           | no     | no           |
| use_after_free     | yes    | yes     | yes     | yes           | yes    | yes          |

For Mathworks Bugfinder, there is also the Code Prover product which checks for
robustness which includes buffer overruns. This would detect most or maybe all
of the buffer overflow bugs but is a seperate product that is not a SCA
comparable to the others.
