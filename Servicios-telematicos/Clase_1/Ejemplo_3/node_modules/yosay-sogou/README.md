# yosay-sogou

> Tell Yeoman what to say

## Install

```sh
$ npm install --save yosay-sogou
```


## Usage

```js
var yosay = require('yosay-sogou');

console.log(yosay('Welcome to the groovy Sogou generator!'));

/*

    _sogou_
   |       |    .--------------------------.
   |--(o)--|    |   Welcome to the groovy  |
  `---------´   |   Sogou generator!       |
   ( _´U`_ )    '--------------------------'
   /___A___\              
    |  ~  |          
  __'.___.'__
´   `  |° ´ Y `
 */
```

*You can style your text with [chalk](https://github.com/sindresorhus/chalk) before passing it to `yosay`.*


## CLI

```
$ npm install --global yosay-sogou
```

```
$ yosay --help

  Usage
    yosay <string>
    yosay <string> --maxLength 8
    echo <string> | yosay

  Example
    yosay 'Sindre is a horse'

     _sogou_
    |       |    .--------------------------.
    |--(o)--|    |     Sindre is a horse    |
   `---------´   '--------------------------'
    ( _´U`_ )
    /___A___\
     |  ~  |
   __'.___.'__
 ´   `  |° ´ Y `
```


## License

[BSD license](http://opensource.org/licenses/bsd-license.php)
 
