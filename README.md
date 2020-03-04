<h1 align="center">
    <br>
    <img src="https://usbac.com.ve/images/Quich_logo.svg" width=100>
    <br>
    Quich
    <br>
</h1>

<h4 align="center">Just an advanced terminal calculator.</h4>

<p align="center">
<img src="https://img.shields.io/badge/version-1.1.1-blue.svg">
<img src="https://img.shields.io/badge/license-MIT-orange.svg">
</p>

Quich is an useful calculator for your terminal with multiple functions and options. Written in ANSI C.

## Options

`-h` `--help` Get help and information

`-p` `--precision` The number of decimals to be used for the numbers

`-r` `--round` The number of decimals to round the result

`-vvv --verbose` Display the result with details

`-v` `--version` Show the application version

## Functions

`sqrt` Square root

`abs`  Absolute value (positive)

`log`  Natural logarithm

`sin`  Sine trigonometric function

`cos`  Cosine trigonometric function

`tan`  Tangent trigonometric function

`floor`  Round down

`ceil`  Round up

## Install

Move to your Quich folder and run the following commands:

`make`

`sudo make install`

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
$ quich 5+3*(-2)
-1
```
```console
$ quich 5+(cos(2)-2)^2
10.8377655357568
```
```console
$ quich 5+(cos(2)-2)^2 -p 2
10.86
```
```console
$ quich 5!+3
123
```

## Contributing

Any contribution or support to this project in the form of a pull request or message will be highly appreciated.

This project is open to changes so don't be shy :)
