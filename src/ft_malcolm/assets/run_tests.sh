#!/bin/bash

run_test() {
    echo "Running test with args: $@"
    ./ft_malcolm "$@"
    if [ $? -eq 0 ]; then
        echo -e "\033[32mTest passed\033[0m\n"
    else
        echo -e "\033[31mTest failed\033[0m\n"
    fi
}

# Valid IP and MAC
run_test "10.12.255.255" "ff:bb:ff:ff:ee:ff-" "10.12.10.22" "1a:c1:EE:ff:56:7d"  # Should pass

# Invalid IP (incorrect format)
run_test "999.999.999.999" "ff:bb:ff:ff:ee:ff" "10.12.10.22" "1a:c1:EE:ff:56:7d"  # Should fail

# Invalid IP (nonexistent IP)
run_test "256.256.256.256" "ff:bb:ff:ff:ee:ff" "10.12.10.22" "1a:c1:EE:ff:56:7d"  # Should fail

# Valid IP (in range 0-255)
run_test "0.0.0.0" "ff:bb:ff:ff:ee:ff" "10.12.10.22" "1a:c1:EE:ff:56:7d"  # Should pass

# Valid IP (boundary case)
run_test "255.255.255.255" "ff:bb:ff:ff:ee:ff" "10.12.10.22" "1a:c1:EE:ff:56:7d"  # Should pass

# Valid MAC, all uppercase letters
run_test "10.12.255.255" "FF:BB:FF:FF:EE:FF" "10.12.10.22" "1A:C1:EE:FF:56:7D"  # Should pass

# Valid MAC, all lowercase letters
run_test "10.12.255.255" "ff:bb:ff:ff:ee:ff" "10.12.10.22" "1a:c1:ee:ff:56:7d"  # Should pass

# Invalid MAC (more than 6 octets)
run_test "10.12.255.255" "ff:bb:ff:ff:ee:ff:gg" "10.12.10.22" "1a:c1:EE:ff:56:7d"  # Should fail

# Invalid MAC (incorrect number of octets)
run_test "10.12.255.255" "ff:bb:ff:ff:ee" "10.12.10.22" "1a:c1:EE:ff:56:7d"  # Should fail

# Invalid MAC (invalid characters in octets)
run_test "10.12.255.255" "ff:bb:ff:zz:ee:ff" "10.12.10.22" "1a:c1:EE:ff:56:7d"  # Should fail

# Invalid MAC (spaces between characters)
run_test "10.12.255.255" "ff bb ff ff ee ff" "10.12.10.22" "1a:c1:EE:ff:56:7d"  # Should fail

# Invalid MAC (random characters)
run_test "10.12.255.255" "zz:zz:zz:zz:zz:zz" "10.12.10.22" "1a:c1:EE:ff:56:7d"  # Should fail

# Valid IP, but in IPv6 format
run_test "2001:0db8:85a3:0000:0000:8a2e:0370:7334" "ff:bb:ff:ff:ee:ff" "10.12.10.22" "1a:c1:EE:ff:56:7d"  # Should fail, it's IPv6

# IP with leading zeros
run_test "010.012.255.255" "ff:bb:ff:ff:ee:ff" "10.12.10.22" "1a:c1:EE:ff:56:7d"  # Should pass

# MAC with leading zeros
run_test "10.12.255.255" "0a:bb:ff:ff:ee:ff" "10.12.10.22" "1a:c1:EE:ff:56:7d"  # Should pass

# Invalid IP format (slashes instead of dots)
run_test "10/12/255/255" "ff:bb:ff:ff:ee:ff" "10.12.10.22" "1a:c1:EE:ff:56:7d"  # Should fail

# Invalid MAC with invalid characters (greater than A-F)
run_test "10.12.255.255" "ff:bb:ff:ff:gg:ff" "10.12.10.22" "1a:c1:EE:ff:56:7d"  # Should fail

# Valid IP (empty string)
run_test "" "ff:bb:ff:ff:ee:ff" "10.12.10.22" "1a:c1:EE:ff:56:7d"  # Should fail

# Valid MAC (empty string)
run_test "10.12.255.255" "" "10.12.10.22" "1a:c1:EE:ff:56:7d"  # Should fail

# Invalid IP format (missing dots)
run_test "10-12-255-255" "ff:bb:ff:ff:ee:ff" "10.12.10.22" "1a:c1:EE:ff:56:7d"  # Should fail

# IP with spaces between numbers
run_test "10 .12 .255 .255" "ff:bb:ff:ff:ee:ff" "10.12.10.22" "1a:c1:EE:ff:56:7d"  # Should fail

# MAC with spaces between characters
run_test "10.12.255.255" "ff bb ff ff ee ff" "10.12.10.22" "1a:c1:EE:ff:56:7d"  # Should fail
