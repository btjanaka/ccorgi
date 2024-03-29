# ccorgi


## Overview

![](docs/sample.png)

ccorgi is a simple program that causes cute corgis to scroll across your
terminal screen!


## Setup

Note: Currently, this program **only works on Linux**. You will also need to have libncurses5 installed.

Simply clone this repo to your home directory:
```shell
git clone https://github.com/btjanaka/ccorgi ~/ccorgi
```
Add the following line to your bashrc:
```shell
alias ccorgi=~/ccorgi/build/ccorgi
```
And reload bash with:
```shell
exec bash
```


## Usage

To run ccorgi after setup, simply run the following from the command line:
```
ccorgi
```
and watch corgis float across your screen!

ccorgi also takes the following flags:
```
-n [INTEGER] | The number of corgis to display.
```
By default, 3 corgis are displayed.


## Credits

The corgi I use was heavily inspired by Joan Stark's dog on ASCII Art Archive:

```
           __
      (___()'`;
      /,    /`
jgs   \\"--\\
```

I also used [this](http://getdrawings.com/pembroke-welsh-corgi-clipart#pembroke-welsh-corgi-clipart-1.jpg) image as inspiration.
