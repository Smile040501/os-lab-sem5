# Assignment 2 (deadline: 03-Sep 2021 23:59 hrs)

## Instructions

1. The instructions on how to submit each answer is indicated below
   the question (in the line starting with "Ans."). Please follow
   those instructions carefully.

2. Use code-blocks when you are pasting outputs seen on the terminal.

## Questions

1. **[1 mark]** With an example, explain the output of the `diff` command.

    **Ans.**

    ```sh
    $ cat 1.txt
    abc
    def
    ghi
    jkl

    $ cat 2.txt
    abc
    def
    ghi
    jkl

    $ cat 3.txt
    ghi
    jkl
    def
    abc

    $ diff 1.txt 2.txt

    $ diff 2.txt 3.txt
    1,2d0
    < abc
    < def
    4c2,4
    < jkl
    \ No newline at end of file
    ---
    > jkl
    > def
    > abc
    \ No newline at end of file

    $ diff 1.txt 3.txt
    1,2d0
    < abc
    < def
    4c2,4
    < jkl
    \ No newline at end of file
    ---
    > jkl
    > def
    > abc
    \ No newline at end of file
    ```

    Since 1.txt and 2.txt have no change, we get nothings on running `diff` command.

    Running `diff` command with 1.txt and 3.txt or 2.txt and 3.txt gives same output.\
    **1,2d0** means lines 1 to 2 in first file are deleted to get the line 0 of second file.\
    **<** are lines from first file.\
    **>** are lines from second file.\
    **---** separate lines from both files.\
    **4c2,4** means lines 4 needs to be changed in first file to match lines 2 to 4 in second file.

2. **[1 mark]** Using an example, show how one can measure the time taken to execute a command.

    **Ans.**. We can measure the time taken to execute a command using the `time` command.\
     Ex. If we want to measure the time of compiling a C program, we can use the time command as follows:

    ```sh
    $ time gcc hello.c -o hello
    ```

    We will just write `time` in front of the command we want to measure the time.
    The output of running above example will be as follows:

    ```sh
    real    0m0.004s
    user    0m0.001s
    sys     0m0.004s
    ```

    **real** is what tells the total time taken by the command from start to finish of the command.\
    **user** is time taken by CPU in user-mode.\
    **sys** is time taken by CPU in kernel.

3. **[1 mark]** What is the difference between a hard-link and a soft-link in Linux Filesystem.
   With an example, show the commands you will use to create such links.

    **Ans.**.

    - Soft links are pointers to file and they are not updated when we move or delete our file. They contain the paths to the original file
    - Hard links are pointers to file and they always refer to the source. Even if we move/delete/rename that file, hard link will still point to that same file
    - So if we create a soft link and hard link to a file and then delete that file, we can still access that file using hard link, but we can't access it through soft link and soft link becomes dangling
    - Hard link increases references count of a location while soft links work a shortcut to file

    To create a hard link:

    ```sh
    $ ln original.txt hard.txt
    ```

    To create a soft link:

    ```sh
    $ ln -s original.txt soft.txt
    ```

4. **[1 mark]** How will you create named pipes in UNIX. Show an example usage of such named pipes.

    **Ans.**. To create a named pipe in UNIX, we can use the `mkfifo` command. It will basically create a named piped file of whatever name we give to it. Then when we write to this file, the terminal will keep running there and wait until the data is read from the piped file.\
    Ex:\
    **NOTE**: Lines after # are treated as comments for explanation purposes

    ```sh
    $ mkfifo cat_cut        # creating a named pipe file with name "cat_cut"
    $ cat file1.txt file2.txt > cat_cut     # Writing to this pipe
                                            # This command will keep running till we read from it
    ```

    On separate terminal:

    ```sh
    $ cut -d',' < cat_cut     # input is coming this named pipe for `cut` command
    ```

5. Analysis of the `syslog` file.

    a. **[2 marks]** Count the number of error messages in the `syslog` file.

    **Ans.**. 96

    Command I used:

    ```sh
    $ grep "error" /var/log/syslog | wc -l
    ```

    Output:

    ```sh
    96
    ```

    b. **[2 marks]** Count the number of lines in the log file.

    **Ans.**. 10357

    Command:

    ```sh
    $ wc -l /var/log/syslog
    ```

    Output:

    ```sh
    10357 /var/log/syslog
    ```

    c. **[2 marks]** Count the number of unique words in the log file.

    **Ans.**. 9567

    Command:

    ```sh
    $ grep -o -E "\w+" /var/log/syslog | sort | uniq | wc -w

    # -E flag for using regex and for words I am using "\w+" as standard regex\
    # -o flag to print matched pattern in new line, this way all the words are printed in new line
    ```

    Output:

    ```sh
    9567
    ```

    d. **[2 marks]** Find the latest error message

    **Ans.**.
    Command:

    ```sh
    $ grep "error" /var/log/syslog | tail -1

    # as syslog file is already sorted by time
    ```

    Output (Answer):

    ```sh
    Sep  3 17:15:46 mayank-LAPTOP-MOD3F6SK discord.desktop[3881]: rtc_log_set_paused error: monitor_option.is_none()
    ```

    e. **[2 marks]** Find the oldest error message

    **Ans.**.
    Command:

    ```sh
    $ grep "error" /var/log/syslog | head -1

    # as syslog file is already sorted by time
    ```

    Output (Answer):

    ```sh
    Sep  3 00:50:42 mayank-LAPTOP-MOD3F6SK gnome-shell[44965]: Fontconfig error: Cannot load default config file: No such file: (null)
    ```

    f. **[2 marks]** Find the average time between the errors

    **Ans.**. 597 seconds
    Script:

    ```sh
    count="0"   # number of pairs of differences of time
    prev="0"    # prev time in seconds
    sum="0"     # sum of differences of times in seconds

    for line in $(grep "error" /var/log/syslog | grep -o -G "[0-9][0-9]:[0-9][0-9]:[0-9][0-9]")
    do
        if [ ${line:0:1} -ne 0 ]; then  # so that string starting with "0" don't consider to be octal
            let first=${line:0:2}
        else
            let first=${line:1:1}
        fi

        if [ ${line:3:1} -ne 0 ]; then  # so that string starting with "0" don't consider to be octal
            let second=${line:3:2}
        else
            let second=${line:4:1}
        fi

        if [ ${line:6:1} -ne 0 ]; then  # so that string starting with "0" don't consider to be octal
            let third=${line:6:2}
        else
            let third=${line:7:1}
        fi

        if [ $count -eq 0 ]; then   # for the first time
            let prev=$first*60*60+$second*60+$third
        else
            let curr=$first*60*60+$second*60+$third     # current time
            let diff=$curr-$prev    # difference b/w current time and previous time in seconds
            let sum=$sum+$diff      # sum of differences
            let prev=$curr          # updating the previous
        fi

        let count=$count+1      # incrementing count
    done

    let count=$count-1      # number of pairs in one less
    let avg=$sum/$count     # the expected answer
    echo $avg
    ```

    Output:

    ```sh
    597   # in seconds
    ```

6. `echoes` using pipes. You should do all the following
   questions inside the folder `lab2/echoes`

    a. **[2 marks]** Write a C program (`iecho.c`) that reads an input (using `scanf()`)
    and stores it to a variable named `num`, increments `num` by one, and prints
    the incremented value (using `printf()`). Compile this program to create
    an executable named `iecho`.

    **Ans.**. (Do this in the folder echoes. YOU SHOULD NOT COMMIT THE EXECUTABLE
    `iecho` INTO YOUR REPO. DOING SO WILL ATTRACT PENALTY).

    b. **[2 marks]** Compile `driver.c` into an executable named `driver`. Pipe the output
    of `driver` as the input of `iecho`.

    **Ans.**.
    Command:

    ```sh
    $ ./driver | ./iecho
    ```

    Output:

    ```sh
    1
    ```

    c. **[8 marks]** Uncomment the lines 9 and 10 of `driver.c`, and recompile the code
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
   e. The filenames can contain special characters such as "\*", spaces, "~", and
   leading "-".
   f. Your script should ignore all non-regular files such as links, pipes, directories

    **Ans.**. (Complete this exercise in `dedup.sh` present under `lab2/dedup`)
