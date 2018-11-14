# iex_example

## How to build it
* Clone the repository
* Run `conan install <path_to_conanfile.txt>`
* Run `cmake .`
* Run `make`

## How to run
Sample command line: `iex_example -i 5 -s GOOGL AAPL`

## What is done
* Added polling info from the API
* Added configurable service
* Added storing to sqlite database
* Added sample unit testing with Catch2 framework

## TODO
* Add REST endpoint (e.g. via Poco/cpprestsdk library)
* Add unit testing for better coverage
* Add more Google services
