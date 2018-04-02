In this video I'm going to provide an introduction to the Boost.Spirit library.

Just from my experience with it, this library is not that powerful as many others,
but it has a nice property - it is already there if you are using Boost.
So, you probably want to use it if you need to do some simple parsing,
like config file or some expressions.

Nice feature of this library that it leverages all of the power of C++ compliler
to compute parsing rules interoperability. For example, if you have a rule for
parsing a number, and it outputs an integer, then a parser build from the series of
this number-parsers must have output of vector of integers.

Downsides for this decision is that compilation errors are quite difficult to read,
because the library has so many degrees of freedom, it is so flexible, that every
single bit is a template parameter.

So, during this video we are going to write from scratch a couple of parsers
with explanation.

I have already prepared some docker containers to simplify the learning process
as much as possible, but the Docker builder-image is not necessary, again,
it is just a bootstrap for your convinience. In this video I will use the Docker
builder-image.

OK, I think we are done with intro, let's start our coding adventure!