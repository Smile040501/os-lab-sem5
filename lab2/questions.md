# Assignment 2 (deadline: 03-Sep 2021 23:59 hrs)

## Instructions

  1. The instructions on how to submit each answer is indicated below
     the question (in the line starting with "Ans."). Please follow
     those instructions carefully.

  2. Use code-blocks when you are pasting outputs seen on the terminal.


## Questions

1. **[1 mark]** With an example, explain the output of the `diff`  command.

    **Ans.** (Type your answer here. HINT: use 3 files, two of which are the same.
   	 Run the `diff` command with all pairs of (these 3) files.
	 In your own words, explain what you see. )

2. **[1 mark]** Using an example, show how one can measure the time taken to execute a command.

    **Ans.**. (Type your answer here. HINT: DO NOT write a C program that uses gettimeofday().
      	 Instead use the `time` command. Explain the output of the `time` command in detail.)

3. **[1 mark]** What is the difference between a hard-link and a soft-link in Linux Filesystem.
   With an example, show the commands you will use to create such links.

    **Ans.**. (Type your answer here. Use code blocks appropriately)
	 
4. **[1 mark]** How will you create named pipes in UNIX. Show an example usage of such named pipes.

    **Ans.**. (Type your answer here. Use code blocks appropriately)
	
5. Analysis of the `syslog` file.

    a. **[2 marks]** Count the number of error messages in the `syslog` file.

    **Ans.**. (Type your answer here. HINT: Assume there is the word "error" in all of the
      	    error messages. Paste the command(s)/script you used, and its output, as seen
	    in your terminal here. Remember to code blocks here)

    b. **[2 marks]** Count the number of lines in the log file.	    

    **Ans.**. (Type your answer here. Paste the command(s)/script you used, and its output,
      	    as seen in your terminal here. Remember to code blocks here.)

    c. **[2 marks]** Count the number of unique words in the log file.	    

    **Ans.**. (Type your answer here. Paste the command(s)/script you used, and its output,
      	    as seen in your terminal here. Remember to code blocks here.)

    d. **[2 marks]** Find the latest error message

    **Ans.**. (Type your answer here. Paste the command(s)/script you used, and its output,
      	    as seen in your terminal here. Remember to code blocks here.)

    e. **[2 marks]** Find the oldest error message

    **Ans.**. (Type your answer here. Paste the command(s)/script you used, and its output,
      	    as seen in your terminal here. Remember to code blocks here.)
	    
    f. **[2 marks]** Find the average time between the errors

    **Ans.**. (Type your answer here. Paste the command(s)/script you used, and its output,
      	    as seen in your terminal here. Remember to code blocks here.)


6. `echoes` using pipes. You should do all the following
   questions inside the folder `lab2/echoes`

    a. **[2 marks]**  Write a C program (`iecho.c`) that reads an input (using `scanf()`)
      and stores it to a variable named `num`, increments `num` by one, and prints
      the incremented value (using `printf()`). Compile this program to create
      an executable named `iecho`.

    **Ans.**. (Do this in the folder echoes. YOU SHOULD NOT COMMIT THE EXECUTABLE
      	   `iecho` INTO YOUR REPO. DOING SO WILL ATTRACT PENALTY).

    b. **[2 marks]**  Compile `driver.c` into an executable named `driver`. Pipe the output
      of `driver` as the input of `iecho`.

    **Ans.**. (PASTE the command used to achieve this, and the output seen on your
      	   terminal. Enclose the text/command/output that you are copying from
	   the terminal into this file in code blocks).
      
    c. **[8 marks]**  Uncomment the lines 9 and 10 of `driver.c`, and recompile the code
      (executable name can continue to be `driver`). Write a command or shell script
      such that `driver` gets (or reads) the incremented value (which is nothing but
      the output of `iecho`). NOTE: This requires a two-way communication where `driver`
      sends a number to `iecho`, `iecho` increments it and sends the incremented value
      back to `driver`. The `driver` then prints both the original value sent and the
      incremented value it received on `stderr`.

    **Ans.**. (PASTE the command used to achieve this, and the output seen on your
      	   terminal. Enclose the text/command/output that you are copying from
	   the terminal into this file in code blocks).

7. **[12 marks]** The folder `lab2/dedup/inputs` has some files that contain information about the
   marks secured by some students in a few subjects. Since a lot of such files may be
   generated in future, you wish to save disk space. Write a shell script `dedup.sh`
   that takes a directory name as an input argument, finds all regular files immediately
   under this directory that are duplicates, and replaces the duplicates with soft-links.
   NOTE:
	a. The filename of the duplicates should remain same (before and after replacing them
	   with soft links).
	b. Your script should not search for duplicates recursively.
	b. The original files that is the one that is lexicographically first.
	c. If there are more than one duplicate, the duplicates should continue to link
	   to the original (lexicographically first) file only.
	d. If the script is not given any input argument, it is assume the current working
	   directory as its input.
	e. The filenames can contain special characters such as "*", spaces, "~", and
	   leading "-".
	f. Your script should ignore all non-regular files such as links, pipes, directories

    **Ans.**. (Complete this exercise in `dedup.sh` present under `lab2/dedup`)

