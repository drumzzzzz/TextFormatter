CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Usage
 * Maintainers


INTRODUCTION
------------

Adapter design pattern project for UWGB Computer Science Fall semester, 2020.
Reads a list of text strings from an input file, performs the selected formatting operations 
and saves the results to an output file.

USAGE example
------------
    TextFormatter "text file in" "text file out" <operation> <operation> ...
	Example: inputfile.txt outputfile.txt lc cw al


    Example operation results from the source message: "Hello world! This is my message."

    Operation   Description             Result
    uc          Upper Case              "HELLO WORLD! THIS IS MY MESSAGE."
    lc          Lower Case              "hello world! this is my message."
    rp          Removes Punctuation     "hello world  this is my message " 
    cw          Capitalize Words        "Hello World! This Is My Message."
    dw          Decapitalize Words      "hELLO wORLD! tHIS iS mY mESSAGE.""

The operation strings are case insensitive.

MAINTAINERS
-----------

 * Nathaniel Kennis - https://github.com/drumzzzzz

