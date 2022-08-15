# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

The longest word in the English language published in a dictionary. It's a synonym for the disease called silicosis.

## According to its man page, what does `getrusage` do?

Return resource usage measures for _who_, which can be of the following: RUSAGE_SELF, RUSAGE_CHILDREN, RUSAGE_THREAD. 

## Per that same man page, how many members are in a variable of type `struct rusage`?

There are 16 members in struct rusage.

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

This way there is no need to create new variables and calculate always has access to the latest before and after data. 

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

The function for reading the words start with a loop that itterates over every character in the provided file (fp) until the end of the file (EOF) is reached.
When a character is read it is put through a series of loops to ensure the following:
1. Check if the character is alphabetical or an apostrophe. If so add the character to the word. After that check if the word might be too long according to the LENGTH definition (provided in dictionary.h), if so ignore the word. 
2. If the character contains digits, ignore the word.
3. If no apostrophes, alphabetical or numerical characters are found, complete the word by adding the null terminator to the word array. If a complete word is found, it will be checked if it's misspelled and this misspelling part is timed by rusage.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

fgetc provides more control than fscanf. You could potentially pollute your input with periods and commas when using fscanf if the input isn't formatted properly, 
because fscanf will read subsequent characters until a whitespace is found (whitespace characters are considered to be blank, newline and tab).
With fgetc you could filter that out more easily by itterating over every character.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

By declaring them constant they become mutable pointers to an immutable character/string, so the contents of the location(s) this pointer points to cannot be changed. 
It's a safer construction for these values, because the system will not allow changes to the values and warn you if you try to do so.