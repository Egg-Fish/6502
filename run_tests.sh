T=$(ls test/*_test/*.bin; echo x)
TESTS="${T%x}"

for item in $TESTS
do
    ./bin/6502.exe $item
done