# Some C testing program

Creditcard problem

## Compile

Compile the program by running
```bash
make
```

## Test files

test_length.txt
 - 7 INVALID

test_syntax.txt
 - 1 VALID
   - 1 Visa

test_paypal.txt
 - 16 VALID
   - 3 Visa
   - 5 Mastercard
   - 3 American Express
   - 5 unknown

Execute the testfiles with
```bash
cat test*.txt | while read input; do echo $input | ./program; done
cat test*.txt | while read input; do echo $input | ./program; done | grep 'INVALID' | wc -l
```
