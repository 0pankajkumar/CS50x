# Questions

## What is pneumonoultramicroscopicsilicovolcanoconiosis?

The largest word possible in the dictionary

## According to its man page, what does `getrusage` do?

getrusage() returns resource usage measures

## Per that same man page, how many members are in a variable of type `struct rusage`?

16

## Why do you think we pass `before` and `after` by reference (instead of by value) to `calculate`, even though we're not changing their contents?

To calculate the resources just used before and after you get net resource usage

## Explain as precisely as possible, in a paragraph or more, how `main` goes about reading words from a file. In other words, convince us that you indeed understand how that function's `for` loop works.

It starts reading each character from the file and stores it in an array.
If it exceeds the word limit we just consume the whole next charatcers read.
Similarly digits are also consumed.
Finally function to check spelling is called with resource calcualtion codes.

## Why do you think we used `fgetc` to read each word's characters one at a time rather than use `fscanf` with a format string like `"%s"` to read whole words at a time? Put another way, what problems might arise by relying on `fscanf` alone?

'fscanf' just reads continuosly. We need to read character by character.

## Why do you think we declared the parameters for `check` and `load` as `const` (which means "constant")?

So that it remains unmodified when executing those functions.
