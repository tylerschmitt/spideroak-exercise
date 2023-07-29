# Technical Assessment Systems Level Developer

The following test can be implemented in any programming language. You will have 5 business days to complete, but it's not expected that you spend more than 3 hours on it.

The assessment involves writing 2 basic programs using a shared library and a symmetrical key.  Both programs will implement a command-line-interface (CLI).  Program 1 will take a message and the key (or passphrase) as input, using the key it will encrypt the message and output a success message.  Program 2 will take key as input and output the decrypted message on success and error message on fail (i.e. wrong key).  The cryptography logic will be contained in the shared library to be used by both programs.  SpiderOak encourages creativity in solving problems.  Therefore, it is up to the candidate on how the ciphertext is delivered to Program 2.  Code should be pushed to a public git repo (GitHub, GitLab, BitBucket, etc) early in the development so SpiderOak engineers can review commits.

The command line clients should provide the following:

```
$ <program1name> -k <key> -m <message>  # Initiate encryption for program 1
$ <program2name> -k <key>               # Decrypt the message and output the plaintext
```

Notes: 
- You can use external packages/libraries.
- Cryptography algorithms to be used are at the candidate's discretion.
- Bonus for programs written in C/C++ or Go.
- Bonus for implementing CMAKE.
- Bonus for creating stories with weights during development.