<h1 align="center">
    <br>
    <img src="https://usbac.com.ve/images/Quich_logo.svg" width=100>
    <br>
    Quich
    <br>
</h1>

<h4 align="center">Just an advanced terminal calculator.</h4>

<p align="center">
<img src="https://img.shields.io/badge/stability-stable-green.svg">
<img src="https://img.shields.io/badge/version-2.2-blue.svg">
<img src="https://img.shields.io/badge/license-MIT-orange.svg">
</p>

Quich is a small, fast and useful calculator for your terminal with multiple functions and options. Written in ANSI C.

You can enter in `interactive mode` calling Quich without an operation.

## Options

`-d` `--degree` Manage the given angles in degrees

`-h` `--help` Get help and information

`-i` `--interactive` Force interactive mode

`-p` `--precision` The number of decimals to be used for the internal numbers

`-r` `--round` The number of decimals to round the result

`-vvv` `--verbose` Display the result with details

`-v` `--version` Show the application version

## Functions

Syntax: `func_name(operand)`

* `sqrt` Square root

* `abs` Absolute value (positive)

* `log` Natural logarithm

* `sin`, `cos`, `tan` Sine, Cosine and Tangent trigonometric functions

* `asin`, `acos`, `atan` Arc sine, Arc cosine and Arc tangent trigonometric functions

* `round` Round to the nearest integer value

* `floor` Round down

* `ceil` Round up

The constants `PI` and `E` are also available.

## Install

Move to your Quich folder and run the following command:

`make; sudo make install`

Now you should be able to access to Quich running `quich` in your terminal.

### Naming

You can specify the Quich name when installing it with the `NAME` makefile variable:

`sudo make install NAME=calc`

Now you will be able to access Quich with the `calc` command.

## Examples

```console
$ quich 5+3
8
```
```console
$ quich "5+3*(-2)"
-1
```
```console
$ quich "5+(cos(2)-2)^2"
10.8377655357568
```
```console
$ quich "5+(cos(2)-2)^2" -p 2
10.86
```
```console
$ quich 5+PI -vvv
Tokens > '5' '+' '3.14159265358979'
Posfix > 5 3.14159265358979 +
Result > 8.14159265358979
```

## Contributing

Any contribution or support to this project in the form of a pull request or message will be highly appreciated.

This project is open to changes so don't be shy :)
