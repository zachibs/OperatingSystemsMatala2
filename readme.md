First, in order to be able to use the tools, we must run 'make all' in the terminal.

Part A:
In this part we created a cmp.c file which compares two text files.
The function will return 1 if the operation was performed successfully and 0 otherwise.
In order to use the file we will run a command according to the following pattern:
./cmp <file1> <file2> -v -i
where -v,-I are optional.
-v : If checked, the output will be either 0 or 1 depending on the input, and will be printed to the user Distinct or Equal respectively.
-I : IGNORE CASES. That means A and a will be recognized as the same letter. (valid only for letters a-z)

Another file we created is copy.c which allows you to copy text files.
The function will return 1 if the operation was performed successfully and 0 otherwise.
./copy <file1> <file2> -v -f

where -v,-f are optional.
-f : If enabled, the file FILE2 will be overwritten if it exists.
-v: Enables printing for the user. If off nothing will be printed, if on then if the operation was successful it will print a message about it, and if it failed it will print the reason, a general error or a file already exists and F is off.


Part B:
In this part we created 2 dynamic libraries, codecA and codecB.
codecA : converts lowercase letters to uppercase and vice versa.
codecB : adds/subtracts 3 to the ASCII value of each character from the input.
Usage:
./encode codecA/B string
./decode codecA/B string


Part C:
A program that creates a shell with modifications we added.
For example, CTRL+C no longer stops but sends a message that the functionality of this signal has been canceled. In order to exit the software, we will have to send the "exit" command.
In addition, there are redirect capabilities with the ">" and ">>" operators, and a pipe capability with "|".