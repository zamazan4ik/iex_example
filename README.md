# iex_example

## How to build it
* Clone the repository
* Run `conan install <path_to_conanfile.txt>`
* Run `cmake .`
* Run `make`

## How to run
Run with JSON file in which must be listed symbols of required companies. Also you can specify
custom interval for polling. How to do it - run binary with `--help`

## TODO
* Add REST endpoint
* Add unit testing
* Fix issues with storing retrieved data
* Add more Google services