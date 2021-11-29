mkfifo tuberia3
ls -l
echo 12345 > tuberia3

#En otra ventana de terminal
cat tuberia3
