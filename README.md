<h1 align="center">
    <br>
    <img src="http://image.usbac.com.ve/Quich.svg" width=120>
    <br>
    Quich
    <br>
</h1>

<h4 align="center">Just an advanced terminal calculator.</h4>

<p align="center">
    <img src="https://travis-ci.org/Usbac/quich.svg?branch=master">
    <img src="https://img.shields.io/badge/stable-3.2.1-blue.svg">
    <img src="https://img.shields.io/badge/license-MIT-orange.svg">
</p>

Quich is a compact, fast, powerful and useful calculator for your terminal with numerous features, supporting Linux, Mac and Windows, written in [ANSI C](https://en.wikipedia.org/wiki/ANSI_C).

You can enter in `interactive mode` by calling Quich in your terminal without an operation.

## Usage

### Options

`-d` `--degree` Manage the given angles in degrees

`-f` `--format` `[%s]` The format to display the result

`-h` `--help` Get help and information

`-i` `--interactive` Force interactive mode

`-p` `--precision` `[%i]` The number of decimals to be used for the internal numbers

`-r` `--round` `[%i]` The number of decimals to round the result

`-t` `--thousands` Display the result with thousands separators

`-vvv` `--verbose` Display the result with details

`-v` `--version` Show the application version

### Functions

Syntax: `func(operand)`

* `sqrt` Square root

* `abs` Absolute value (positive)

* `log` Natural logarithm

* `sin`, `cos`, `tan` Sine, Cosine and Tangent trigonometric functions

* `asin`, `acos`, `atan` Arc sine, Arc cosine and Arc tangent trigonometric functions

* `rand` Random number between 0 and 1

* `round` Round to the nearest integer value

* `floor` Round down

* `ceil` Round up

### Variables

For defining a variable just write an equal operator between its name and its value. Like this: `a=4+20`.

### Available

Values `PI`, `E`, `GR` (Golden Ratio) and `G` (earth gravity).

The units of measurement for data storage `mb`, `gb`, `tb` and `pt` (they return the result in kb).

## Install

<a href="https://repology.org/project/quich/versions"><img src="https://repology.org/badge/vertical-allrepos/quich.svg" alt="Packaging status"></a>

You can download the bundles here.

[Linux - v3.2.1](https://github.com/Usbac/quich/releases/download/v3.2.1/quich-linux)

Or move to your Quich folder and run the following command:

`make && sudo make install`

Now you should be able to access Quich by running `quich` in your terminal.

### Naming

You can specify the Quich name when installing it with the `NAME` makefile variable:

`sudo make install NAME=calc`

Now you will be able to access Quich with the `calc` command.

## Testing

Move to your Quich folder and run the following command:

`make test && ./quich_test`

## Examples

```console
$ quich 5+3
8
```
```console
$ quich "a=20;a+1"
21
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
$ quich 1234567+1 -t
1,234,568
```
```console
$ quich 1gb+1mb
1049600
```
```console
$ quich 12345 -f '%.1g'
1e+04
```
```console
$ quich 5+PI -vvv
Tokens > '5' '+' 'PI'
Posfix > 5 PI +
Result > 8.14159265358979
```

## Contributing

Any contribution or support to this project in the form of a pull request or message will be highly appreciated. ❤️

You can read more about it [right here](CONTRIBUTING.md). Don't be shy :)

## License

Quich is open-source software licensed under the [MIT license](https://github.com/Usbac/quich/blob/master/LICENSE).
