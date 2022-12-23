# Running tests
If you want to run all tests, best way is to call 'runTests("dirWithTestFiles");' in main function.
It runs all files in specified directory named Test*, generates TestX.res files and compares them with TestX.out files.

For running one test you can use IO redirection. 
On Windows in PowerShell use 'Get-Content TestX.in | Calculator.exe'.
On UNIX use just Calculator.exe < TestX.in.

# Tests description
Each test has its description at first line.

* Test1 - Basic arithmetics with whole numbers
* Test2 - Basic arithmetics with floating point numbers
* Test3 - Advanced arithmetics with whole numbers
* Test4 - dvanced arithmetics with floating point numbers
* Test5 - Basic parentheses
* Test6 - Nested parentheses
* Test7 - Variable asignment
* Test8 - Variable usage in expression
* Test9 - Invalid inputs